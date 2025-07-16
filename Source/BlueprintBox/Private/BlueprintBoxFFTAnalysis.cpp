
#pragma once
#include "BlueprintBoxFFTAnalysis.h"
#include "tools/kiss_fftnd.h"
#include "AudioAnalysisToolsLibrary.h"
#include "async/Async.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "Engine/Engine.h"
#include "Math/UnrealMathUtility.h"
#include <cmath>


void UBlueprintBoxFFT::CalculateFFT(const TArray<float> samples, const int32 NumChannels, const int32 SampleRate, const UBlueprintBoxCore* Ref, TArray<float>& OutRealFrequencies, TArray<float>& OutImagFrequencies, FString& Warnings)
{
	// Clear the Array before continuing
	OutRealFrequencies.Empty();
	OutImagFrequencies.Empty();

	// Make sure the Number of Channels is NOT 0 or greater than 2
	if (NumChannels == 0 || NumChannels > 2)
	{
		Warnings = "Number of Channels is < 0!";
		return;
	}

	//checks if we actually got any samples
	if (samples.Num() == 0)
	{
		Warnings = "No Samples to calculate";
		return;
	}

	int32 SamplesToRead = samples.Num();

	// Create two 2-dim Arrays for complex numbers | Buffer and Output
	kiss_fft_cpx* Buffer[2] = { 0 };
	kiss_fft_cpx* Output[2] = { 0 };

	SamplesToRead /= NumChannels;

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
		//pregenerated so its not making the hanning stuff every time it loops
		float Hanning = Ref->HannWindow[SampleIndex];

		for (int32 ChannelIndex = 0; ChannelIndex < NumChannels; ChannelIndex++)
		{

			// Use Window function to get a better result for the Data (Hann Window)
			Buffer[ChannelIndex][SampleIndex].r = Hanning * samples[SampleIndex * NumChannels + ChannelIndex];

			Buffer[ChannelIndex][SampleIndex].i = Hanning * samples[SampleIndex * NumChannels + ChannelIndex];
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

	OutRealFrequencies.AddZeroed(SamplesToRead);
	OutImagFrequencies.AddZeroed(SamplesToRead);

	for (int32 SampleIndex = 0; SampleIndex < SamplesToRead; ++SampleIndex)
	{
		float ChannelSumR = 0.f;
		float ChannelSumI = 0.f;

		for (int32 ChannelIndex = 0; ChannelIndex < NumChannels; ++ChannelIndex)
		{

			if (Buffer[ChannelIndex]) {
				// With this we get the actual Frequency value for the frequencies from 0hz to ~22000hz
				//ChannelSum += FMath::Sqrt(FMath::Square(Output[ChannelIndex][SampleIndex].r) + FMath::Square(Output[ChannelIndex][SampleIndex].i));

				ChannelSumR += Output[ChannelIndex][SampleIndex].r;
				ChannelSumI += Output[ChannelIndex][SampleIndex].i;
			}
			
		}
				
		//OutRealFrequencies[SampleIndex] = FMath::Pow(ChannelSum / NumChannels, 0.2);
		OutRealFrequencies[SampleIndex] = ChannelSumR;
		OutImagFrequencies[SampleIndex] = ChannelSumI;
	}

	// Make sure to free up the FFT stuff
	KISS_FFT_FREE(STF);
	
	for (int32 ChannelIndex = 0; ChannelIndex < NumChannels; ++ChannelIndex)
	{
		KISS_FFT_FREE(Buffer[ChannelIndex]);
		KISS_FFT_FREE(Output[ChannelIndex]);
	}

}


inline float ExtractSineWaveComponentHannWindowed(const TArray<float>& InSignal, const float SampleRate, const int NumChannels, const float TargetFrequency, const UBlueprintBoxCore* Ref)
{
	const int32 N = InSignal.Num() / NumChannels;
	if (N <= 0 || SampleRate <= 0 || TargetFrequency <= 0)
	{
		return 0.f;
	}

	// Compute normalized angular frequency
	const float Omega = 2.0f * PI * TargetFrequency / SampleRate;

	// Precompute windowed sums
	float SumCos = 0.0f;
	float SumSin = 0.0f;
	float WindowSum = 0.0f;

	for (int32 n = 0; n < N; ++n)
	{
		for (int32 ChIndex = 0; ChIndex < NumChannels; ++ChIndex)
		{
			const float Angle = Omega * static_cast<float>(n);
			const float Window = 0.5f - 0.5f * FMath::Cos(2.0f * PI * static_cast<float>(n) / static_cast<float>(N - 1)); // Hann window;

			const float CosVal = FMath::Cos(Angle);
			const float SinVal = FMath::Sin(Angle);

			SumCos += InSignal[n] * CosVal * Window;
			SumSin += InSignal[n] * SinVal * Window;
			WindowSum += Window;
		}
	}

	// Normalize (optional but recommended)
	SumCos /= WindowSum;
	SumSin /= WindowSum;


	// Final magnitude
	return FMath::Sqrt(SumCos * SumCos + SumSin * SumSin) * 10;
}

void CalculateDFT(TArray<float> samples, const int32 NumChannels, const int32 SampleRate, const int32 HzMin, const int32 HzMax, const int32 FrequencyBins, const UBlueprintBoxCore* Ref, TArray<float>& OutRealFrequencies, FString& Warnings) {
	
	OutRealFrequencies.Empty();

	const int range = HzMax - HzMin;
	const float binSize = range / FrequencyBins;
	
	for (int i = 0; i < FrequencyBins; i++) {

		const float Frequency = binSize * FMath::Pow(float(i) / float(FrequencyBins), 2.5) * FrequencyBins + HzMin;
		
		//const float Frequency = binSize * i + HzMin;
		//ensures that the smallest needed samples are used for the frequency in question
		const int32 sampleSize = SampleRate / (Frequency / 16);
		if (samples.Num() >= sampleSize) {
			samples.SetNum(sampleSize);
		}

		OutRealFrequencies.Add(ExtractSineWaveComponentHannWindowed(samples, SampleRate, NumChannels, Frequency, Ref));
	}

}

void UBlueprintBoxFFT::CalculateWavelet(const TArray<float> samples,const int32 FrequencyCount,const int32 TimeSampling, int32 NumChannels,const int32 SampleRate,const bool Linear,const bool ToMono,TArray<float>& OutFrequencies, FString& Warnings)
{
	Warnings = "nothing here yet. to do";
}

//allows you to clamp the range of the imput between 2 values
float clampRange(const float Input, const float MaxVal, const float MinVal) {
	return std::min(MaxVal, std::max(Input, MinVal));
}

//Using LowEntryExtendedStandardLibrary's functions for this. it worked super well in blueprints and i wanted to use it again here in C++.
UTexture2D* DataToTexture2D(int32 Width, int32 Height, const void* Src, SIZE_T Count)
{
	//dont know why windows turned this into a macro, but it was messing with stuff
#undef UpdateResource

	UTexture2D* Texture2D = UTexture2D::CreateTransient(Width, Height, EPixelFormat::PF_R8);
	if (Texture2D == nullptr)
	{
		return NULL;
	}
	Texture2D->bNoTiling = true;

#if WITH_EDITORONLY_DATA
	Texture2D->MipGenSettings = TMGS_NoMipmaps;
#endif

#if (ENGINE_MAJOR_VERSION == 4)
	void* TextureData = Texture2D->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(TextureData, Src, Count);
	Texture2D->PlatformData->Mips[0].BulkData.Unlock();

	Texture2D->UpdateResource();
	return Texture2D;
#endif

#if (ENGINE_MAJOR_VERSION == 5)
	void* TextureData = Texture2D->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(TextureData, Src, Count);
	Texture2D->GetPlatformData()->Mips[0].BulkData.Unlock();

	Texture2D->UpdateResource();
	return Texture2D;
#endif

}

UTexture2D* CreateGrayScaleTexture(const int32 Width, const int32 Height, const TArray<uint8>& Pixels)
{
	if ((Pixels.Num() <= 0) || (Width <= 0) || (Height <= 0))
	{
		return NULL;
	}
	return DataToTexture2D(Width, Height, &Pixels[0], Pixels.Num());
}

void UBlueprintBoxFFT::MakeFFTColorArray(FSpectrogramInput SpectrogramValues, const int32 ChunkIndex, const int32 ThreadId, const UBlueprintBoxCore* Ref, TEnumAsByte<FGenerationStatus>& ContinueLooping, TArray<uint8>& color) {

	ContinueLooping = FGenerationStatus::DontLoop;

	if (!(SpectrogramValues.ImportedSoundWave.GetEvenIfUnreachable()->IsValidLowLevel() && SpectrogramValues.AudioAnalysisObject.GetEvenIfUnreachable()->IsValidLowLevel())) {

		ContinueLooping = FGenerationStatus::InvalidObject;
		return;

	}

	TWeakObjectPtr<UImportedSoundWave> ImportedSoundWave = SpectrogramValues.ImportedSoundWave;
	TWeakObjectPtr<UAudioAnalysisToolsLibrary> AudioAnalysisObject = SpectrogramValues.AudioAnalysisObject;

	FSpectrogramTextureType textureType = SpectrogramValues.TextureType;
	int32 ThreadCount = SpectrogramValues.ThreadCount;
	int32 SpectrogramSamples = SpectrogramValues.SpectrogramSamples;
	int32 SpectrogramBands = SpectrogramValues.SpectrogramBands;

	int32 BandsMin = round(SpectrogramBands * SpectrogramValues.BandsMin);
	int32 BandsMax = round(SpectrogramBands * SpectrogramValues.BandsMax * 0.5);
	int32 TextureHeight = (SpectrogramSamples + 1);
	int32 TextureWidth = SpectrogramBands + 1;

	//audio file setup
	int32 SampleRate = ImportedSoundWave.GetEvenIfUnreachable()->GetSampleRate();
	int32 NumChannels = ImportedSoundWave.GetEvenIfUnreachable()->NumChannels;
	float SongLength = ImportedSoundWave.GetEvenIfUnreachable()->GetDuration();

	//never used. just there to make the functions happy.
	FString WarningOut = "";

	// for use in multi threading. this allows you to more easily multi thread the spectrogram
	int32 ThreadLocation = ((ChunkIndex * ThreadCount) + ThreadId);

	//calculates how many bands have already been generated. the actual math is all the way at the bottom
	int32 BandsGenerated = 0;

	// gets the offsets so that time is deadly accurate. 512 samples is 11ms for 44.1 sample rate.
	float MainOffset = (float(SpectrogramBands) / float(SampleRate));



	//creates the chunk size and length in samples
	int32 firstIndex = ThreadLocation * SpectrogramSamples;
	int32 lastIndex = (ThreadLocation + 1) * SpectrogramSamples;
	TArray<uint8> Pixels;

	//lamda to clean up code thats repeated below
	auto SpectrogamStuff = [](TArray<float>& TsamplesR, TArray<float>& TsamplesI, int32 NumChannels, TArray<uint8>& Tpixels, int32& TBMin, int32& TBMax)
	{
		int32 MainSpectrogramLen = TsamplesR.Num();

		for (int32 FrequencyIndex = 0; FrequencyIndex < MainSpectrogramLen; FrequencyIndex++) {

			if (FrequencyIndex >= TBMin) {

				if (FrequencyIndex <= TBMax) {

					float mag = FMath::Sqrt(FMath::Square(TsamplesR[FrequencyIndex]) + FMath::Square(TsamplesI[FrequencyIndex]));

					mag = FMath::Sqrt(FMath::Sqrt(mag / NumChannels));

					float MainSpectrogramVal = clampRange(mag, 10.f, 0.0f);

					uint8 CurrentPixel = round(clampRange(MainSpectrogramVal * 50, 255.f, 0.f));
					Tpixels.Add(CurrentPixel);

				}
				else {
					break;
				}

			}

		}
	};

	//sets up the real and imaginary spectrogram inputs and returns. the only thing used for the input is the real. imaginary is fake numbers. dont be fooled by its very common use in math.
	TArray<float> MainSpectrogramR;
	TArray<float> MainSpectrogramI;

	for (int32 Chunkpart = firstIndex; Chunkpart <= lastIndex; Chunkpart++) {

		int32 TriCounter = 0;

		float StartTime = (float(Chunkpart) / float(SpectrogramSamples)) - MainOffset;
		float EndTime = ((float(NumChannels * SpectrogramBands) / float(SampleRate)) + StartTime) - MainOffset;

		StartTime = FMath::Max(0, StartTime);

		//checking if the location to get is less than the imported sound length
		if (EndTime < SongLength) {
			if (!AudioAnalysisObject.GetEvenIfUnreachable()->IsValidLowLevel()) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("audio analysis object is invalid"));
			}

			if (!ImportedSoundWave.GetEvenIfUnreachable()->IsValidLowLevel()) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("imported soundwave is invalid"));
			}

			AudioAnalysisObject.GetEvenIfUnreachable()->GetAudioByTimeRange(ImportedSoundWave.GetEvenIfUnreachable(), StartTime, EndTime, MainSpectrogramR);

			//ensures the returned FFT is the correct size
			if (MainSpectrogramR.Num() > NumChannels * SpectrogramBands) {
				MainSpectrogramR.SetNumZeroed(NumChannels * SpectrogramBands);
			}

			//zero pads before the start of the song, to remove any smearing.
			int32 RemainingSamples = FMath::Max(0, (NumChannels * SpectrogramBands) - MainSpectrogramR.Num());

			TArray<float> TempArray;
			TempArray.SetNum(RemainingSamples);
			TempArray.Append(MainSpectrogramR);

			MainSpectrogramI = MainSpectrogramR = TempArray;

		}
		else {
			
			EndTime = FMath::Min(SongLength, EndTime);

			MainSpectrogramR.Empty();

			if (!AudioAnalysisObject.GetEvenIfUnreachable()->IsValidLowLevel()) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("audio analysis object is invalid"));
			}

			if (!ImportedSoundWave.GetEvenIfUnreachable()->IsValidLowLevel()) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("imported soundwave is invalid"));
			}

			if (StartTime < SongLength) {
				AudioAnalysisObject.GetEvenIfUnreachable()->GetAudioByTimeRange(ImportedSoundWave.GetEvenIfUnreachable(), StartTime, EndTime, MainSpectrogramR);

			}

			//ensures the fft result is the correct size.
			MainSpectrogramR.SetNumZeroed(NumChannels * SpectrogramBands);
		
			MainSpectrogramI = MainSpectrogramR;
		}

		switch (textureType)
		{
			case Left: {

				int TempLength = MainSpectrogramR.Num() / 2;
				TArray<float> Channel = {};

				Channel.SetNumZeroed(TempLength);
				for (int i = 0; i < TempLength; i++) {
					Channel[i] = MainSpectrogramR[i * 2];
				}

				MainSpectrogramR = Channel;

				UBlueprintBoxFFT::CalculateFFT(MainSpectrogramR, 1, SampleRate, Ref, MainSpectrogramR, MainSpectrogramI, WarningOut);

				SpectrogamStuff(MainSpectrogramR, MainSpectrogramI, 1, Pixels, BandsMin, BandsMax);

				break;
			}
			case Right: {

				int TempLength = MainSpectrogramR.Num() / 2;
				TArray<float> Channel = {};

				Channel.SetNumZeroed(TempLength);
				for (int i = 0; i < TempLength; i++) {
					Channel[i] = MainSpectrogramR[(i * 2) + 1];
				}

				MainSpectrogramR = Channel;

				UBlueprintBoxFFT::CalculateFFT(MainSpectrogramR, 1, SampleRate, Ref, MainSpectrogramR, MainSpectrogramI, WarningOut);

				SpectrogamStuff(MainSpectrogramR, MainSpectrogramI, 1, Pixels, BandsMin, BandsMax);

				break;
			}
			case Combined: {

				//the default behavior, so not much to do here
				UBlueprintBoxFFT::CalculateFFT(MainSpectrogramR, NumChannels, SampleRate, Ref, MainSpectrogramR, MainSpectrogramI, WarningOut);

				//expirimental. kinda works but needs to be combined with fft for best results
				//CalculateDFT(MainSpectrogramR, NumChannels, SampleRate, 1, 22050 / 2, 200, Ref, MainSpectrogramR, WarningOut);

				SpectrogamStuff(MainSpectrogramR, MainSpectrogramI, NumChannels, Pixels, BandsMin, BandsMax);


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

void UBlueprintBoxFFT::MakeWaveformColorArray(FWaveformInput WaveformValues, const int32 ChunkIndex, const int32 ThreadId, TEnumAsByte<FGenerationStatus>& ContinueLooping, TArray<uint8>& color)
{
	ContinueLooping = FGenerationStatus::DontLoop;

	if (!(WaveformValues.ImportedSoundWave.GetEvenIfUnreachable()->IsValidLowLevel() && WaveformValues.AudioAnalysisObject.GetEvenIfUnreachable()->IsValidLowLevel())) {

		ContinueLooping = FGenerationStatus::InvalidObject;

		return;

	}

	//setting up some default values
	TWeakObjectPtr<UImportedSoundWave> ImportedSoundWave = WaveformValues.ImportedSoundWave;
	TWeakObjectPtr<UAudioAnalysisToolsLibrary> AudioAnalysisObject = WaveformValues.AudioAnalysisObject;

	int32 sampleRate = ImportedSoundWave.GetEvenIfUnreachable()->GetSampleRate();
	float songLength = ImportedSoundWave.GetEvenIfUnreachable()->GetDuration();

	int32 waveformSampleRate = sampleRate / WaveformValues.WaveformSampleRate;
	int32 textureWidth = WaveformValues.WaveformAudioGranularity;
	int32 WaveformChunk = (ChunkIndex * WaveformValues.ThreadCount) + ThreadId;

	TArray<uint8> Pixels;
	uint8 WhitePixel = 255;
	TArray<uint8> CleanPixels;
	CleanPixels.SetNumZeroed(textureWidth);
	TArray<uint8> TempPixels;

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

			AudioAnalysisObject.GetEvenIfUnreachable()->GetAudioByTimeRange(ImportedSoundWave.GetEvenIfUnreachable(), startTime, endTime, AudioFrame);

			TempPixels = CleanPixels;

			//getting the first index of the audio frame. this would be faster if i could get specific indexes, but oh well.
			//clip prevention, which i never expected to need.

			float Val = FMath::Clamp(AudioFrame[0],-1.f,1.f);
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


void UBlueprintBoxFFT::MakeWaveletColorArray(FWaveletInput WavletValues, const int32 ChunkIndex, const int32 ThreadId, TEnumAsByte<FGenerationStatus>& ContinueLooping, TArray<uint8>& color)
{

}

//this function is on the secondary thread.
void UBlueprintBoxFFT::CalculateSpectrogramAsync(UBlueprintBoxCore* CoreRef, FGenerationType type, FWaveformInput WaveformInput, FSpectrogramInput FFTSpectrogramInput, FWaveletInput WaveletSpectrogramInput, int32 ChunkIndex, int32 ThreadID) {


	FSpectrogramOutput TempOutput;
	UBlueprintBoxCore* ref = CoreRef;

	if (!(FFTSpectrogramInput.AudioAnalysisObject.GetEvenIfUnreachable()->IsValidLowLevel() && FFTSpectrogramInput.ImportedSoundWave.GetEvenIfUnreachable()->IsValidLowLevel() && ref->IsValidLowLevel()) ||
		!(WaveformInput.AudioAnalysisObject.GetEvenIfUnreachable()->IsValidLowLevel() && WaveformInput.ImportedSoundWave.GetEvenIfUnreachable()->IsValidLowLevel() && ref->IsValidLowLevel())) {

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("main thread invalid"));
		TempOutput.Status = FGenerationStatus::InvalidObject;
		ref->DoneCalculatingFFT_Internal(TempOutput, ref);
		return;
	}

	if ((type == FFT) && (CoreRef->HannDerivativeWindow.Num() != FFTSpectrogramInput.SpectrogramBands)) {
		CoreRef->PrecomputeHannWindows(FFTSpectrogramInput.SpectrogramBands, CoreRef);
	}
	

	switch (type)
	{
		case Waveform:
		{
			AsyncTask(ENamedThreads::AnyThread, [ref, WaveformInput, ChunkIndex, ThreadID, TempOutput]() mutable {

				if (!(WaveformInput.AudioAnalysisObject.GetEvenIfUnreachable()->IsValidLowLevel() && WaveformInput.ImportedSoundWave.GetEvenIfUnreachable()->IsValidLowLevel() && ref->IsValidLowLevel())) {
					FSpectrogramOutput tempoutput;
					tempoutput.Status = FGenerationStatus::InvalidObject;
					ref->DoneCalculatingFFT_Internal(TempOutput, ref);
					return;
				}

				TEnumAsByte<FGenerationStatus> ContinueLooping;
				TArray<uint8> color;
				UImportedSoundWave* audio = WaveformInput.ImportedSoundWave.GetEvenIfUnreachable();

				TempOutput.Time = ((ChunkIndex + 1) * WaveformInput.ThreadCount) + (ThreadID - WaveformInput.ThreadCount + 1);
				if (!(float(TempOutput.Time - 1) < audio->GetDuration())) {
					TempOutput.Status = FGenerationStatus::DontLoop;
					ref->DoneCalculatingFFT_Internal(TempOutput, ref);
					return;
				}

				//running the Waveform function
				UBlueprintBoxFFT::MakeWaveformColorArray(WaveformInput, ChunkIndex, ThreadID, ContinueLooping, color);

				int32 tempChunkIndex = ChunkIndex + 1;
				int32 height = WaveformInput.WaveformAudioGranularity;
				int32 width = color.Num() / height;

				//doing this because i cant be assed to figure out the real size atm.
				//regardless, im not gaining or losing any data by doing this method, so it doesnt matter overall.
				color.SetNumZeroed(height * width);
				TempOutput.Status = ContinueLooping;
				TArray<uint8> ColorArray = color;

				//tried very hard to make this texture creation stuff async. Wasnt able to in the end.
				AsyncTask(ENamedThreads::GameThread, [height, width, tempChunkIndex, ref, TempOutput, ColorArray, ThreadID]() mutable {
					if (ColorArray.Num() > 0) {
						TempOutput.Texture = CreateGrayScaleTexture(height, width, ColorArray);
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

					TempOutput.ThreadID = ThreadID;
					ref->DoneCalculatingFFT_Internal(TempOutput, ref);
					return;
				});
			});
		}
		break;

		case FFT:
		{
			AsyncTask(ENamedThreads::AnyThread, [ref, FFTSpectrogramInput, ChunkIndex, ThreadID, TempOutput]() mutable {
				if (!(FFTSpectrogramInput.AudioAnalysisObject.GetEvenIfUnreachable()->IsValidLowLevel() && FFTSpectrogramInput.ImportedSoundWave.GetEvenIfUnreachable()->IsValidLowLevel() && ref->IsValidLowLevel())) {
					FSpectrogramOutput tempoutput;
					tempoutput.Status = FGenerationStatus::InvalidObject;
					ref->DoneCalculatingFFT_Internal(TempOutput, ref);
					return;
				}

				TEnumAsByte<FGenerationStatus> ContinueLooping;
				TArray<uint8> color;
				UImportedSoundWave* audio = FFTSpectrogramInput.ImportedSoundWave.GetEvenIfUnreachable();

				TempOutput.Time = ((ChunkIndex + 1) * FFTSpectrogramInput.ThreadCount) + (ThreadID - FFTSpectrogramInput.ThreadCount + 1);
				if (!(float(TempOutput.Time - 1) < audio->GetDuration())) {
					TempOutput.Status = FGenerationStatus::DontLoop;
					ref->DoneCalculatingFFT_Internal(TempOutput, ref);
					return;
				}

				//running the main FFT function
				UBlueprintBoxFFT::MakeFFTColorArray(FFTSpectrogramInput, ChunkIndex, ThreadID, ref, ContinueLooping, color);

				int32 tempChunkIndex = ChunkIndex + 1;
				int32 height = FFTSpectrogramInput.SpectrogramSamples + 1;
				int32 width = color.Num() / height;

				//doing this because i cant be assed to figure out the real size atm.
				//regardless, im not gaining or losing any data by doing this method, so it doesnt matter overall.
				color.SetNumZeroed(height * width);
				TempOutput.Status = ContinueLooping;
				TArray<uint8> ColorArray = color;

				//tried very hard to make this texture creation stuff async. Wasnt able to in the end.
				AsyncTask(ENamedThreads::GameThread, [height, width, tempChunkIndex, ref, TempOutput, ColorArray, ThreadID]() mutable {
					if (ColorArray.Num() > 0) {
						TempOutput.Texture = CreateGrayScaleTexture(width, height, ColorArray);
						TempOutput.ChunkIndex = tempChunkIndex;
					}
					else {
						TempOutput.Status = FGenerationStatus::InvalidObject;
						TempOutput.ChunkIndex = tempChunkIndex;
					}
				
					TempOutput.ThreadID = ThreadID;
					ref->DoneCalculatingFFT_Internal(TempOutput, ref);
					return;
					});
				});
		}
		break;

		case ContinuiousWavelet:
		{
			AsyncTask(ENamedThreads::AnyThread, [ref, WaveletSpectrogramInput, ChunkIndex, ThreadID, TempOutput]() mutable {

				if (!(WaveletSpectrogramInput.AudioAnalysisObject.GetEvenIfUnreachable()->IsValidLowLevel() && WaveletSpectrogramInput.ImportedSoundWave.GetEvenIfUnreachable()->IsValidLowLevel() && ref->IsValidLowLevel())) {
					FSpectrogramOutput tempoutput;
					tempoutput.Status = FGenerationStatus::InvalidObject;
					ref->DoneCalculatingFFT_Internal(TempOutput, ref);
					return;
				}

				TEnumAsByte<FGenerationStatus> ContinueLooping;
				TArray<uint8> color;
				UImportedSoundWave* audio = WaveletSpectrogramInput.ImportedSoundWave.GetEvenIfUnreachable();

				TempOutput.Time = ((ChunkIndex + 1) * WaveletSpectrogramInput.ThreadCount) + (ThreadID - WaveletSpectrogramInput.ThreadCount + 1);
				if (!(float(TempOutput.Time - 1) < audio->GetDuration())) {
					TempOutput.Status = FGenerationStatus::DontLoop;
					ref->DoneCalculatingFFT_Internal(TempOutput, ref);
					return;
				}

				//running the main FFT function
				UBlueprintBoxFFT::MakeWaveletColorArray(WaveletSpectrogramInput, ChunkIndex, ThreadID, ContinueLooping, color);

				int32 tempChunkIndex = ChunkIndex + 1;
				int32 height = WaveletSpectrogramInput.BandCount;
				int32 width = WaveletSpectrogramInput.WaveletSamples;

				//doing this because i cant be assed to figure out the real size atm.
				//regardless, im not gaining or losing any data by doing this method, so it doesnt matter overall.
				color.SetNumZeroed(height * width);
				TempOutput.Status = ContinueLooping;
				TArray<uint8> ColorArray = color;

				//tried very hard to make this texture creation stuff async. Wasnt able to in the end.
				AsyncTask(ENamedThreads::GameThread, [height, width, tempChunkIndex, ref, TempOutput, ColorArray, ThreadID]() mutable {
					if (ColorArray.Num() > 0) {
						TempOutput.Texture = CreateGrayScaleTexture(width, height, ColorArray);
						TempOutput.ChunkIndex = tempChunkIndex;
					}
					else {
						TempOutput.Status = FGenerationStatus::InvalidObject;
						TempOutput.ChunkIndex = tempChunkIndex;
					}

					TempOutput.ThreadID = ThreadID;
					ref->DoneCalculatingFFT_Internal(TempOutput, ref);
					return;
					});
				});
		}
	}
}