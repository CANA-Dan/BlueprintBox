// Copyright Epic Games, Inc. All Rights Reserved.

#include "AnalysisPluginBPLibrary.h"
#include "AnalysisPlugin.h"
#include "Audio.h"
#include <algorithm>
#include <string>
#include "tools/kiss_fftnd.h"
#include "AudioAnalysisToolsLibrary.h"
#include "async/Async.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "UObject/UObjectGlobals.h"
#include "GameFramework/Actor.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include <complex>
#include <valarray>
#include <cmath>

//======================================================================================================================
//											FFT Stuff
//======================================================================================================================

void UAnalysisPluginBPLibrary::CalculateFFT(const TArray<float> samples, const int32 NumChannels, const int32 SampleRate, TArray<float>& OutFrequencies, FString& Warnings)
{
	// Clear the Array before continuing
	OutFrequencies.Empty();

	// Make sure the Number of Channels is correct
	if (NumChannels > 0 && NumChannels <= 2)
	{

		//checks if we actually got any samples
		if (samples.Num() > 0)
		{

			int32 SamplesToRead = samples.Num() / 2;

			// Create two 2-dim Arrays for complex numbers | Buffer and Output
			kiss_fft_cpx* Buffer[2] = { 0 };
			kiss_fft_cpx* Output[2] = { 0 };

			// Create 1-dim Array with one slot for SamplesToRead
			int32 Dims[1] = { SamplesToRead };

			// alloc once and forget, should probably move to a init/deinit func
			kiss_fftnd_cfg STF = kiss_fftnd_alloc(Dims, 1, 0, NULL, NULL);

			// Allocate space in the Buffer and Output Arrays for all the data that FFT returns
			for (int32 ChannelIndex = 0; ChannelIndex < NumChannels; ChannelIndex++)
			{
				Buffer[ChannelIndex] = (kiss_fft_cpx*)KISS_FFT_MALLOC(sizeof(kiss_fft_cpx) * SamplesToRead);
				Output[ChannelIndex] = (kiss_fft_cpx*)KISS_FFT_MALLOC(sizeof(kiss_fft_cpx) * SamplesToRead);
			}

			float precomputeMultiplier = 2.f * PI / (SamplesToRead - 1);
			for (int32 SampleIndex = 0; SampleIndex < SamplesToRead; SampleIndex++)
			{
				//sets up some windowing stuff

				float Hanning = 0.5f * (1.f - FMath::Cos(2.f * PI * (static_cast<float>(SampleIndex) / (SamplesToRead - 1))));

				for (int32 ChannelIndex = 0; ChannelIndex < NumChannels; ChannelIndex++)
				{

					// Use Window function to get a better result for the Data (Hann Window)
					Buffer[ChannelIndex][SampleIndex].r = Hanning * samples[SampleIndex + ChannelIndex];

					Buffer[ChannelIndex][SampleIndex].i = 0.f;
				}
			}

			// Now that the Buffer is filled, use the FFT
			for (int32 ChannelIndex = 0; ChannelIndex < NumChannels; ChannelIndex++)
			{
				if (Buffer[ChannelIndex])
				{
					kiss_fftnd(STF, Buffer[ChannelIndex], Output[ChannelIndex]);
				}
			}

			OutFrequencies.AddZeroed(SamplesToRead);

			for (int32 SampleIndex = 0; SampleIndex < SamplesToRead; ++SampleIndex)
			{
				float ChannelSum = 0.0f;

				for (int32 ChannelIndex = 0; ChannelIndex < NumChannels; ++ChannelIndex)
				{
					if (Output[ChannelIndex])
					{
						// With this we get the actual Frequency value for the frequencies from 0hz to ~22000hz
						ChannelSum += FMath::Sqrt(FMath::Square(Output[ChannelIndex][SampleIndex].r) + FMath::Square(Output[ChannelIndex][SampleIndex].i));
					}
				}
				OutFrequencies[SampleIndex] = FMath::Pow((ChannelSum / NumChannels), 0.2);
			}

			// Make sure to free up the FFT stuff
			KISS_FFT_FREE(STF);

			for (int32 ChannelIndex = 0; ChannelIndex < NumChannels; ++ChannelIndex)
			{
				KISS_FFT_FREE(Buffer[ChannelIndex]);
				KISS_FFT_FREE(Output[ChannelIndex]);
			}


		}
		else {
			Warnings = "Number of SamplesToRead is < 0!";
		}
	}
	else {
		Warnings = "Number of Channels is < 0!";
	}
}


//allows you to clamp the range of the imput between 2 values
float clampRange(const float Input, const float MaxVal, const float MinVal) {
	return std::min(MaxVal, std::max(Input, MinVal));
}

//Using LowEntryExtendedStandardLibrary's functions for this. it worked super well in blueprints and i wanted to use it again here in C++.
UTexture2D* DataToTexture2D(int32 Width, int32 Height, const void* Src, SIZE_T Count)
{
	UTexture2D* Texture2D = UTexture2D::CreateTransient(Width, Height, EPixelFormat::PF_B8G8R8A8);
	if (Texture2D == nullptr)
	{
		return NULL;
	}
	Texture2D->bNoTiling = true;

#if WITH_EDITORONLY_DATA
	Texture2D->MipGenSettings = TMGS_NoMipmaps;
#endif

	void* TextureData = Texture2D->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(TextureData, Src, Count);
	Texture2D->PlatformData->Mips[0].BulkData.Unlock();

	Texture2D->UpdateResource();
	return Texture2D;
}

UTexture2D* PixelsToTexture2D(const int32 Width, const int32 Height, const TArray<FColor>& Pixels)
{
	if ((Pixels.Num() <= 0) || (Width <= 0) || (Height <= 0))
	{
		return NULL;
	}
	return DataToTexture2D(Width, Height, &Pixels[0], Pixels.Num() * sizeof(FColor));
}

void UAnalysisPluginBPLibrary::MakeSpectrogramColorArray(FSpectrogramInput SpectrogramValues, const int32 ChunkIndex, const int32 ThreadId, TEnumAsByte<FGenerationStatus>& ContinueLooping, TArray<FColor>& color) {

	ContinueLooping = FGenerationStatus::DontLoop;

	if (!(SpectrogramValues.ImportedSoundWave.IsValid() && SpectrogramValues.AudioAnalysisObject.IsValid())) {

		ContinueLooping = FGenerationStatus::InvalidObject;
		return;

	}

	UImportedSoundWave* ImportedSoundWave = SpectrogramValues.ImportedSoundWave.Get();
	UAudioAnalysisToolsLibrary* AudioAnalysisObject = SpectrogramValues.AudioAnalysisObject.Get();


	FSpectrogramTextureType textureType = SpectrogramValues.TextureType;
	int32 ThreadCount = SpectrogramValues.ThreadCount;
	int32 SpectrogramSamples = SpectrogramValues.SpectrogramSamples;
	int32 SpectrogramBands = SpectrogramValues.SpectrogramBands;

	int32 BandsMin = round(SpectrogramBands * SpectrogramValues.BandsMin);
	int32 BandsMax = round(SpectrogramBands * SpectrogramValues.BandsMax);
	int32 TextureHeight = (SpectrogramSamples + 1);
	int32 TextureWidth = SpectrogramBands + 1;

	//audio file setup
	int32 SampleRate = ImportedSoundWave->GetSampleRate();
	int32 NumChannels = ImportedSoundWave->NumChannels;
	float SongLength = ImportedSoundWave->GetDuration();

	//never used. just there to make the functions happy.
	FString WarningOut = "";

	// for use in multi threading. this allows you to more easily multi thread the spectrogram
	int32 ThreadLocation = ((ChunkIndex * ThreadCount) + ThreadId);

	//calculates how many bands have already been generated. the actual math is all the way at the bottom
	int32 BandsGenerated = 0;

	float freqCompPow = 0.8f + 1.f * 0.2f;

	// gets the offsets so that time is deadly accurate. 512 samples is 11ms for 44.1 sample rate.
	float MainOffset = (float(SpectrogramBands) / float(SampleRate)) * 1.5;



	//creates the chunk size and length in samples
	int32 firstIndex = ThreadLocation * SpectrogramSamples;
	int32 lastIndex = (ThreadLocation + 1) * SpectrogramSamples;
	TArray<FColor> Pixels;

	int32 whileLength = TextureWidth * TextureHeight;
	for (int32 Chunkpart = firstIndex; Chunkpart <= lastIndex; Chunkpart++) {

		int32 TriCounter = 0;

		// * 4 instead of * 2 because of a weird bug. its divided by 2 in the fft function to give you the proper size.
		float StartTime = (float(Chunkpart) / float(SpectrogramSamples)) - MainOffset;
		if (StartTime < 0.f) {
			StartTime = 0.f;
		}
		float EndTime = ((float(NumChannels * 4 * SpectrogramBands) / float(SampleRate)) + StartTime) - MainOffset;


		//get the samples for the main spectrogram.
		TArray<float> MainSpectrogram = {};

		//checking if the location to get is less than the imported sound length
		if (EndTime <= SongLength) {
			AudioAnalysisObject->GetAudioByTimeRange(ImportedSoundWave, StartTime, EndTime, MainSpectrogram);
		}
		else {

			while (Pixels.Num() - 1 < whileLength) {
				FColor CurrentPixel;
				CurrentPixel.R = 0;
				CurrentPixel.G = 0;
				CurrentPixel.B = 0;
				CurrentPixel.A = 255;

				Pixels.Add(CurrentPixel);
			}

			ContinueLooping = FGenerationStatus::Loop;
			color = Pixels;
			return;
		}

		MainSpectrogram.SetNumZeroed(NumChannels * 4 * SpectrogramBands);

		switch (textureType) {
			case Left: {	

				int TempLength = MainSpectrogram.Num() / 2;
				TArray<float> Channel = {};

				Channel.SetNumZeroed(TempLength);
				for(int i = 0; i < TempLength; i++) {
					Channel[i] = MainSpectrogram[i * 2];
				}

				MainSpectrogram = Channel;
				UAnalysisPluginBPLibrary::CalculateFFT(MainSpectrogram, NumChannels, SampleRate, MainSpectrogram, WarningOut);

				int32 MainSpectrogramLen = MainSpectrogram.Num();
				for (int32 FrequencyIndex = 0; FrequencyIndex < MainSpectrogramLen; FrequencyIndex++) {

					if (FrequencyIndex >= BandsMin) {

						if (FrequencyIndex <= BandsMax) {

							float MainSpectrogramVal = clampRange(MainSpectrogram[FrequencyIndex], 10.f, 0.0f);

							FColor CurrentPixel;
							int colorVal = round(clampRange(MainSpectrogramVal * 50.f, 255.f, 0.f));
							CurrentPixel.R = colorVal;
							CurrentPixel.G = colorVal;
							CurrentPixel.B = colorVal;
							CurrentPixel.A = 255;
							Pixels.Add(CurrentPixel);

						}
						else {
							break;
						}

					}

				}

				break;
			}
			case Right: {

				int TempLength = MainSpectrogram.Num() / 2;
				TArray<float> Channel = {};

				Channel.SetNumZeroed(TempLength);
				for (int i = 0; i < TempLength; i++) {
					Channel[i] = MainSpectrogram[(i * 2) + 1];
				}

				MainSpectrogram = Channel;
				UAnalysisPluginBPLibrary::CalculateFFT(MainSpectrogram, NumChannels, SampleRate, MainSpectrogram, WarningOut);
				
				int32 MainSpectrogramLen = MainSpectrogram.Num();
				for (int32 FrequencyIndex = 0; FrequencyIndex < MainSpectrogramLen; FrequencyIndex++) {

					if (FrequencyIndex >= BandsMin) {

						if (FrequencyIndex <= BandsMax) {

							float MainSpectrogramVal = clampRange(MainSpectrogram[FrequencyIndex], 10.f, 0.0f);

							FColor CurrentPixel;
							int colorVal = round(clampRange(MainSpectrogramVal * 50.f, 255.f, 0.f));
							CurrentPixel.R = colorVal;
							CurrentPixel.G = colorVal;
							CurrentPixel.B = colorVal;
							CurrentPixel.A = 255;
							Pixels.Add(CurrentPixel);

						}
						else {
							break;
						}

					}

				}

				break;
			}
			case Combined: {

				//the default behavior, so not much to do here
				UAnalysisPluginBPLibrary::CalculateFFT(MainSpectrogram, NumChannels, SampleRate, MainSpectrogram, WarningOut);

				int32 MainSpectrogramLen = MainSpectrogram.Num();
				for (int32 FrequencyIndex = 0; FrequencyIndex < MainSpectrogramLen; FrequencyIndex++) {

					if (FrequencyIndex >= BandsMin) {

						if (FrequencyIndex <= BandsMax) {

							float MainSpectrogramVal = clampRange(MainSpectrogram[FrequencyIndex], 10.f, 0.0f);

							FColor CurrentPixel;
							int colorVal = round(clampRange(MainSpectrogramVal * 50.f, 255.f, 0.f));
							CurrentPixel.R = colorVal;
							CurrentPixel.G = colorVal;
							CurrentPixel.B = colorVal;
							CurrentPixel.A = 255;
							Pixels.Add(CurrentPixel);

						}
						else {
							break;
						}

					}

				}

				break;
			}
		}

		//the make pixel stuff goes here
		BandsGenerated = BandsMax * (Chunkpart - (SpectrogramSamples * ThreadLocation));
	}

	ContinueLooping = FGenerationStatus::Loop;
	color = Pixels;
	return;
}

void UAnalysisPluginBPLibrary::MakeWaveformColorArray(FWaveformInput WaveformValues, const int32 ChunkIndex, const int32 ThreadId, TEnumAsByte<FGenerationStatus>& ContinueLooping, TArray<FColor>& color)
{
	ContinueLooping = FGenerationStatus::DontLoop;

	if (!(WaveformValues.ImportedSoundWave.IsValid() && WaveformValues.AudioAnalysisObject.IsValid())) {

		ContinueLooping = FGenerationStatus::InvalidObject;

		return;

	}

	//setting up some default values
	UImportedSoundWave* ImportedSoundWave = WaveformValues.ImportedSoundWave.Get();
	UAudioAnalysisToolsLibrary* AudioAnalysisObject = WaveformValues.AudioAnalysisObject.Get();

	int32 sampleRate = ImportedSoundWave->GetSampleRate();
	float songLength = ImportedSoundWave->GetDuration();

	int32 waveformSampleRate = sampleRate / WaveformValues.WaveformSampleRate;
	int32 textureWidth = WaveformValues.WaveformAudioGranularity;
	int32 WaveformChunk = (ChunkIndex * WaveformValues.ThreadCount) + ThreadId;

	TArray<FColor> Pixels;
	FColor WhitePixel;
	WhitePixel.R = 255;
	WhitePixel.G = 255;
	WhitePixel.B = 255;
	WhitePixel.A = 255;
	TArray<FColor> CleanPixels;
	CleanPixels.SetNumZeroed(textureWidth);
	TArray<FColor> TempPixels;

	//keeps you from doing this in the loop. allows you to convert the waveform from 0 and 2 to 0 and 1.
	float halfTextureWidth = float(textureWidth) * 0.5f;

	int32 loopSize = WaveformValues.WaveformSampleRate;
	TArray<float> AudioFrame;
	int32 End = 0;

	//onto the main loop stuff. precasting some values so i dont have to cast in the loop.
	float FloatingLoopSize = float(loopSize);
	float FloatingWaveformChunk = float(WaveformChunk);
	float singleSmapleDuration = 1.1f / float(sampleRate);

	//checks to make sure we are within the length of the song. otherwise it immediately exits

	for (int32 LoopIndex = 0; LoopIndex <= loopSize; LoopIndex++) {
		//float version so it doesnt have to be cast several times
		float FloatingIndex = float(LoopIndex);

		float startTime = (FloatingIndex / FloatingLoopSize) + FloatingWaveformChunk;
		//float endTime = startTime + singleSmapleDuration;
		float endTime = ((FloatingIndex + 1.f) / FloatingLoopSize) + FloatingWaveformChunk;

		//now to check if the time is still valid. if its not, the waveform will end cleanly
		if (endTime < songLength) {

			AudioAnalysisObject->GetAudioByTimeRange(ImportedSoundWave, startTime, endTime, AudioFrame);

			TempPixels = CleanPixels;

			//getting the first index of the audio frame. this would be faster if i could get specific indexes, but oh well.
			float Val = AudioFrame[0];
			int32 Start = floor((Val + 1.f) * halfTextureWidth);

			//a kinda hacky way of making the previous start time close enough to the previous chunk. most likely wrong, but good enough.
			if (LoopIndex == 0) {
				End = Start;
			}

			//onto the main pixel manipulation stuff. pretty simple. Color a line of pixels from point A to point B white.
			if (Start < End) {
				for (int32 i = Start; i < End; i++) {

					TempPixels[i] = WhitePixel;
				}

				Pixels.Append(TempPixels);
			}
			else {
				for (int32 i = End; i < Start; i++) {

					TempPixels[i] = WhitePixel;
				}

				Pixels.Append(TempPixels);
			}
			//now it starts on the next line of pixels.
			End = Start;
		}
		else {
			//makes the remaining pixels in one fell swoop.
			TempPixels.Empty();
			TempPixels.SetNumZeroed(textureWidth * (loopSize - LoopIndex));
			Pixels.Append(TempPixels);
			ContinueLooping = FGenerationStatus::Loop;
			color = Pixels;
			return;
		}

	}

	ContinueLooping = FGenerationStatus::Loop;
	color = Pixels;
	return;
}

UAnalysisPluginBPLibrary* UAnalysisPluginBPLibrary::CreateAnalysisPluginRef() {
	return NewObject<UAnalysisPluginBPLibrary>();
}


//this function is on the secondary thread.
void UAnalysisPluginBPLibrary::CalculateSpectrogramAsync(UAnalysisPluginBPLibrary* AnalysisPluginRef, FGenerationType type, FWaveformInput WaveformInput, FSpectrogramInput SpectrogramInput, int32 ChunkIndex, int32 ThreadID) {

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("accessing now"));

	FSpectrogramOutput TempOutput;
	UAnalysisPluginBPLibrary* ref = AnalysisPluginRef;
	if (!(SpectrogramInput.ImportedSoundWave.IsValid() && SpectrogramInput.AudioAnalysisObject.IsValid() && ref->IsValidLowLevel())) {

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("main thread invalid"));
		TempOutput.Status = FGenerationStatus::InvalidObject;
		ref->DoneCalculating_Internal(TempOutput, ref);
		return;
	}

	switch (type)
	{
	case Waveform:
		{
			AsyncTask(ENamedThreads::AnyThread, [ref, WaveformInput, ChunkIndex, ThreadID, TempOutput]() mutable {

				if (!(WaveformInput.ImportedSoundWave.IsValid() && WaveformInput.AudioAnalysisObject.IsValid() && ref->IsValidLowLevel())) {
					FSpectrogramOutput tempoutput;
					tempoutput.Status = FGenerationStatus::InvalidObject;
					ref->DoneCalculating_Internal(TempOutput, ref);
					return;
				}

				TEnumAsByte<FGenerationStatus> ContinueLooping;
				TArray<FColor> color;
				UImportedSoundWave* audio = WaveformInput.ImportedSoundWave.Get();

				TempOutput.Time = ((ChunkIndex + 1) * WaveformInput.ThreadCount) + (ThreadID - WaveformInput.ThreadCount + 1);
				if (!(float(TempOutput.Time - 1) < audio->GetDuration())) {
					TempOutput.Status = FGenerationStatus::DontLoop;
					ref->DoneCalculating_Internal(TempOutput, ref);
					return;
				}

				//running the Waveform function
				UAnalysisPluginBPLibrary::MakeWaveformColorArray(WaveformInput, ChunkIndex, ThreadID, ContinueLooping, color);

				int32 tempChunkIndex = ChunkIndex + 1;
				int32 height = WaveformInput.WaveformAudioGranularity;
				int32 width = color.Num() / height;

				//doing this because i cant be assed to figure out the real size atm.
				//regardless, im not gaining or losing any data by doing this method, so it doesnt matter overall.
				color.SetNumZeroed(height * width);
				TempOutput.Status = ContinueLooping;
				TArray<FColor> ColorArray = color;

				//tried very hard to make this texture creation stuff async. Wasnt able to in the end.
				AsyncTask(ENamedThreads::GameThread, [height, width, tempChunkIndex, ref, TempOutput, ColorArray]() mutable {
					if (ColorArray.Num() > 0) {
						TempOutput.Texture = PixelsToTexture2D(height, width, ColorArray);
						TempOutput.ChunkIndex = tempChunkIndex;
					}
					else {
						TempOutput.Status = FGenerationStatus::InvalidObject;
						TempOutput.ChunkIndex = tempChunkIndex;
					}

					FString thing = "";
					if (!ref->IsValidLowLevel()) {
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MyLibRef is valid"));
					}

					ref->DoneCalculating_Internal(TempOutput, ref);
					return;
				});
			});
		}
		break;

	case Spectrogram:
		{
			AsyncTask(ENamedThreads::AnyThread, [ref, SpectrogramInput, ChunkIndex, ThreadID, TempOutput]() mutable {

				if (!(SpectrogramInput.ImportedSoundWave.IsValid() && SpectrogramInput.AudioAnalysisObject.IsValid() && ref->IsValidLowLevel())) {
					FSpectrogramOutput tempoutput;
					tempoutput.Status = FGenerationStatus::InvalidObject;
					ref->DoneCalculating_Internal(TempOutput, ref);
					return;
				}

				TEnumAsByte<FGenerationStatus> ContinueLooping;
				TArray<FColor> color;
				UImportedSoundWave* audio = SpectrogramInput.ImportedSoundWave.Get();

				TempOutput.Time = ((ChunkIndex + 1) * SpectrogramInput.ThreadCount) + (ThreadID - SpectrogramInput.ThreadCount + 1);
				if (!(float(TempOutput.Time - 1) < audio->GetDuration())) {
					TempOutput.Status = FGenerationStatus::DontLoop;
					ref->DoneCalculating_Internal(TempOutput, ref);
					return;
				}

				//running the main FFT function
				UAnalysisPluginBPLibrary::MakeSpectrogramColorArray(SpectrogramInput, ChunkIndex, ThreadID, ContinueLooping, color);

				int32 tempChunkIndex = ChunkIndex + 1;
				int32 height = SpectrogramInput.SpectrogramSamples + 1;
				int32 width = color.Num() / height;

				//doing this because i cant be assed to figure out the real size atm.
				//regardless, im not gaining or losing any data by doing this method, so it doesnt matter overall.
				color.SetNumZeroed(height * width);
				TempOutput.Status = ContinueLooping;
				TArray<FColor> ColorArray = color;

				//tried very hard to make this texture creation stuff async. Wasnt able to in the end.
				AsyncTask(ENamedThreads::GameThread, [height, width, tempChunkIndex, ref, TempOutput, ColorArray]() mutable {
					if (ColorArray.Num() > 0) {
						TempOutput.Texture = PixelsToTexture2D(width, height, ColorArray);
						TempOutput.ChunkIndex = tempChunkIndex;
					}
					else {
						TempOutput.Status = FGenerationStatus::InvalidObject;
						TempOutput.ChunkIndex = tempChunkIndex;
					}

					ref->DoneCalculating_Internal(TempOutput, ref);
					return;
				});
			});
		}
		break;

	}

}

void UAnalysisPluginBPLibrary::DoneCalculating_Internal(FSpectrogramOutput output, UAnalysisPluginBPLibrary* Ref)
{

	AsyncTask(ENamedThreads::GameThread, [Ref, output]()
		{

			if (!Ref->IsValidLowLevel())
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("pointer is invalid"));
				return;
			}

			bool bBroadcasted{ false };

			if (Ref->DoneCalculating.IsBound())
			{
				bBroadcasted = true;
				Ref->DoneCalculating.Broadcast(output);
			}

			if (!bBroadcasted)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to send!"));
			}
		});

}

//======================================================================================================================
//											Data Stuff
//======================================================================================================================

//helper function to get the specific transform type requested.
float UAnalysisPluginBPLibrary::getTransformAxis(AActor* ActorRef, FActorTransform SortingAxis) {
	if (ActorRef->IsValidLowLevel()) {
		switch (SortingAxis) {
			case LocationX:
			{
				return ActorRef->GetActorLocation().X;
			}
			case LocationY:
			{
				return ActorRef->GetActorLocation().Y;
			}
			case LocationZ:
			{
				return ActorRef->GetActorLocation().Z;
			}
			case RotationX:
			{
				return ActorRef->GetActorRotation().Vector().X;
			}
			case RotationY:
			{
				return ActorRef->GetActorRotation().Vector().Y;
			}
			case RotationZ:
			{
				return ActorRef->GetActorRotation().Vector().Z;
			}
			case ScaleX:
			{
				return ActorRef->GetActorScale().X;
			}
			case ScaleY:
			{
				return ActorRef->GetActorScale().Y;
			}
			case ScaleZ:
			{
				return ActorRef->GetActorScale().Z;
			}
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("object transform could not be gotten. null object"));
	return 0.0;
}

int64 GetDigitAtColumn(int64 num, int64 column) {
	int64 DigitAtColumn = floor(double(num) / powl(10, double(column)));
	return DigitAtColumn - floor((double(DigitAtColumn) * 0.1l)) * 10;
}

template<class TypeFrom, class TypeTo>
void UAnalysisPluginBPLibrary::CastArray(const TArray<TypeFrom*> FromObjArray, TArray<TypeTo*>& ToObjArray)
{
	ToObjArray.Reserve(FromObjArray.Num());
	for (TypeFrom* FromObj : FromObjArray)
	{
		if (TypeTo* ToObj = Cast<TypeTo>(FromObj))
		{
			ToObjArray.Add(ToObj);
		}
	}
}

TArray<AActor*> UAnalysisPluginBPLibrary::RadixSortActorsTransform(TArray<AActor*> ActorArray, FActorTransform SortingAxis, float Accuracy)
{
	TArray<AActor*> RadixActorArray = ActorArray;
	TArray<AActor*> TempActorArray = ActorArray;


	int64 DigitLength = 0;
	
	int32 TotalItems = RadixActorArray.Num();
	double HighestVal = 0.0;
	double LowestVal = 0.0;
	double transform = 0.0;

	//find the highest and lowest value
	for (int32 i = 0; i < TotalItems; i++) {

		transform = getTransformAxis(RadixActorArray[i], SortingAxis);
		HighestVal = FGenericPlatformMath::Max<double>(HighestVal, transform);
		LowestVal = FGenericPlatformMath::Min<double>(HighestVal, transform);
	}

	if (LowestVal >= 0.0) {
		LowestVal = 0.0;
	}
	else {
		LowestVal = LowestVal * -1;
	}

	HighestVal = (HighestVal + LowestVal) * Accuracy;

	//find how many digits the value is
	while (HighestVal > 1.0) {
		HighestVal = HighestVal * 0.1;
		DigitLength++;
	}
	
	//the main for loop
	TArray<int64> RadixSortCounter;
	for (int ForLoop = 0; ForLoop <= DigitLength; ForLoop++) {
		RadixSortCounter.Empty();
		RadixSortCounter.SetNum(10);
		int64 DigAtColIndex = 0;

		//find how many of each digit.
		for (int32 j = 0; j < TotalItems; j++) {
			transform = (getTransformAxis(RadixActorArray[j], SortingAxis) + LowestVal) * Accuracy;
			DigAtColIndex = GetDigitAtColumn(int64(floor(transform)), ForLoop);
			RadixSortCounter[DigAtColIndex] = RadixSortCounter[DigAtColIndex] ++;
		}

		// cant remember what this does, but something important im sure
		for (int32 index = 1; index <= 9; index++) {
			RadixSortCounter[index] = RadixSortCounter[index] + RadixSortCounter[index - 1];
		}

		int32 Rev = TotalItems - 1;
		//the reverse for loop for sorting each digit into its bins
		for (int32 i = Rev; i >= 0; i--) {

			transform = (getTransformAxis(RadixActorArray[i], SortingAxis) + LowestVal) * Accuracy;
			DigAtColIndex = GetDigitAtColumn(int64(floor(transform)), ForLoop);
			RadixSortCounter[DigAtColIndex] = RadixSortCounter[DigAtColIndex] --;
			int32 arrayindex = RadixSortCounter[DigAtColIndex];
			TempActorArray[arrayindex] = RadixActorArray[i];
		}

		RadixActorArray = TempActorArray;
	}

	return RadixActorArray;
}

void UAnalysisPluginBPLibrary::GetObjReferences(UObject* Obj, TArray<UObject*>& OutReferencedObjects)
{
	if (!Obj || !Obj->IsValidLowLevelFast())
	{
		return;
	}

	TArray<UObject*> ReferredToObjects;             //req outer, ignore archetype, recursive, ignore transient
	FReferenceFinder ObjectReferenceCollector(ReferredToObjects, Obj, false, true, true, false);
	ObjectReferenceCollector.FindReferences(Obj);


	OutReferencedObjects.Append(ReferredToObjects);
;
}

void UAnalysisPluginBPLibrary::FreeMem(UObject* Object)
{
		//stacked like this because 'IsPendingKill' will throw an exception if it isnt valid. ie, i dont think i can do it on the same line.
		if (Object->IsValidLowLevel()) {
			if (!Object->IsPendingKill()) {
				Object->UObject::ConditionalBeginDestroy();
			}
		}

}


//======================================================================================================================
//											Midi Stuff
//======================================================================================================================

void UAnalysisPluginBPLibrary::ImportBinaryFromDisk(FString Path, TArray<uint8>& ArrayOfBytes, FString& ErrorLog)
{
	FText error;

	if (!FFileHelper::IsFilenameValidForSaving(Path, error)) {
		ErrorLog = "Error";
		return;

	}
	FFileHelper::LoadFileToArray(ArrayOfBytes, *Path);
	ErrorLog = "Success";
}


int64 UAnalysisPluginBPLibrary::ByteArrayToInt(const TArray<uint8> ArrayOfBytes, bool BigEndian, bool Signed)
{
	if (ArrayOfBytes.Num() == 0) {
		return 0;
	}

	TArray<uint8> Bytes = ArrayOfBytes;
	if (Bytes.Num() > 8) {
		Bytes.SetNum(8, true);
	}
	
	int64 num = 0;
	int32 len = Bytes.Num() - 1;
	if (BigEndian == false) {
		Algo::Reverse(Bytes);
	}

	for (int32 i = 0; i <= len; i++) {
		num += (Bytes[i] * pow(256, len - i));
	}

	if (Signed == true) {
		if (num >= pow(2, (Bytes.Num() * 8) - 1)) {
			num -= pow(2, Bytes.Num() * 8);
		}

	}
	return int64(num);
}

FString UAnalysisPluginBPLibrary::ByteToChar(uint8 Byte)
{
	FString Char = " ";
	Char[0] = char(Byte);
	return Char;
}

bool UAnalysisPluginBPLibrary::IsValidChar(const uint8 Byte, bool CheckIfChar, bool CheckIfInt, bool CheckIfCommonSpecialCharacter, bool CheckIfUncommonSpecialCharacter, TArray<FString> AdditionalCharacters)
{

	FString Char = ByteToChar(Byte);
	char ch = Char[0];

	if (CheckIfChar && ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')))
	{
		return true;
	}

	if (CheckIfInt && (ch >= '0' && ch <= '9'))
	{
		return true;
	}

	//if theres an easier way to do this, let me know. for now, the brute force way.
	if (CheckIfCommonSpecialCharacter) {
		switch (ch) {
			case '!':
			{
				return true;
			}
			case '&':
			{
				return true;
			}
			case '(':
			{
				return true;
			}
			case ')':
			{
				return true;
			}
			case '-':
			{
				return true;
			}
			case '_':
			{
				return true;
			}
			case '|':
			{
				return true;
			}
			case ';':
			{
				return true;
			}
			case ':':
			{
				return true;
			}
			case '\'':
			{
				return true;
			}
			case '"':
			{
				return true;
			}
			case ',':
			{
				return true;
			}
			case '.':
			{
				return true;
			}
			case '/':
			{
				return true;
			}
			case '?':
			{
				return true;
			}
			case ' ':
			{
				return true;
			}
		}
	}

	if (CheckIfUncommonSpecialCharacter) {
		switch (ch) {
			case '`':
			{
				return true;
			}
			case '~':
			{
				return true;
			}
			case '@':
			{
				return true;
			}
			case '#':
			{
				return true;
			}
			case '$':
			{
				return true;
			}
			case '%':
			{
				return true;
			}
			case '^':
			{
				return true;
			}
			case '*':
			{
				return true;
			}
			case '=':
			{
				return true;
			}
			case '+':
			{
				return true;
			}
			case '[':
			{
				return true;
			}
			case '{':
			{
				return true;
			}
			case ']':
			{
				return true;
			}
			case '}':
			{
				return true;
			}
			case '\\':
			{
				return true;
			}
			case '<':
			{
				return true;
			}
			case '>':
			{
				return true;
			}
		}
	}

	if (AdditionalCharacters.Num() > 0) {
		for (int i = 0; i < AdditionalCharacters.Num(); i++) {
			if (AdditionalCharacters[i][0] == ch) {
				return true;
				break;
			}
		}
	}
	return false;
}

void UAnalysisPluginBPLibrary::ProvideMidiChunks(const TArray<uint8> ArrayOfBytes, FMidiStruct& MetaData, TArray<FMidiChunk>& Chunk)
{
	int32 length = ArrayOfBytes.Num();
	int32 uintToInt = pow(2, 31);
	int32 Index = 0;

	for (int32 i = Index; i < length; i++) {
		FString Char;
		Char = ",";
		Char = ByteToChar(ArrayOfBytes[i]);

		//initial check for if its a midi header.
		if (Char == "M") {

			//actual check for initial midi header. Should be right at the beginning of the file, but, yah know, never can be sure.
			FString FullHeaderCheck = ByteToChar(ArrayOfBytes[i]) + ByteToChar(ArrayOfBytes[i + 1]) + ByteToChar(ArrayOfBytes[i + 2]) + ByteToChar(ArrayOfBytes[i + 3]);
			if ("MThd" == FullHeaderCheck) {
				i = i + 4;
				int32 headerLen = 0;
				TArray<uint8> Array;

				int len = 4;
				Array.SetNum(len);
				for (int j = 0; j < len; j++) {
					Array[j] = ArrayOfBytes[i + j];
				}
				headerLen = ByteArrayToInt(Array, true, false);
				i = i + len;

				//Header Offset
				int hO = i;

				//midi type. should be a direct conversion. not sure why its 16 bits long when 8 bits would have been fine, but it is.
				len = 2;
				Array.SetNum(len);
				for (int j = 0; j < len; j++) {
					Array[j] = ArrayOfBytes[hO + j];
				}
				MetaData.Format = FMidiFormat(ByteArrayToInt(Array, true, false));
				hO += len;

				//how many midi tracks this file contains
				len = 2;
				Array.SetNum(len);
				for (int j = 0; j < len; j++) {
					Array[j] = ArrayOfBytes[hO + j];
				}
				MetaData.TrackCount = ByteArrayToInt(Array, true, false);
				hO += len;

				//expected values are 192, 128, 96 or something.
				len = 2;
				Array.SetNum(len);

				if (ArrayOfBytes[hO] <= 127) {
					//this is ticks
					for (int j = 0; j < len; j++) {
						Array[j] = ArrayOfBytes[hO + j];
					}
					MetaData.Division = ByteArrayToInt(Array, true, false);
					MetaData.DivisionType = Ticks;

				} else {
					//this is SMTPE frames
					//left byte is converted to signed (should be a value like -24, -25, -29, or -30) then is converted to positive and multiplied by the ticks per frame value.
					//25 * 40 for example gives the value of 1ms per tick

					MetaData.Division = (int8(ArrayOfBytes[hO]) * -1) * ArrayOfBytes[hO];
					MetaData.DivisionType = SMTPEframes;
				}

				//just to be sure the location we are going to is the next header
				Index = i + headerLen;

				break;
			};
		}
	}

	Chunk.SetNum(MetaData.TrackCount);

	int ChunkIndex = -1;

	//now getting each chunk. 
	for (int32 i = Index; i < ArrayOfBytes.Num(); i++) {
		FString Char;
		Char = ",";
		Char = ByteToChar(ArrayOfBytes[i]);

		//initial check for if its a midi header.
		if (Char == "M") {
			
			//gets this chunk.
			FString FullHeaderCheck = ByteToChar(ArrayOfBytes[i]) + ByteToChar(ArrayOfBytes[i + 1]) + ByteToChar(ArrayOfBytes[i + 2]) + ByteToChar(ArrayOfBytes[i + 3]);
			if ("MTrk" == FullHeaderCheck) {
				ChunkIndex++;
			};
		}

		//checking if the chunks index is valid.
		if (ChunkIndex < MetaData.TrackCount) {

			Chunk[ChunkIndex].MIDIBinary.Add(ArrayOfBytes[i]);
		}
		
	}
}

void UAnalysisPluginBPLibrary::GetTickDelta(const TArray<uint8> ArrayOfBytes, int32 StartIndex, int32& TickDelta, int32& NewIndex)
{	
	//good sanity check. variable length data cant be more than 4 byts anyways as the value needs to fit into the a 32 bit int.
	int MaxEndIndex = StartIndex + 4;

	TArray<uint8> timeDelta;
	int32 TempDelta = 0;

	for (int i = StartIndex; i < MaxEndIndex; i++) {
		//if it encounters a value higher than F7, it needs to be overflowed down to 00. 81 is equivilent to 1. 
		//this also means that its not the last value in the var len data, as the last value will always be below 128.
		if (ArrayOfBytes[i] > 127) {
			timeDelta.Add(ArrayOfBytes[i] - 128);
		}
		else {
			timeDelta.Add(ArrayOfBytes[i]);
			break;
		}
	}

	int len = timeDelta.Num() - 1;
	
	for (int i = len; i >= 0; i--) {

		TempDelta = TempDelta + timeDelta[len - i] * pow(128, i);
	}
	TickDelta = TempDelta;
	NewIndex = len + 1 + StartIndex;
}

void UAnalysisPluginBPLibrary::GetMidiType(const TArray<uint8> ArrayOfBytes, int32 StartIndex, TEnumAsByte<FMidiNoteType>& DataType, TArray<uint8>& DataReturn, int32& Channel, int32& NewIndex)
{	
	uint8 byte = ArrayOfBytes[StartIndex];
	Channel = byte % 16;
	int firstHex = (byte - Channel) / 16;


	switch (firstHex) {
		case 8:
		{
			DataType = NoteOff;
			int DataLength = 2;
			for (int i = 0; i < DataLength; i++) {
				uint8 data = ArrayOfBytes[StartIndex + i + 1];
				if (data > 127) {
					DataType = NaN;
					NewIndex = StartIndex + 1;
					return;
				}
				DataReturn.Add(data);
			}
			NewIndex = StartIndex + 1 + DataLength;
			return;
		}
		case 9:
		{
			DataType = NoteOn;
			int DataLength = 2;
			for (int i = 0; i < DataLength; i++) {
				uint8 data = ArrayOfBytes[StartIndex + i + 1];
				if (data > 127) {
					DataType = NaN;
					NewIndex = StartIndex + 1;
					return;
				}
				DataReturn.Add(data);
			}
			NewIndex = StartIndex + 1 + DataLength;
			return;
		}
		case 10:
		{
			DataType = AfterTouch;
			int DataLength = 2;
			for (int i = 0; i < DataLength; i++) {
				uint8 data = ArrayOfBytes[StartIndex + i + 1];
				if (data > 127) {
					DataType = NaN;
					NewIndex = StartIndex + 1;
					return;
				}
				DataReturn.Add(data);
			}
			NewIndex = StartIndex + 1 + DataLength;
			return;
		}
		case 11:
		{
			DataType = ControlChange;
			int DataLength = 2;
			for (int i = 0; i < DataLength; i++) {
				uint8 data = ArrayOfBytes[StartIndex + i + 1];
				if (data > 127) {
					DataType = NaN;
					NewIndex = StartIndex + 1;
					return;
				}
				DataReturn.Add(data);
			}
			NewIndex = StartIndex + 1 + DataLength;
			return;
		}
		case 12:
		{
			DataType = ProgramChange;
			int DataLength = 1;
			for (int i = 0; i < DataLength; i++) {
				uint8 data = ArrayOfBytes[StartIndex + i + 1];
				if (data > 127) {
					DataType = NaN;
					NewIndex = StartIndex + 1;
					return;
				}
				DataReturn.Add(data);
			}
			NewIndex = StartIndex + 1 + DataLength;
			return;
		}
		case 13:
		{
			DataType = ChannelPressure;
			int DataLength = 1;
			for (int i = 0; i < DataLength; i++) {
				uint8 data = ArrayOfBytes[StartIndex + i + 1];
				if (data > 127) {
					DataType = NaN;
					NewIndex = StartIndex + 1;
					return;
				}
				DataReturn.Add(data);
			}
			NewIndex = StartIndex + 1 + DataLength;
			return;
		}
		case 14:
		{
			DataType = PitchWheel;
			int DataLength = 2;
			for (int i = 0; i < DataLength; i++) {
				uint8 data = ArrayOfBytes[StartIndex + i + 1];
				if (data > 127) {
					DataType = NaN;
					NewIndex = StartIndex + 1;
					return;
				}
				DataReturn.Add(data);
			}
			NewIndex = StartIndex + 1 + DataLength;
			return;
		}
		case 15:
		{
			DataType = SysMes;
			NewIndex = StartIndex;
			return;
		}
		default:
		{
			DataType = NaN;
			NewIndex = StartIndex + 1;
			return;
		}
	}
}

void UAnalysisPluginBPLibrary::GetSysMessage(const TArray<uint8> ArrayOfBytes, int32 StartIndex, TEnumAsByte<FMidiSysMessages>& DataType, TArray<uint8>& DataReturn, int32& NewIndex)
{
	uint8 byte = ArrayOfBytes[StartIndex];
	int secondHex = byte % 16;

	switch (secondHex) {
		case 0:
		{
			DataType = SysEx;
			uint8 Data = 0;
			int DataLength = 0;

			//does a check for the while loop so it doesnt exceed 1000 loops. as a sanity check. because this is totally dynamically sized, i think iv just got to do this and hope for the best.
			if (DataReturn.Num() > 0) {
				while ((Data != 247) && (DataLength < 1000)) {

					Data = ArrayOfBytes[StartIndex + DataLength];
					DataReturn[DataLength] = Data;
					DataLength++;
				}
			}
			
			NewIndex = StartIndex + 1 + DataLength;
			return;
		}
		case 1:
		{
			DataType = UndfOne;
			NewIndex = StartIndex + 1;
			return;
		}
		case 2:
		{
			DataType = SongPosPtr;
			int DataLength = 2;
			for (int i = 0; i < DataLength; i++) {
				DataReturn.Add(ArrayOfBytes[StartIndex + i]);
			}
			NewIndex = StartIndex + 1 + DataLength;
			return;
		}
		case 3:
		{
			DataType = SongSelect;
			int DataLength = 1;
			for (int i = 0; i < DataLength; i++) {
				DataReturn.Add(ArrayOfBytes[StartIndex + i]);
			}
			NewIndex = StartIndex + 1 + DataLength;
			return;
		}
		case 4:
		{
			DataType = UndfTwo;
			NewIndex = StartIndex + 1;
			return;
		}
		case 5:
		{
			DataType = UndfThree;
			NewIndex = StartIndex + 1;
			return;
		}
		case 6:
		{
			DataType = TuneRequest;
			NewIndex = StartIndex + 1;
			return;
		}
		case 7:
		{
			DataType = EndOfSysEx;
			NewIndex = StartIndex + 1;
			return;
		}
		case 8:
		{
			DataType = TimingClock;
			NewIndex = StartIndex + 1;
			return;
		}
		case 9:
		{
			DataType = UndfFour;
			NewIndex = StartIndex + 1;
			return;
		}
		case 10:
		{
			DataType = Start;
			NewIndex = StartIndex + 1;
			return;
		}
		case 11:
		{
			DataType = Continue;
			NewIndex = StartIndex + 1;
			return;
		}
		case 12:
		{
			DataType = Stop;
			NewIndex = StartIndex + 1;
			return;
		}
		case 13:
		{
			DataType = UndfFive;
			NewIndex = StartIndex + 1;
			return;
		}
		case 14:
		{
			DataType = ActiveSensing;
			NewIndex = StartIndex + 1;
			return;
		}
		case 15:
		{
			DataType = ResetMeta;
			NewIndex = StartIndex;
			return;
		}
	}
}

void UAnalysisPluginBPLibrary::GetMetaEvent(const TArray<uint8> ArrayOfBytes, const int32 StartIndex, TEnumAsByte<FMidiMetaEvents>& DataType, TArray<uint8>& DataReturn, int32& NewIndex) {

	int index = StartIndex + 1;
	uint8 Type = ArrayOfBytes[index];
	index = StartIndex + 2;
	switch (Type) {
		case 0:
		{
			DataType = SequenceNum;
			int DataLength = 0;
			int nah = 0;
			UAnalysisPluginBPLibrary::GetTickDelta(ArrayOfBytes, index, DataLength, nah);
			for (int i = 0; i < DataLength; i++) {
				DataReturn.Add(ArrayOfBytes[index + i + 1]);
			}
			NewIndex = index + 1 + DataLength;
			return;
		}
		case 1:
		{
			DataType = Text;
			int DataLength = 0;
			int nah = 0;
			UAnalysisPluginBPLibrary::GetTickDelta(ArrayOfBytes, index, DataLength, nah);
			for (int i = 0; i < DataLength; i++) {
				DataReturn.Add(ArrayOfBytes[index + i + 1]);
			}
			NewIndex = index + 1 + DataLength;
			return;
		}
		case 2:
		{
			DataType = Copywrite;
			int DataLength = 0;
			int nah = 0;
			UAnalysisPluginBPLibrary::GetTickDelta(ArrayOfBytes, index, DataLength, nah);
			for (int i = 0; i < DataLength; i++) {
				DataReturn.Add(ArrayOfBytes[index + i + 1]);
			}
			NewIndex = index + 1 + DataLength;
			return;
		}
		case 3:
		{
			DataType = TrackName;
			int DataLength = 0;
			int nah = 0;
			UAnalysisPluginBPLibrary::GetTickDelta(ArrayOfBytes, index, DataLength, nah);
			for (int i = 0; i < DataLength; i++) {
				DataReturn.Add(ArrayOfBytes[index + i + 1]);
			}
			NewIndex = index + 1 + DataLength;
			return;
		}
		case 4:
		{
			DataType = InstrumentName;
			int DataLength = 0;
			int nah = 0;
			UAnalysisPluginBPLibrary::GetTickDelta(ArrayOfBytes, index, DataLength, nah);
			for (int i = 0; i < DataLength; i++) {
				DataReturn.Add(ArrayOfBytes[index + i + 1]);
			}
			NewIndex = index + 1 + DataLength;
			return;
		}
		case 5:
		{
			DataType = Lyric;
			int DataLength = 0;
			int nah = 0;
			UAnalysisPluginBPLibrary::GetTickDelta(ArrayOfBytes, index, DataLength, nah);
			for (int i = 0; i < DataLength; i++) {
				DataReturn.Add(ArrayOfBytes[index + i + 1]);
			}
			NewIndex = index + 1 + DataLength;
			return;
		}
		case 6:
		{
			DataType = Marker;
			int DataLength = 0;
			int nah = 0;
			UAnalysisPluginBPLibrary::GetTickDelta(ArrayOfBytes, index, DataLength, nah);
			for (int i = 0; i < DataLength; i++) {
				DataReturn.Add(ArrayOfBytes[index + i + 1]);
			}
			NewIndex = index + 1 + DataLength;
			return;
		}
		case 7:
		{
			DataType = CuePoint;
			int DataLength = 0;
			int nah = 0;
			UAnalysisPluginBPLibrary::GetTickDelta(ArrayOfBytes, index, DataLength, nah);
			for (int i = 0; i < DataLength; i++) {
				DataReturn.Add(ArrayOfBytes[index + i + 1]);
			}
			NewIndex = index + 1 + DataLength;
			return;
		}
		case 32:
		{
			DataType = ChannelPrefix;
			int DataLength = 1;
			DataReturn.Add(ArrayOfBytes[index + DataLength]);
			NewIndex = index + 1 + DataLength;
			return;
		}
		case 47:
		{
			DataType = EndOfTrack;
			int DataLength = 1;
			DataReturn.Add(0);
			NewIndex = index + 1 + DataLength;
			return;
		}
		case 81:
		{
			DataType = SetTempo;
			int DataLength = 3;
			for (int i = 0; i < DataLength; i++) {
				DataReturn.Add(ArrayOfBytes[index + i + 1]);
			}
			NewIndex = index + 1 + DataLength;
			return;
		}
		case 84:
		{
			DataType = SMPTEOffset;
			int DataLength = 5;
			for (int i = 0; i < DataLength; i++) {
				DataReturn.Add(ArrayOfBytes[index + i + 1]);
			}
			NewIndex = index + 1 + DataLength;
			return;
		}
		case 88:
		{
			DataType = TimeSig;
			int DataLength = 4;
			for (int i = 0; i < DataLength; i++) {
				DataReturn.Add(ArrayOfBytes[index + i + 1]);
			}
			NewIndex = index + 1 + DataLength;
			return;
		}
		case 89:
		{
			DataType = KeySig;
			int DataLength = 2;
			for (int i = 0; i < DataLength; i++) {
				DataReturn.Add(ArrayOfBytes[index + i + 1]);
			}
			NewIndex = index + 1 + DataLength;
			return;
		}
		case 127:
		{
			DataType = SeqMetaEvent;
			int DataLength = 0;
			int nah = 0;
			UAnalysisPluginBPLibrary::GetTickDelta(ArrayOfBytes, StartIndex + 2, DataLength, nah);
			for (int i = 0; i < DataLength; i++) {
				DataReturn.Add(ArrayOfBytes[index + i + 1]);
			}
			NewIndex = index + 1 + DataLength;
			return;
		}
	}
}

void UAnalysisPluginBPLibrary::ImportMidi(FString MidiFileLocation, FString& ErrorLog, FMidiStruct& MetaData, TArray<FMidiTrack>& MidiTracks)
{
	TArray<uint8> bytes;

	TArray<FMidiChunk> chunks;
	UAnalysisPluginBPLibrary::ImportBinaryFromDisk(MidiFileLocation, bytes, ErrorLog);

	UAnalysisPluginBPLibrary::ProvideMidiChunks(bytes, MetaData, chunks);

	TArray<FMidiTrack> Tracks;
	Tracks.SetNum(chunks.Num());
	TEnumAsByte<FMidiNoteType> NoteType;
	TEnumAsByte<FMidiSysMessages> SysMesType;
	TEnumAsByte<FMidiMetaEvents> MetaEventType;

	

	//to get past the header data
	int index = 0;
	int tickDelta = 0;
	int tick = 0;
	int channel = 0;

	for (int i = 0; i < chunks.Num(); i++)
	{	
		index = 9;
		tick = 0;
		tickDelta = 0;
		MetaEventType = NaME;

		TArray<FMidiNote> noteArray;

		TArray<uint8> Binary;
		Binary = chunks[i].MIDIBinary;
		
		while (index < Binary.Num())
		{	
			FMidiNote note;
			TArray<uint8> DataBytes;

			UAnalysisPluginBPLibrary::GetMidiType(Binary, index, NoteType, DataBytes, channel, index);
			note.Note = NoteType;
			note.Channel = channel;
			note.DataBytes = DataBytes;

			if (NoteType == SysMes) {

				UAnalysisPluginBPLibrary::GetSysMessage(Binary, index, SysMesType, DataBytes, index);
				note.SystemMessage = SysMesType;
				note.DataBytes = DataBytes;

				if (SysMesType == ResetMeta) {

					UAnalysisPluginBPLibrary::GetMetaEvent(Binary, index, MetaEventType, DataBytes, index);
					note.MetaEvent = MetaEventType;
					note.DataBytes = DataBytes;

				}
				else {
					note.MetaEvent = FMidiMetaEvents::NaME;
				}
			}
			else {
				note.SystemMessage = FMidiSysMessages::NaSM;
				note.MetaEvent = FMidiMetaEvents::NaME;
			}

			if ((NoteType != NaN) && (MetaEventType != EndOfTrack)) {

				tick = tick + tickDelta;
				note.DeltaTime = tickDelta;
				note.TickTime = tick;

				// value of tick delta is stored for next time. this value is for the distance to the next note, thats why im using the previous dick delta for the calculation
				UAnalysisPluginBPLibrary::GetTickDelta(Binary, index, tickDelta, index);
			}

			noteArray.Add(note);

		}
		Tracks[i].TrackData = noteArray;

	}
	MidiTracks = Tracks;
}