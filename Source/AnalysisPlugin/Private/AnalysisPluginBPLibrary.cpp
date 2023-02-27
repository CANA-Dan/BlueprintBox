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
			case Separated: {

				int TempLength = MainSpectrogram.Num() / 2;
				TArray<float> ChannelLeft = {};

				ChannelLeft.SetNumZeroed(TempLength);
				for (int i = 0; i < TempLength; i++) {
					ChannelLeft[i] = MainSpectrogram[i * 2];
				}

				ChannelLeft;
				UAnalysisPluginBPLibrary::CalculateFFT(ChannelLeft, NumChannels, SampleRate, ChannelLeft, WarningOut);

				int32 MainSpectrogramLen = ChannelLeft.Num();
				for (int32 FrequencyIndex = 0; FrequencyIndex < MainSpectrogramLen; FrequencyIndex++) {

					if (FrequencyIndex >= BandsMin) {

						if (FrequencyIndex <= BandsMax) {

							float MainSpectrogramVal = clampRange(ChannelLeft[FrequencyIndex], 10.f, 0.0f);

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

				TArray<float> ChannelRight = {};

				ChannelRight.SetNumZeroed(TempLength);
				for (int i = 0; i < TempLength; i++) {
					ChannelRight[i] = MainSpectrogram[(i * 2) + 1];
				}

				MainSpectrogram = ChannelRight;
				UAnalysisPluginBPLibrary::CalculateFFT(ChannelRight, NumChannels, SampleRate, ChannelRight, WarningOut);

				MainSpectrogramLen = ChannelRight.Num();
				for (int32 FrequencyIndex = 0; FrequencyIndex < MainSpectrogramLen; FrequencyIndex++) {

					if (FrequencyIndex >= BandsMin) {

						if (FrequencyIndex <= BandsMax) {

							float MainSpectrogramVal = clampRange(ChannelRight[FrequencyIndex], 10.f, 0.0f);

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
			case SeparatedFlipped: {

				int TempLength = MainSpectrogram.Num() / 2;
				TArray<float> ChannelRight = {};

				ChannelRight.SetNumZeroed(TempLength);
				for (int i = 0; i < TempLength; i++) {
					ChannelRight[i] = MainSpectrogram[(i * 2) + 1];
				}

				ChannelRight;
				UAnalysisPluginBPLibrary::CalculateFFT(ChannelRight, NumChannels, SampleRate, ChannelRight, WarningOut);

				int32 MainSpectrogramLen = ChannelRight.Num();
				for (int32 FrequencyIndex = 0; FrequencyIndex < MainSpectrogramLen; FrequencyIndex++) {

					if (FrequencyIndex >= BandsMin) {

						if (FrequencyIndex <= BandsMax) {

							float MainSpectrogramVal = clampRange(ChannelRight[FrequencyIndex], 10.f, 0.0f);

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

				TArray<float> ChannelLeft = {};

				ChannelLeft.SetNumZeroed(TempLength);
				for (int i = 0; i < TempLength; i++) {
					ChannelLeft[i] = MainSpectrogram[i * 2];
				}

				MainSpectrogram = ChannelLeft;
				UAnalysisPluginBPLibrary::CalculateFFT(ChannelLeft, NumChannels, SampleRate, ChannelLeft, WarningOut);

				MainSpectrogramLen = ChannelLeft.Num();
				for (int32 FrequencyIndex = 0; FrequencyIndex < MainSpectrogramLen; FrequencyIndex++) {

					if (FrequencyIndex >= BandsMin) {

						if (FrequencyIndex <= BandsMax) {

							float MainSpectrogramVal = clampRange(ChannelLeft[FrequencyIndex], 10.f, 0.0f);

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
				for (int32 i = Start; i <= End; i++) {

					TempPixels[i] = WhitePixel;
				}

				Pixels.Append(TempPixels);
			}
			else {
				for (int32 i = End; i <= Start; i++) {

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
//											Sorting Stuff
//======================================================================================================================

//helper function to get the specific transfrom type requested.
//float getTransform(AActor* ActorRef, FActorTransform SortingAxis) {
//	switch (SortingAxis) {
//		case LocationX:
//		{
//			return ActorRef->GetActorLocation().X;
//		}
//		case LocationY:
//		{
//			return ActorRef->GetActorLocation().Y;
//		}
//		case LocationZ:
//		{
//			return ActorRef->GetActorLocation().Z;
//		}
//		case RotationX:
//		{
//			return ActorRef->GetActorRotation().Vector().X;
//		}
//		case RotationY:
//		{
//			return ActorRef->GetActorRotation().Vector().Y;
//		}
//		case RotationZ:
//		{
//			return ActorRef->GetActorRotation().Vector().Z;
//		}
//		case ScaleX:
//		{
//			return ActorRef->GetActorScale().X;
//		}
//		case ScaleY:
//		{
//			return ActorRef->GetActorScale().Y;
//		}
//		case ScaleZ:
//		{
//			return ActorRef->GetActorScale().Z;
//		}
//	}
//	return 0.0;
//}
//
//int64 GetDigitAtColumn(int64 num, int32 column) {
//	int64 DigitAtColumn = floorl(long double(num) / powl(10, double(column)));
//	return DigitAtColumn - floorl((long double(DigitAtColumn) * 0.1)) * 10;
//}
//
//TArray<AActor*> UAnalysisPluginBPLibrary::RadixSortActorsTransform(TArray<AActor*> ActorArray, FActorTransform SortingAxis, int64 accuracy)
//{
//	TArray<AActor*> RadixActorArray = ActorArray;
//	TArray<AActor*> TempActorArray = ActorArray;
//	int DigitLength = 1;
//	
//	int32 TotalItems = RadixActorArray.Num();
//	long double HighestVal = 0.0;
//	double transform = 0.0;
//
//	//find the highest value
//	for (int32 i = 0; i < TotalItems; i++) {
//
//		transform = getTransform(RadixActorArray[i], SortingAxis);
//		if (transform > HighestVal) {
//			HighestVal = transform;
//		}
//	}
//
//	HighestVal = HighestVal * accuracy;
//
//	//find how many digits the value is
//	while (HighestVal > 1.0) {
//		HighestVal = HighestVal * 0.1;
//		DigitLength++;
//	}
//	
//	//the main for loop
//	TArray<int32> RadixSortCounter;
//	for (int ForLoop = 0; ForLoop <= DigitLength; ForLoop++) {
//		RadixSortCounter.Empty();
//		RadixSortCounter.SetNum(10);
//
//		//find how many of each digit.
//		for (int32 j = 0; j < TotalItems; j++) {
//			transform = getTransform(RadixActorArray[j], SortingAxis) * accuracy;
//			RadixSortCounter[GetDigitAtColumn(int64(transform), ForLoop)] = RadixSortCounter[GetDigitAtColumn(int64(transform), ForLoop)]++;
//		}
//
//		// cant remember what this does, but something important im sure
//		for (int index = 1; index <= 9; index++) {
//			RadixSortCounter[index] = RadixSortCounter[index] + RadixSortCounter[index - 1];
//		}
//
//		//the for loop for sorting each digit into its bins
//		for (int32 i = 0; i < TotalItems; i++) {
//
//			transform = getTransform(RadixActorArray[i], SortingAxis);
//			RadixSortCounter[GetDigitAtColumn(int64(transform), ForLoop)] = RadixSortCounter[GetDigitAtColumn(int64(transform), ForLoop)]--;
//			int32 arrayindex = RadixSortCounter[GetDigitAtColumn(int64(transform), ForLoop)];
//			TempActorArray[arrayindex] = RadixActorArray[i];
//		}
//		RadixActorArray = TempActorArray;
//	}
//
//	return RadixActorArray;
//}

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

void systemMessages(TArray<uint8> ArrayOfBytes, FMidiStruct& MidiChunk, int32 i, TArray<uint8> param1, int32 offset) {
	TArray<uint8> param2;
	param2.SetNum(param1.Num());
	param2 = { ArrayOfBytes[offset - 1], ArrayOfBytes[offset] };

	if (param1 == param2) {
		int32 Len = ArrayOfBytes[offset + 1];
		FString name;
		for (int i = 0; i < Len; i++) {
			name = name + UAnalysisPluginBPLibrary::ByteToChar(ArrayOfBytes[offset + 2 + i]);
		}
		MidiChunk.ChunkArray[i];
	}
}

void UAnalysisPluginBPLibrary::ProvideMidiChunks(TArray<uint8> ArrayOfBytes, FMidiStruct& MidiChunk)
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
				MidiChunk.Format = FMidiFormat(ByteArrayToInt(Array, true, false));
				hO += len;

				//how many midi tracks this file contains
				len = 2;
				Array.SetNum(len);
				for (int j = 0; j < len; j++) {
					Array[j] = ArrayOfBytes[hO + j];
				}
				MidiChunk.TrackCount = ByteArrayToInt(Array, true, false);
				hO += len;

				//expected values are 192, 128, 96 or something.
				len = 2;
				Array.SetNum(len);

				if (ArrayOfBytes[hO] <= 127) {
					//this is ticks
					for (int j = 0; j < len; j++) {
						Array[j] = ArrayOfBytes[hO + j];
					}
					MidiChunk.Division = ByteArrayToInt(Array, true, false);
					MidiChunk.DivisionType = Ticks;

				} else {
					//this is SMTPE frames
					//left byte is converted to signed (should be a value like -24, -25, -29, or -30) then is converted to positive and multiplied by the ticks per frame value.
					//25 * 40 for example gives the value of 1ms per tick

					MidiChunk.Division = (int8(ArrayOfBytes[hO]) * -1) * ArrayOfBytes[hO];
					MidiChunk.DivisionType = SMTPEframes;
				}

				//just to be sure the location we are going to is the next header
				Index = i + headerLen;

				break;
			};
		}
	}

	MidiChunk.ChunkArray.SetNum(MidiChunk.TrackCount);

	//system exclusive events. each one should be self explanitory. used this for refernce. scroll down to events http://midi.mathewvp.com/aboutMidi.html or http://personal.kent.edu/~sbirch/Music_Production/MP-II/MIDI/midi_file_format.htm
	TArray<uint8> ChunkEnd = { 255, 47, 0 };

	TArray<uint8> ChunkText = { 255, 1 };
	TArray<uint8> ChunkCopyright = { 255, 2 };
	TArray<uint8> ChunkTrackName = { 255, 3 };
	TArray<uint8> ChunkInstrument = { 255, 4 };
	TArray<uint8> ChunkLyric = { 255, 5 };
	TArray<uint8> ChunkMarker = { 255, 6 };
	TArray<uint8> ChunkCuePoint = { 255, 7 };

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
		if (ChunkIndex < MidiChunk.TrackCount) {

			MidiChunk.ChunkArray[ChunkIndex].MIDIBinary.Add(ArrayOfBytes[i]);
		}
		
	}
}

void UAnalysisPluginBPLibrary::GetNotes(const TArray<uint8> ArrayOfBytes, FMidiNote& MidiNotes)
{
}

