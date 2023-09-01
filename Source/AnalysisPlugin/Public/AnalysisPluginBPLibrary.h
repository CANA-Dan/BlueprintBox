// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AudioAnalysisToolsLibrary.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "GameFramework/Actor.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AnalysisPluginBPLibrary.generated.h"


UENUM(BlueprintType)
enum FGenerationStatus
{

	Loop			UMETA(DisplayName = "Continue Looping"),

	InvalidObject	UMETA(DisplayName = "Objects Failed to Verify"),

	DontLoop		UMETA(DisplayName = "End Reached"),

};

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

	Waveform		UMETA(DisplayName = "Waveform"),

	Spectrogram		UMETA(DisplayName = "Spectrogram"),

};

UENUM(BlueprintType)
enum FActorTransform
{

	LocationX		UMETA(DisplayName = "Location X"),

	LocationY		UMETA(DisplayName = "Location Y"),

	LocationZ		UMETA(DisplayName = "Location Z"),

	RotationX		UMETA(DisplayName = "Rotation X"),

	RotationY		UMETA(DisplayName = "Rotation Y"),

	RotationZ		UMETA(DisplayName = "Rotation Z"),

	ScaleX			UMETA(DisplayName = "Scale X"),

	ScaleY			UMETA(DisplayName = "Scale Y"),

	ScaleZ			UMETA(DisplayName = "Scale Z"),

};

UENUM(BlueprintType)
enum FMidiFormat
{

	Single			UMETA(DisplayName = "Single MIDI Track"),

	Simultanious	UMETA(DisplayName = "Multi Track Simultanious"),

	Sequence		UMETA(DisplayName = "Multi Track Sequentual"),


};

UENUM(BlueprintType)
enum FMidiDivision
{

	Ticks			UMETA(DisplayName = "Ticks"),

	SMTPEframes		UMETA(DisplayName = "SMTPE Frames"),

};

UENUM(BlueprintType)
enum FMidiNoteType
{

	NoteOff			UMETA(DisplayName = "Note Off"),

	NoteOn			UMETA(DisplayName = "Note On"),

	AfterTouch		UMETA(DisplayName = "Key Pressure (Aftertouch)"),

	ControlChange	UMETA(DisplayName = "Control Change"),

	ProgramChange	UMETA(DisplayName = "Program Change"),

	ChannelPressure	UMETA(DisplayName = "Channel Pressure (Aftertouch)"),

	PitchWheel		UMETA(DisplayName = "Pitch Wheel Change"),

	SysMes			UMETA(DisplayName = "System Message"),

	NaN				UMETA(DisplayName = "Null"),
};

UENUM(BlueprintType)
enum FMidiSysMessages
{
	SysEx			UMETA(DisplayName = "System Exclusive (F0)"),

	UndfOne			UMETA(DisplayName = "Undefined 1 (F1)"),

	SongPosPtr		UMETA(DisplayName = "Song Position Pointer (F2)"),

	SongSelect		UMETA(DisplayName = "Song Select (F3)"),

	UndfTwo			UMETA(DisplayName = "Undefined 2 (F4)"),

	UndfThree		UMETA(DisplayName = "Undefined 3 (F5)"),

	TuneRequest		UMETA(DisplayName = "Tune Request (F6)"),

	EndOfSysEx		UMETA(DisplayName = "End of Exclusive (F7)"),

	TimingClock		UMETA(DisplayName = "Timing Clock (F8)"),

	UndfFour		UMETA(DisplayName = "Undefined 4 (F9)"),

	Start			UMETA(DisplayName = "Start (FA)"),

	Continue		UMETA(DisplayName = "Continue (FB)"),

	Stop			UMETA(DisplayName = "Stop (FC)"),

	UndfFive		UMETA(DisplayName = "Undefined 5 (FD)"),

	ActiveSensing	UMETA(DisplayName = "Active Sensing (FE)"),

	ResetMeta		UMETA(DisplayName = "Reset/Meta Event(FF)"),

	NaSM			UMETA(DisplayName = "Null"),
};

UENUM(BlueprintType)
enum FMidiMetaEvents
{
	SequenceNum		UMETA(DisplayName = "Sequence Number"),

	Text			UMETA(DisplayName = "Text Event"),

	Copywrite		UMETA(DisplayName = "Copyright Notice"),

	TrackName		UMETA(DisplayName = "Sequence/Track Name"),

	InstrumentName	UMETA(DisplayName = "Instrument Name"),

	Lyric			UMETA(DisplayName = "Lyric"),

	Marker			UMETA(DisplayName = "Marker"),

	CuePoint		UMETA(DisplayName = "Cue Point"),

	ChannelPrefix	UMETA(DisplayName = "Channel Prefix"),

	EndOfTrack		UMETA(DisplayName = "End of Track"),

	SetTempo		UMETA(DisplayName = "Set Tempo"),

	SMPTEOffset		UMETA(DisplayName = "SMPTE Offset"),

	TimeSig			UMETA(DisplayName = "Time Signature"),

	KeySig			UMETA(DisplayName = "Key Signature"),

	SeqMetaEvent	UMETA(DisplayName = "Sequencer Specific Meta-Event"),

	NaME			UMETA(DisplayName = "Null"),
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

//Output from the delegate. break apart to get the goodies inside.
USTRUCT(BlueprintType)
struct FSpectrogramOutput
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, meta = (ToolTip = "generation status"))
		TEnumAsByte<FGenerationStatus> Status;

		UPROPERTY(BlueprintReadWrite, meta = (ToolTip = "Stick back into the function"))
		int32 ChunkIndex;

		UPROPERTY(BlueprintReadWrite, meta = (ToolTip = "Where in the song this particular chunk is representing in seconds", DisplayName = "Time (Seconds)"))
		int32 Time;

		UPROPERTY(BlueprintReadWrite, meta = (ToolTip = "The texture for this chunk"))
		TWeakObjectPtr<UTexture2D> Texture;

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

USTRUCT(BlueprintType)
struct FMidiChunk
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, meta = (ToolTip = "all the midi binary, including the header and end"))
		TArray<uint8> MIDIBinary;
};

USTRUCT(BlueprintType)
struct FMidiStruct
{
	GENERATED_BODY()
		
		UPROPERTY(BlueprintReadWrite, meta = (ToolTip = "The Type of midi track this is"))
		TEnumAsByte<FMidiFormat> Format;

		UPROPERTY(BlueprintReadWrite, meta = (ToolTip = "How many midi tracks are in this midi file."))
		int32 TrackCount;

		UPROPERTY(BlueprintReadWrite, meta = (ToolTip = "The Type of midi track this is"))
		TEnumAsByte<FMidiDivision> DivisionType;

		UPROPERTY(BlueprintReadWrite, meta = (ToolTip = "The amount of ticks (or frames) per quarter beat"))
		int32 Division;
};

USTRUCT(BlueprintType)
struct FMidiNote
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite)
		TEnumAsByte<FMidiNoteType> Note;

		UPROPERTY(BlueprintReadWrite)
		TEnumAsByte<FMidiSysMessages> SystemMessage;

		UPROPERTY(BlueprintReadWrite)
		TEnumAsByte<FMidiMetaEvents> MetaEvent;

		UPROPERTY(BlueprintReadWrite)
		TArray<uint8> DataBytes;

		UPROPERTY(BlueprintReadWrite)
		int32 DeltaTime;

		UPROPERTY(BlueprintReadWrite)
		int32 TickTime;

		UPROPERTY(BlueprintReadWrite)
		int32 Channel;

};

USTRUCT(BlueprintType)
struct FMidiSystemMessage
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite)
		TEnumAsByte<FMidiSysMessages> SystemMessageType;
	
		UPROPERTY(BlueprintReadWrite)
		TArray<uint8> DataBytes;

		UPROPERTY(BlueprintReadWrite)
		int32 TickDelta;

};

USTRUCT(BlueprintType)
struct FMidiTrack
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite)
		TArray<FMidiNote> TrackData;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGeneratedTextures, FSpectrogramOutput, Output);

UCLASS(BlueprintType, Category = "Analysis Plugin | Core")
class UAnalysisPluginBPLibrary : public UBlueprintFunctionLibrary
{

	GENERATED_BODY()

public:
	
	//======================================================================================================================
	//											FFT Stuff
	//======================================================================================================================

	UPROPERTY(BlueprintAssignable, Category = "Analysis Plugin | Audio Analysis")
		FGeneratedTextures DoneCalculating;
	
	//Used for multithreading and other such internal things. Its EXTREMELY important that you turn this into an object reference.
	//Otherwise, GC may come along and wipe this, thinking its not in use (even tho it is).
	UFUNCTION(BlueprintCallable, Category = "Analysis Plugin | Core")
		static UAnalysisPluginBPLibrary* CreateAnalysisPluginRef();

	//Calculates the frequency spectrum from a given array of samples. Used internaly for "MakeSpectrogramColorArray", but avalible to the user in blueprints.
	//@param Samples - The Samples to use to generate the spectrogram
	//@param Channel - The channel of the sound to calculate.  Specify 0 to combine channels together
	//@param StartTime - The beginning of the window to calculate the spectrum of
	//@param TimeLength - The duration of the window to calculate the spectrum of
	//@return OutSpectrum - The resulting spectrum
	UFUNCTION(BlueprintCallable, Category = "Analysis Plugin | Audio Analysis", DisplayName = "(Internal) Calculate FFT")
		static void CalculateFFT(const TArray<float> samples, const int32 NumChannels, const int32 SampleRate, TArray<float>& OutFrequencies, FString& Warnings);

	//Generates an array of pixels (one second per chunk). Intended to be turned into a texture. Used internaly for "Calculate Spectrogram Async", but avalible to the user in blueprints.
	//@param SpectrogramValues - Input nodes for the fft. Allows you to simplify your setup when it comes to making a thread pool. Best to leave these as constant values once the spectrogram is running.
	//@param ChunkIndex - What index you wish to calculate and generate. This variable should be thread specific.
	//@param ThreadId - Allows you to give the thread calculation offset so that chunks can be generated correctly. Set 0 for a single thread.
	UFUNCTION(BlueprintCallable, Category = "Analysis Plugin | Audio Analysis", DisplayName = "(Internal) Make Spectrogram Color Array")
		static void MakeSpectrogramColorArray(FSpectrogramInput SpectrogramValues, const int32 ChunkIndex, const int32 ThreadId, TEnumAsByte<FGenerationStatus>& ContinueLooping, TArray<FColor>& color);
	
	///Generates an array of pixels (one second per chunk). Intended to be turned into a texture. Used internaly for "Calculate Spectrogram Async", but avalible to the user in blueprints.
	//@param WaveformValues - Input nodes for the waveform. Allows you to simplify your setup when it comes to making a thread pool. Best to leave these as constant values once the waveform is generating.
	//@param ChunkIndex - What index you wish to calculate and generate. This variable should be thread specific.
	//@param ThreadId - Allows you to give the thread calculation offset so that chunks can be generated correctly. Set 0 for a single thread.
	UFUNCTION(BlueprintCallable, Category = "Analysis Plugin | Audio Analysis", DisplayName = "(Internal) Make Waveform Color Array")
		static void MakeWaveformColorArray(FWaveformInput WaveformValues, const int32 ChunkIndex, const int32 ThreadId, TEnumAsByte<FGenerationStatus>& ContinueLooping, TArray<FColor>& color);

	//Allows you to generate a spectrogram texture asynchronously. Take a look on my github for how to set this up (or make a thread pool)
	//Make sure that you leave, at minimum, 1 thread (for the game thread) in order for things to work smoothly in the background. 2 is much more ideal, as it leaves one for your OS.
	// 
	//Because the texture generation must lock the mutex (ie all threads must wait for the opperation to be complete), there is a max cap on how many threads you can run if your textures are large enough and are generated fast enough.
	//My CPU can only handel 13 threads at 1024 by 512 for the spectrogram, and 6 threads at 96 by 1024 for the waveform, before i start to experance lag and stuttering.
	//@param AnalysisPluginRef - reference to "Create Analysis Plugin Ref"
	//@param type - What texture you wish to generate.
	//@param WaveformInput - Input nodes for the waveform. Allows you to simplify your setup when it comes to making a thread pool. Best to leave these as constant values once the spectrogram is running.
	//@param SpectrogramInput - Input nodes for the fft. Allows you to simplify your setup when it comes to making a thread pool. Best to leave these as constant values once the spectrogram is running.
	//@param ChunkIndex - Plug 'Output Chunk Index' that you get from the delegate back in here if you intend to loop across the entire song
	//@param ThreadId - Allows you to give the thread calculation offset so that chunks can be generated correctly.
	UFUNCTION(BlueprintCallable, Category = "Analysis Plugin | Audio Analysis", DisplayName = "Calculate Spectrogram Async")
		static void CalculateSpectrogramAsync(UAnalysisPluginBPLibrary* AnalysisPluginRef, FGenerationType type, FWaveformInput WaveformInput, FSpectrogramInput SpectrogramInput, int32 ChunkIndex, int32 ThreadID);
	
	//======================================================================================================================
	//											Data Stuff
	//======================================================================================================================

	//This uses a somewhat unoptimized radix sorting algorithm to sort actors on any transform. Unpotimized because I made it from scratch, but still way faster than the base sort function in C++. i think.
	//@param SortingAxis - what axis you want to sort by. will sort both positive and negative numbers
	//@param Accuracy - because transforms are floats, this allows you to dial in how accurate deep the radix sorter goes. low values like 1 or 0.1 will be faster but less accurate. high values 100 or 1000 will be slower but more accurate.
	//@param position - acts as a change log of position swaps. this way you can swap other stuff that may be attached to the actor, but not directly contained within.
	UFUNCTION(blueprintcallable, category = "analysis plugin | Data Stuff", displayname = "Radix sort actors transform")
		static TArray<AActor*> RadixSortActorsTransform(TArray<AActor*> ActorArray, FActorTransform SortingAxis, float Accuracy = 1000.f);

	//A programatic way to get actor transform on a specific axis.
	UFUNCTION(blueprintcallable, BlueprintPure, category = "analysis plugin | Data Stuff", displayname = "Get actor transform")
		static float getTransformAxis(AActor* ActorRef, FActorTransform Axis);
	
	template<class TypeFrom, class TypeTo>

	//allows you to cast an entire array all at once
	UFUNCTION(blueprintcallable, category = "analysis plugin | Data Stuff", displayname = "Cast Array")
		static void CastArray(const TArray<TypeFrom*> FromObjArray, TArray<TypeTo*>& ToObjArray);

	//Allows you to find any refernces to an object.
	//Rama made a tutorial on this. Im just grabbing it.
	UFUNCTION(BlueprintCallable, Category = "Analysis Plugin | Data Stuff", DisplayName = "Get Object Reference Count")
		static void GetObjReferences(UObject* Obj, TArray<UObject*>& OutReferencedObjects);

	//Allows you to mark objects for deletion. Im not sure why this isnt implimented in blueprints, but it is now.
	UFUNCTION(BlueprintCallable, Category = "Analysis Plugin | Data Stuff", DisplayName = "Destruct Object")
		static void FreeMem(UObject* Object);

	//======================================================================================================================
	//											MIDI Styff
	//======================================================================================================================

	//Used for importing MIDI, but can be used to import any binary file in theory.
	UFUNCTION(BlueprintCallable, Category = "Analysis Plugin | MIDI Importing", DisplayName = "(Internal) Import Binary From Disk")
		static void ImportBinaryFromDisk(FString Path, TArray<uint8>& ArrayOfBytes, FString& ErrorLog);

	//Allows you to convert an array of bytes into its higher value int counterparts.
	//If you want something like a 16 bit int, then give only 2 bytes. intended to be used up to 56 bit numbers)
	//@param BigEndian - BigEndian is also known as motorola format. Reads the bytes from left to right. Set false to read bytes from right to left (intel format/LittleEndian).
	//@param Signed - Allows you to specifiy if you want the value signed or not. Unsigned means the value returned will always be positive. Signed means that values will overflow properly. If you dont know what you are doing, leave this as false.
	UFUNCTION(BlueprintCallable, Category = "Analysis Plugin | MIDI Importing", DisplayName = "(Internal) Byte Array To Int")
		static int64 ByteArrayToInt(TArray<uint8> ArrayOfBytes, bool BigEndian, bool Signed);

	//Converts a byte into a char. Used to find MIDI Chunk headers, but usable for general binary files.
	UFUNCTION(BlueprintCallable, Category = "Analysis Plugin | MIDI Importing", DisplayName = "(Internal) Byte To Char")
		static FString ByteToChar(uint8 Byte);

	//This function will tell you if something is a character or not. its used for the "Provide Midi Chunk" function, but is avalible to the user in blueprints.
	//@param CheckIfChar - This will check if the byte is any character from "A" to "Z", both upper and lower case.
	//@param CheckIfInt - This will check for any number between 0 and 9.
	//@param CheckIfCommonSpecialCharacter - This will check for all these special characters ! & ( ) - _  ; : ' " , . / ? as well as the space character.
	//@param CheckIfUncommonSpecialCharacter - This will check for all these special characters ` ~ # % ^ * = + [ { ] } \ | < > as well as the "At" symbol (the one used in emails). Blueprints wont show it because of formating.
	//@param additionalCharacters - Any characters you wish to check for specifically that the options above dont cover. If you dont wish to check for anything, make an array without any pins.
	UFUNCTION(BlueprintCallable, Category = "Analysis Plugin | MIDI Importing", DisplayName = "(Internal) Is Valid Character")
		static bool IsValidChar(const uint8 Byte, bool CheckIfChar, bool CheckIfInt, bool CheckIfCommonSpecialCharacter, bool CheckIfUncommonSpecialCharacter, TArray<FString> AdditionalCharacters);

	//Finds and provides midi header data. Note that this includes "MTrk", length, and end of track. This means the chunk length will be 8 longer than the length bytes specify.
	UFUNCTION(BlueprintCallable, Category = "Analysis Plugin | MIDI Importing", DisplayName = "(Internal) Provide Midi Chunks")
		static void ProvideMidiChunks(const TArray<uint8> ArrayOfBytes, FMidiStruct& MetaData, TArray<FMidiChunk>& Chunk);

	//@param ArrayOfBytes - Chunk array goes here.
	//@param StartIndex - This Value should be the index of the byte right after the three bytes of a note or other midi data.
	//@param TickDelta - How many ticks from the previous data value.
	//@param NewIndex - The index of the next piece of data.
	UFUNCTION(BlueprintCallable, Category = "Analysis Plugin | MIDI Importing", DisplayName = "(Internal) Get Tick Delta")
		static void GetTickDelta(const TArray<uint8> ArrayOfBytes, const int32 StartIndex, int32& TickDelta, int32& NewIndex);

	//@param ArrayOfBytes - Chunk array goes here.
	//@param StartIndex - This Value should be the index of the byte right after the three bytes of a note or other midi data.
	//@param DataType - For data type. read here (appendix 1.1) for more information http://www.music.mcgill.ca/~ich/classes/mumt306/StandardMIDIfileformat.html
	//@param NewIndex - The index of the next piece of data, likely the tick delta function.
	//@param ByteReturn - The data to return. check if the length is 0, it is a system message.
	//@param Channel - goes from 0 to 15. Special exception for system messages, which arent tied to channel, and instead are system message type (Song Select, Tune Request, Timing Clock, ect...)
	//@param NewIndex - The index of the next piece of data.
	UFUNCTION(BlueprintCallable, Category = "Analysis Plugin | MIDI Importing", DisplayName = "(Internal) Get Midi Data Type")
		static void GetMidiType(const TArray<uint8> ArrayOfBytes, const int32 StartIndex, TEnumAsByte<FMidiNoteType>& DataType, TArray<uint8>& DataReturn, int32& Channel, int32& NewIndex);

	//@param ArrayOfBytes - Chunk array goes here.
	//@param StartIndex - This Value should be the index of the byte right after the three bytes of a note or other midi data.
	//@param DataType - For data type. read here (appendix 1.1 and 3 - Meta Events) for more information http://www.music.mcgill.ca/~ich/classes/mumt306/StandardMIDIfileformat.html
	//@param NewIndex - The index of the next piece of data, likely the tick delta function.
	//@param DataReturn - The data to return. If the type being returned is System Exclusive, more processing will need to take place as this is custom length data. Meta Events are static sized, but special in their nature. use the Get Meta Events plugin to decode them.
	//@param NewIndex - The index of the next piece of data.
	UFUNCTION(BlueprintCallable, Category = "Analysis Plugin | MIDI Importing", DisplayName = "(Internal) GetSystem Message")
		static void GetSysMessage(const TArray<uint8> ArrayOfBytes, const int32 StartIndex, TEnumAsByte<FMidiSysMessages>& DataType, TArray<uint8>& DataReturn, int32& NewIndex);
	
	//these Events will be stuff like text, bpm changes, lyrics, offset, ect.
	//@param ArrayOfBytes - Chunk array goes here.
	//@param StartIndex - This Value should be the index of the byte right after the three bytes of a note or other midi data.
	//@param DataType - For data type. read here (3 - Meta Events) for more information http://www.music.mcgill.ca/~ich/classes/mumt306/StandardMIDIfileformat.html
	//@param NewIndex - The index of the next piece of data, likely the tick delta function.
	//@param DataLength - the size of the message being sent
	//@param NewIndex - The index of the next piece of data.
	UFUNCTION(BlueprintCallable, Category = "Analysis Plugin | MIDI Importing", DisplayName = "(Internal) Get Meta Event")
		static void GetMetaEvent(const TArray<uint8> ArrayOfBytes, const int32 StartIndex, TEnumAsByte<FMidiMetaEvents>& DataType, TArray<uint8>& DataReturn, int32& NewIndex);
	
	//Gets the midi from disk and provides in a readable format
	//@param ArrayOfBytes - Location to midi file
	//@param StartIndex - This Value should be the index of the byte right after the three bytes of a note or other midi data.
	//@param DataType - For data type. read here (3 - Meta Events) for more information http://www.music.mcgill.ca/~ich/classes/mumt306/StandardMIDIfileformat.html
	//@param NewIndex - The index of the next piece of data, likely the tick delta function.
	//@param DataLength - the size of the message being sent
	//@param NewIndex - The index of the next piece of data.
	UFUNCTION(BlueprintCallable, Category = "Analysis Plugin | MIDI Importing", DisplayName = "Import Midi")
		static void ImportMidi(FString MidiFileLocation, FString& ErrorLog, FMidiStruct& MetaData, TArray<FMidiTrack>& MidiTracks);

protected:

	//spectrogram done all its calculations
	void DoneCalculating_Internal(FSpectrogramOutput output, UAnalysisPluginBPLibrary* Ref);

};
