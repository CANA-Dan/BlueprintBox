// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "BlueprintBoxMIDI.h"

void UBlueprintBoxMIDI::ImportBinaryFromDisk(FString Path, TArray<uint8>& ArrayOfBytes, FString& ErrorLog)
{
	FText error;

	if (!FFileHelper::IsFilenameValidForSaving(Path, error)) {
		ErrorLog = "Error";
		return;

	}
	FFileHelper::LoadFileToArray(ArrayOfBytes, *Path);
	ErrorLog = "Success";
}


int64 UBlueprintBoxMIDI::ByteArrayToInt(const TArray<uint8> ArrayOfBytes, bool BigEndian, bool Signed)
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

FString UBlueprintBoxMIDI::ByteToChar(uint8 Byte)
{
	FString Char = " ";
	Char[0] = char(Byte);
	return Char;
}

bool UBlueprintBoxMIDI::IsValidChar(const uint8 Byte, bool CheckIfChar, bool CheckIfInt, bool CheckIfCommonSpecialCharacter, bool CheckIfUncommonSpecialCharacter, TArray<FString> AdditionalCharacters)
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

void UBlueprintBoxMIDI::ProvideMidiChunks(const TArray<uint8> ArrayOfBytes, FMidiStruct& MetaData, TArray<FMidiChunk>& Chunk)
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

				}
				else {
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

void UBlueprintBoxMIDI::GetTickDelta(const TArray<uint8> ArrayOfBytes, int32 StartIndex, int32& TickDelta, int32& NewIndex)
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

void UBlueprintBoxMIDI::GetMidiType(const TArray<uint8> ArrayOfBytes, int32 StartIndex, TEnumAsByte<FMidiNoteType>& DataType, TArray<uint8>& DataReturn, int32& Channel, int32& NewIndex)
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

void UBlueprintBoxMIDI::GetSysMessage(const TArray<uint8> ArrayOfBytes, int32 StartIndex, TEnumAsByte<FMidiSysMessages>& DataType, TArray<uint8>& DataReturn, int32& NewIndex)
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

void UBlueprintBoxMIDI::GetMetaEvent(const TArray<uint8> ArrayOfBytes, const int32 StartIndex, TEnumAsByte<FMidiMetaEvents>& DataType, TArray<uint8>& DataReturn, int32& NewIndex) {

	int index = StartIndex + 1;
	uint8 Type = ArrayOfBytes[index];
	index = StartIndex + 2;
	switch (Type) {
	case 0:
	{
		DataType = SequenceNum;
		int DataLength = 0;
		int nah = 0;
		UBlueprintBoxMIDI::GetTickDelta(ArrayOfBytes, index, DataLength, nah);
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
		UBlueprintBoxMIDI::GetTickDelta(ArrayOfBytes, index, DataLength, nah);
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
		UBlueprintBoxMIDI::GetTickDelta(ArrayOfBytes, index, DataLength, nah);
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
		UBlueprintBoxMIDI::GetTickDelta(ArrayOfBytes, index, DataLength, nah);
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
		UBlueprintBoxMIDI::GetTickDelta(ArrayOfBytes, index, DataLength, nah);
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
		UBlueprintBoxMIDI::GetTickDelta(ArrayOfBytes, index, DataLength, nah);
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
		UBlueprintBoxMIDI::GetTickDelta(ArrayOfBytes, index, DataLength, nah);
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
		UBlueprintBoxMIDI::GetTickDelta(ArrayOfBytes, index, DataLength, nah);
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
		UBlueprintBoxMIDI::GetTickDelta(ArrayOfBytes, StartIndex + 2, DataLength, nah);
		for (int i = 0; i < DataLength; i++) {
			DataReturn.Add(ArrayOfBytes[index + i + 1]);
		}
		NewIndex = index + 1 + DataLength;
		return;
	}
	}
}

void UBlueprintBoxMIDI::ImportMidi(FString MidiFileLocation, FString& ErrorLog, FMidiStruct& MetaData, TArray<FMidiTrack>& MidiTracks)
{
	TArray<uint8> bytes;

	TArray<FMidiChunk> chunks;
	UBlueprintBoxMIDI::ImportBinaryFromDisk(MidiFileLocation, bytes, ErrorLog);

	UBlueprintBoxMIDI::ProvideMidiChunks(bytes, MetaData, chunks);

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

			UBlueprintBoxMIDI::GetMidiType(Binary, index, NoteType, DataBytes, channel, index);
			note.Note = NoteType;
			note.Channel = channel;
			note.DataBytes = DataBytes;

			if (NoteType == SysMes) {

				UBlueprintBoxMIDI::GetSysMessage(Binary, index, SysMesType, DataBytes, index);
				note.SystemMessage = SysMesType;
				note.DataBytes = DataBytes;

				if (SysMesType == ResetMeta) {

					UBlueprintBoxMIDI::GetMetaEvent(Binary, index, MetaEventType, DataBytes, index);
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
				UBlueprintBoxMIDI::GetTickDelta(Binary, index, tickDelta, index);
			}

			noteArray.Add(note);

		}
		Tracks[i].TrackData = noteArray;

	}
	MidiTracks = Tracks;
}