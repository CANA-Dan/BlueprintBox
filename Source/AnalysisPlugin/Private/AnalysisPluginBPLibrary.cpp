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
			AudioAnalysisObject->GetAudioFrameFromSoundWaveByTimeCustom(ImportedSoundWave, StartTime, EndTime, MainSpectrogram);
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

			AudioAnalysisObject->GetAudioFrameFromSoundWaveByTimeCustom(ImportedSoundWave, startTime, endTime, AudioFrame);

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
	if (ArrayOfBytes.Num() > 8) {
		Bytes.SetNum(8, true);
	}
	
	uint64 num = 0;
	int32 len = Bytes.Num() - 1;
	if (BigEndian == false) {
		Algo::Reverse(Bytes);
	}

	for (int32 i = 0; i <= len; i++) {
		num = num + (Bytes[i] * pow(256, len - i));
	}

	if (Signed == false) {
		num = num - pow(2,63);
	}
	return int64(num);
}

FString UAnalysisPluginBPLibrary::ByteArrayToChar(TArray<uint8> ArrayOfBytes, int32 Index)
{
	int32 length = ArrayOfBytes.Num() - 1;
	if (Index > length) {
		return "";
	}
	FString Char;

	Char = ",";
	Char[0] = char(ArrayOfBytes[Index]);
	return Char;
}

void UAnalysisPluginBPLibrary::ProvideMidiChunks(TArray<uint8> ArrayOfBytes, FMidiStruct& MidiChunk)
{
	int32 length = ArrayOfBytes.Num();
	int32 uintToInt = pow(2, 31);

	for (int32 i = 0; i < length; i++) {
		FString Char;
		Char = ",";
		Char = ByteArrayToChar(ArrayOfBytes, i);
		//initial check for if its a midi header.
		if (Char == "M") {
			//actual check for initial midi header. Should be right at the beginning of the file, but, yah know, never can be sure.
			FString FullHeaderCheck = ByteArrayToChar(ArrayOfBytes, i) + ByteArrayToChar(ArrayOfBytes, i + 1) + ByteArrayToChar(ArrayOfBytes, i + 2) + ByteArrayToChar(ArrayOfBytes, i + 3);
			if ("MThd" == FullHeaderCheck) {
				i = i + 4;
				int32 headerLen = 0;
				TArray<uint8> Array;

				int len = 4;
				Array.SetNum(len);
				for (int j = 0; j < len; j++) {
					Array[j] = ArrayOfBytes[i + j];
				}
				headerLen = ByteArrayToInt(Array, true, true);
				i = i + len;

				//midi type. should be a direct conversion. not sure why its 16 bits long when 8 bits would have been fine, but it is.
				len = 2;
				Array.SetNum(len);
				for (int j = 0; j < len; j++) {
					Array[j] = ArrayOfBytes[i + j];
				}
				MidiChunk.Format = FMidiFormat(ByteArrayToInt(Array, true, true));
				i = i + len;

				//how many midi tracks this file contains
				len = 2;
				Array.SetNum(len);
				for (int j = 0; j < len; j++) {
					Array[j] = ArrayOfBytes[i + j];
				}
				MidiChunk.TrackCount = ByteArrayToInt(Array, true, true);
				i = i + len;

				//expected values are 192, 128, 96 or something.
				len = 2;
				Array.SetNum(len);
				for (int j = 0; j < len; j++) {
					Array[j] = ArrayOfBytes[i + j];
				}
				MidiChunk.TimeDivision = ByteArrayToInt(Array, true, true);
				i = i + len;

				//just to be sure the location we are going to is the next header
				i = i - 6 + headerLen;

				break;
			};
		}
	}
}
