// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "BlueprintBoxCore.h"
#include "BlueprintBoxMIDI.generated.h"


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

UCLASS(BlueprintType, Category = "Blueprint Box | MIDI Importing")
class BLUEPRINTBOX_API UBlueprintBoxMIDI : public UBlueprintBoxCore
{

	GENERATED_BODY()

public:

	//Used for importing MIDI, but can be used to import any binary file.
	UFUNCTION(BlueprintCallable, Category = "Blueprint Box | MIDI Importing", DisplayName = "(Internal) Import Binary From Disk")
	static void ImportBinaryFromDisk(FString Path, TArray<uint8>& ArrayOfBytes, FString& ErrorLog);

	//Allows you to convert an array of bytes into its higher value int counterparts.
	//If you want something like a 16 bit int, then give only 2 bytes. intended to be used up to 56 bit numbers
	//@param BigEndian - BigEndian is also known as motorola format. Reads the bytes from left to right. Set false to read bytes from right to left (intel format/LittleEndian).
	//@param Signed - Allows you to specifiy if you want the value signed or not. Unsigned means the value returned will always be positive. Signed means that values will overflow properly. If you dont know what you are doing, leave this as false.
	UFUNCTION(BlueprintCallable, Category = "Blueprint Box | MIDI Importing", DisplayName = "(Internal) Byte Array To Int")
	static int64 ByteArrayToInt(TArray<uint8> ArrayOfBytes, bool BigEndian, bool Signed);

	//Converts a byte into a char. Used to find MIDI Chunk headers, but usable for general binary files.
	UFUNCTION(BlueprintCallable, Category = "Blueprint Box | MIDI Importing", DisplayName = "(Internal) Byte To Char")
	static FString ByteToChar(uint8 Byte);

	//This function will tell you if something is a character or not. its used for the "Provide Midi Chunk" function, but is avalible to the user in blueprints.
	//@param CheckIfChar - This will check if the byte is any character from "A" to "Z", both upper and lower case.
	//@param CheckIfInt - This will check for any number between 0 and 9.
	//@param CheckIfCommonSpecialCharacter - This will check for all these special characters ! & ( ) - _  ; : ' " , . / ? as well as the space character.
	//@param CheckIfUncommonSpecialCharacter - This will check for all these special characters ` ~ # % ^ * = + [ { ] } \ | < > as well as the "At" symbol (the one used in emails). Blueprints wont show it because of formating.
	//@param additionalCharacters - Any characters you wish to check for specifically that the options above dont cover. If you dont wish to check for anything, make an array without any pins.
	UFUNCTION(BlueprintCallable, Category = "Blueprint Box | MIDI Importing", DisplayName = "(Internal) Is Valid Character")
	static bool IsValidChar(const uint8 Byte, bool CheckIfChar, bool CheckIfInt, bool CheckIfCommonSpecialCharacter, bool CheckIfUncommonSpecialCharacter, TArray<FString> AdditionalCharacters);

	//Finds and provides midi header data. Note that this includes "MTrk", length, and end of track. This means the chunk length will be 8 longer than the length bytes specify.
	UFUNCTION(BlueprintCallable, Category = "Blueprint Box | MIDI Importing", DisplayName = "(Internal) Provide Midi Chunks")
	static void ProvideMidiChunks(const TArray<uint8> ArrayOfBytes, FMidiStruct& MetaData, TArray<FMidiChunk>& Chunk);

	//@param ArrayOfBytes - Chunk array goes here.
	//@param StartIndex - This Value should be the index of the byte right after the three bytes of a note or other midi data.
	//@param TickDelta - How many ticks from the previous data value.
	//@param NewIndex - The index of the next piece of data.
	UFUNCTION(BlueprintCallable, Category = "Blueprint Box | MIDI Importing", DisplayName = "(Internal) Get Tick Delta")
	static void GetTickDelta(const TArray<uint8> ArrayOfBytes, const int32 StartIndex, int32& TickDelta, int32& NewIndex);

	//@param ArrayOfBytes - Chunk array goes here.
	//@param StartIndex - This Value should be the index of the byte right after the three bytes of a note or other midi data.
	//@param DataType - For data type. read here (appendix 1.1) for more information http://www.music.mcgill.ca/~ich/classes/mumt306/StandardMIDIfileformat.html
	//@param NewIndex - The index of the next piece of data, likely the tick delta function.
	//@param ByteReturn - The data to return. check if the length is 0, it is a system message.
	//@param Channel - goes from 0 to 15. Special exception for system messages, which arent tied to channel, and instead are system message type (Song Select, Tune Request, Timing Clock, ect...)
	//@param NewIndex - The index of the next piece of data.
	UFUNCTION(BlueprintCallable, Category = "Blueprint Box | MIDI Importing", DisplayName = "(Internal) Get Midi Data Type")
	static void GetMidiType(const TArray<uint8> ArrayOfBytes, const int32 StartIndex, TEnumAsByte<FMidiNoteType>& DataType, TArray<uint8>& DataReturn, int32& Channel, int32& NewIndex);

	//@param ArrayOfBytes - Chunk array goes here.
	//@param StartIndex - This Value should be the index of the byte right after the three bytes of a note or other midi data.
	//@param DataType - For data type. read here (appendix 1.1 and 3 - Meta Events) for more information http://www.music.mcgill.ca/~ich/classes/mumt306/StandardMIDIfileformat.html
	//@param NewIndex - The index of the next piece of data, likely the tick delta function.
	//@param DataReturn - The data to return. If the type being returned is System Exclusive, more processing will need to take place as this is custom length data. Meta Events are static sized, but special in their nature. use the Get Meta Events plugin to decode them.
	//@param NewIndex - The index of the next piece of data.
	UFUNCTION(BlueprintCallable, Category = "Blueprint Box | MIDI Importing", DisplayName = "(Internal) Get System Message")
	static void GetSysMessage(const TArray<uint8> ArrayOfBytes, const int32 StartIndex, TEnumAsByte<FMidiSysMessages>& DataType, TArray<uint8>& DataReturn, int32& NewIndex);

	//these Events will be stuff like text, bpm changes, lyrics, offset, ect.
	//@param ArrayOfBytes - Chunk array goes here.
	//@param StartIndex - This Value should be the index of the byte right after the three bytes of a note or other midi data.
	//@param DataType - For data type. read here (3 - Meta Events) for more information http://www.music.mcgill.ca/~ich/classes/mumt306/StandardMIDIfileformat.html
	//@param NewIndex - The index of the next piece of data, likely the tick delta function.
	//@param DataLength - the size of the message being sent
	//@param NewIndex - The index of the next piece of data.
	UFUNCTION(BlueprintCallable, Category = "Blueprint Box | MIDI Importing", DisplayName = "(Internal) Get Meta Event")
	static void GetMetaEvent(const TArray<uint8> ArrayOfBytes, const int32 StartIndex, TEnumAsByte<FMidiMetaEvents>& DataType, TArray<uint8>& DataReturn, int32& NewIndex);

	//Gets the midi from disk and provides in a readable format
	//@param ArrayOfBytes - Location to midi file
	//@param StartIndex - This Value should be the index of the byte right after the three bytes of a note or other midi data.
	//@param DataType - For data type. read here (3 - Meta Events) for more information http://www.music.mcgill.ca/~ich/classes/mumt306/StandardMIDIfileformat.html
	//@param NewIndex - The index of the next piece of data, likely the tick delta function.
	//@param DataLength - the size of the message being sent
	//@param NewIndex - The index of the next piece of data.
	UFUNCTION(BlueprintCallable, Category = "Blueprint Box | MIDI Importing", DisplayName = "Import Midi")
	static void ImportMidi(FString MidiFileLocation, FString& ErrorLog, FMidiStruct& MetaData, TArray<FMidiTrack>& MidiTracks);
};
