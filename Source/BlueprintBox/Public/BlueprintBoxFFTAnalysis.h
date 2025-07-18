﻿// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "AudioAnalysisToolsLibrary.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "BlueprintBoxCore.h"
#include "BlueprintBoxFFTAnalysis.generated.h"


UENUM(BlueprintType)
enum FSpectrogramTextureType
{
	Left				UMETA(DisplayName = "Left", ToolTip = "Provides the left audio only"),

	Right				UMETA(DisplayName = "Right", ToolTip = "Provides the right audio only"),

	Combined			UMETA(DisplayName = "Combined", ToolTip = "Merges both left and right into a single texture"),

};

UENUM(BlueprintType)
enum FGenerationType
{

	Waveform			UMETA(DisplayName = "Waveform"),

	FFT					UMETA(DisplayName = "FFT Spectrogram"),

	ContinuiousWavelet	UMETA(DisplayName = "Wavelet Spectrogram"),

};

UENUM(BlueprintType)
enum FSpectralReassignment
{

	Hann				UMETA(DisplayName = "Hann"),

	TimeWeightedHann	UMETA(DisplayName = "Time Weighted Hann"),

	HannDerivative		UMETA(DisplayName = "Derivative Hann"),

};

//Input nodes for the fft. Allows you to simplify your setup when it comes to making a thread pool.
USTRUCT(BlueprintType)
struct FSpectrogramInput
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<UImportedSoundWave> ImportedSoundWave;

	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<UAudioAnalysisToolsLibrary> AudioAnalysisObject;

	//Allows you to tell the function how many threads are going to be used total
	UPROPERTY(BlueprintReadWrite)
	int32 ThreadCount;

	//Determines how many times you wish for the spectrogram to calculate a second. 256 is reccommended.
	UPROPERTY(BlueprintReadWrite)
	int32 SpectrogramSamples;

	//Determines how many bands you wish for the spectrogram to calculate. Value MUST be a multiple of two. 256 is reccommended.
	UPROPERTY(BlueprintReadWrite)
	int32 SpectrogramBands;

	//defines how many bands you wish to chop from the low frequencies of the texture, as a float from 0 to 1. set to 0 to include everything from 0 up.
	UPROPERTY(BlueprintReadWrite)
	float BandsMin;

	//defines how many bands you wish to chop from the high frequencies of the texture, as a float from 0 to 1. set to 1 to include everything from 1 down.
	UPROPERTY(BlueprintReadWrite)
	float BandsMax;

	//Allows you to specify how you want the channels returned.
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<FSpectrogramTextureType> TextureType;
};

//Input nodes for the fft. Allows you to simplify your setup when it comes to making a thread pool.
USTRUCT(BlueprintType)
struct FWaveletInput
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<UImportedSoundWave> ImportedSoundWave;

	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<UAudioAnalysisToolsLibrary> AudioAnalysisObject;

	//Allows you to tell the function how many threads are going to be used total
	UPROPERTY(BlueprintReadWrite)
	int32 ThreadCount;

	//Determines how many times you wish for the spectrogram to calculate a second. 256 is reccommended.
	UPROPERTY(BlueprintReadWrite)
	int32 WaveletSamples;

	//Determines how many bands you wish for the spectrogram to calculate. Value MUST be a multiple of two. 256 is reccommended.
	UPROPERTY(BlueprintReadWrite)
	int32 BandCount;

	//returns the spectrum linearly, rather than naturally log
	UPROPERTY(BlueprintReadWrite)
	bool LinearReturn;

	//defines how many bands you wish to chop from the low frequencies of the texture, as a float from 0 to 1. set to 0 to include everything from 0 up.
	UPROPERTY(BlueprintReadWrite)
	float BandsMin;

	//defines how many bands you wish to chop from the high frequencies of the texture, as a float from 0 to 1. set to 1 to include everything from 1 down.
	UPROPERTY(BlueprintReadWrite)
	float BandsMax;

	//Allows you to specify how you want the channels returned.
	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<FSpectrogramTextureType> TextureType;
};

//Input nodes for the waveform. Allows you to simplify your setup when it comes to making a thread pool.
USTRUCT(BlueprintType)
struct FWaveformInput
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<UImportedSoundWave> ImportedSoundWave;

	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<UAudioAnalysisToolsLibrary> AudioAnalysisObject;

	//Allows you to tell the function how many threads are going to be used total.
	UPROPERTY(BlueprintReadWrite)
	int32 ThreadCount;

	//Determines how often you wish to sample the original sound wave. Values higher than 2^14 will not generate.
	UPROPERTY(BlueprintReadWrite)
	int32 WaveformSampleRate;

	//Determines the audio granularity of the waveform. also determines the texture width. Recommended to be an even number. Values of 256 are recommended.
	UPROPERTY(BlueprintReadWrite)
	int32 WaveformAudioGranularity;

};


USTRUCT(BlueprintType)
struct FSpectrogramTextures
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, meta = (ToolTip = "Where in the song this particular chunk is representing in seconds", DisplayName = "Time (Seconds)"))
	int32 Time;

	UPROPERTY(BlueprintReadWrite, meta = (ToolTip = "The texture for this chunk"))
	TWeakObjectPtr<UTexture2D> Texture;

};

UCLASS(BlueprintType, Category = "Blueprint Box | Audio Analysis")
class BLUEPRINTBOX_API UBlueprintBoxFFT : public UBlueprintBoxCore
{
	
	GENERATED_BODY()

public:

	//Calculates the frequency spectrum using FFT analysis from a given array of samples. Used internaly for "MakeSpectrogramColorArray", but avalible to the user in blueprints.
	//@param Samples - The Samples to use to generate the spectrogram
	//@param NumChannels - how many channels the audio contains. 2 channels max.
	//@param SampleRate - The Sample rate of the audio.
	//@param OutFrequencies - will be the same size as the input array. half of it will be from 0 to the max frequency, and ther other half will be the nyquist freqeucies, which can be discarded
	UFUNCTION(BlueprintCallable, Category = "Blueprint Box | Audio Analysis", DisplayName = "(Internal) Calculate FFT")
	static void CalculateFFT(const TArray<float> samples, const int32 NumChannels, const int32 SampleRate, const UBlueprintBoxCore* Ref, TArray<float>& OutRealFrequencies, TArray<float>& OutImagFrequencies, FString& Warnings);

	//Calculates the frequency spectrum using Wavelet analysis from a given array of samples. Used internaly for "MakeSpectrogramColorArray", but avalible to the user in blueprints.
	//@param Samples - The Samples to use to generate the spectrogram
	//@param NumLevels - descibes how many octaves you want to calulculate. each level adds another band to the analysis
	//@param OutFrequencies - will be the same size as the input array. half of it will be from 0 to the max frequency, and ther other half will be the nyquist freqeucies, which can be discarded.
	//@param LinearReturn - returns the array as a linear set of bands instead of logorithmic, which is normally how it would be returned.
	UFUNCTION(BlueprintCallable, Category = "Blueprint Box | Audio Analysis", DisplayName = "(Internal) Calculate Wavelet")
	static void CalculateWavelet(const TArray<float> samples, const int32 FrequencyCount, const int32 TimeSampling, const int32 NumChannels, const int32 SampleRate, const bool Linear, const bool ToMono, TArray<float>& OutFrequencies, FString& Warnings);

	//Generates an array of pixels (one second per chunk). Intended to be turned into a texture. Used internaly for "Calculate Spectrogram Async", but avalible to the user in blueprints.
	//@param SpectrogramValues - Input nodes for the fft. Allows you to simplify your setup when it comes to making a thread pool. Best to leave these as constant values once the spectrogram is running.
	//@param ChunkIndex - What index you wish to calculate and generate. This variable should be thread specific.
	//@param ThreadId - Allows you to give the thread calculation offset so that chunks can be generated correctly. Set 0 for a single thread.
	UFUNCTION(BlueprintCallable, Category = "Blueprint Box | Audio Analysis", DisplayName = "(Internal) Make FFT Spectrogram Color Array")
	static void MakeFFTColorArray(FSpectrogramInput SpectrogramValues, const int32 ChunkIndex, const int32 ThreadId, const UBlueprintBoxCore* Ref, TEnumAsByte<FGenerationStatus>& ContinueLooping, TArray<uint8>& color);

	///Generates an array of pixels (one second per chunk). Intended to be turned into a texture. Used internaly for "Calculate Spectrogram Async", but avalible to the user in blueprints.
	//@param WaveformValues - Input nodes for the waveform. Allows you to simplify your setup when it comes to making a thread pool. Best to leave these as constant values once the waveform is generating.
	//@param ChunkIndex - What index you wish to calculate and generate. This variable should be thread specific.
	//@param ThreadId - Allows you to give the thread calculation offset so that chunks can be generated correctly. Set 0 for a single thread.
	UFUNCTION(BlueprintCallable, Category = "Blueprint Box | Audio Analysis", DisplayName = "(Internal) Make Waveform Color Array")
	static void MakeWaveformColorArray(FWaveformInput WaveformValues, const int32 ChunkIndex, const int32 ThreadId, TEnumAsByte<FGenerationStatus>& ContinueLooping, TArray<uint8>& color);

	//Generates an array of pixels (one second per chunk). Intended to be turned into a texture. Used internaly for "Calculate Spectrogram Async", but avalible to the user in blueprints.
	//@param SpectrogramValues - Input nodes for the fft. Allows you to simplify your setup when it comes to making a thread pool. Best to leave these as constant values once the spectrogram is running.
	//@param ChunkIndex - What index you wish to calculate and generate. This variable should be thread specific.
	//@param ThreadId - Allows you to give the thread calculation offset so that chunks can be generated correctly. Set 0 for a single thread.
	UFUNCTION(BlueprintCallable, Category = "Blueprint Box | Audio Analysis", DisplayName = "(Internal) Make Wavelet Spectrogram Color Array")
	static void MakeWaveletColorArray(FWaveletInput SpectrogramValues, const int32 ChunkIndex, const int32 ThreadId, TEnumAsByte<FGenerationStatus>& ContinueLooping, TArray<uint8>& color);

	//Allows you to generate a spectrogram texture asynchronously. Take a look on my github for how to set this up (or make a thread pool)
	//Make sure that you leave, at minimum, 1 thread (for the game thread) in order for things to work smoothly in the background. 2 is much more ideal, as it leaves one for your OS.
	// 
	//Because the texture generation must lock the mutex (ie all threads must wait for the opperation to be complete), there is a max cap on how many threads you can run if your textures are large enough and are generated fast enough.
	//My CPU can only handel 13 threads at 1024 by 512 for the spectrogram, and 6 threads at 96 by 1024 for the waveform, before i start to experance lag and stuttering.
	//@param BlueprintBoxRef - reference to "Create Blueprint Box Ref"
	//@param type - What texture you wish to generate.
	//@param WaveformInput - Input nodes for the waveform. Allows you to simplify your setup when it comes to making a thread pool. Best to leave these as constant values once the spectrogram is running.
	//@param FFTSpectrogramInput - Input nodes for the fft function. Allows you to simplify your setup when it comes to making a thread pool. Best to leave these as constant values once the spectrogram is running.
	//@param FFTSpectrogramInput - Input nodes for the wavelet function. Allows you to simplify your setup when it comes to making a thread pool. Best to leave these as constant values once the spectrogram is running.
	//@param ChunkIndex - Plug 'Output Chunk Index' that you get from the delegate back in here if you intend to loop across the entire song
	//@param ThreadId - Allows you to give the thread calculation offset so that chunks can be generated correctly.
	UFUNCTION(BlueprintCallable, meta = (Category = "Blueprint Box | Audio Analysis", DisplayName = "Calculate Spectrogram Async"))
	static void CalculateSpectrogramAsync(UBlueprintBoxCore* CoreRef, FGenerationType type, FWaveformInput WaveformInput, FSpectrogramInput FFTSpectrogramInput, FWaveletInput WaveletSpectrogramInput, int32 ChunkIndex, int32 ThreadID);
};
