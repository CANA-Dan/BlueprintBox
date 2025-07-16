// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "BlueprintBoxRandomJunk.h"
#include "async/Async.h"
#include "UObject/UObjectGlobals.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"
#include "GameFramework/GameUserSettings.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Math/MathFwd.h"


//======================================================================================================================
//											Helper Functions
//======================================================================================================================

double AcosD(double A)
{
	return (180.f) / PI * FMath::Acos(A);
}

double SinD(double A)
{
	return FMath::Sin(PI / (180.f) * A);
}

double CosD(double A)
{
	return FMath::Cos(PI / (180.f) * A);
}

FVector GetAbs(FVector A)
{
	return FVector(FMath::Abs(A.X), FMath::Abs(A.Y), FMath::Abs(A.Z));
}

//======================================================================================================================
//											Random Junk
//======================================================================================================================

void UBlueprintBoxRandomJunk::GetObjReferences(UObject* Obj, TArray<UObject*>& OutReferencedObjects)
{
	if (!Obj || !Obj->IsValidLowLevelFast())
	{
		return;
	}

	TArray<UObject*> ReferredToObjects;             //req outer, ignore archetype, recursive, ignore transient
	FReferenceFinder ObjectReferenceCollector(ReferredToObjects, Obj, false, true, true, false);
	ObjectReferenceCollector.FindReferences(Obj);


	OutReferencedObjects.Append(ReferredToObjects);
}

TArray<bool> UBlueprintBoxRandomJunk::SetCustomDataValues(UInstancedStaticMeshComponent* ISM, TArray<int32> InstanceIndexes, TArray<int32> CustomDataIndexs, TArray<float> CustomDataValue, bool MarkRenderStateDirty)
{
	int32 indexNum = InstanceIndexes.Num();
	int32 CstmNum = CustomDataIndexs.Num();
	TArray<bool> Ret;
	Ret.SetNum(indexNum);
	bool tempA = false;
	bool tempB = false;

	//ensures the values array is the same length as the input indexs
	TArray<float> Values = CustomDataValue;
	Values.SetNum(CstmNum);

	for (int i = 0; i < indexNum; i++) {
		tempA = true;
		tempB = true;

		for (int j = 0; j < CstmNum; j++) {
			tempA = ISM->SetCustomDataValue(InstanceIndexes[i], CustomDataIndexs[j], CustomDataValue[j], false);
			if (!tempA) {
				tempB = false;
			}
		}
		Ret[i] = tempB;
	}

	if (MarkRenderStateDirty) {
		ISM->MarkRenderStateDirty();
	}

	return Ret;
}

TArray<float> UBlueprintBoxRandomJunk::SwapFloats(TArray<float> Input, float A, float B)
{
	TArray<float> Temp = Input;
	int32 len = Temp.Num();
	float tempVal = 0.0;
	for (int32 i = 0; i < len; i++) {
		tempVal = Temp[i];
		if (tempVal == A) {
			tempVal = B;
		}
		else {
			tempVal = A;
		}
		Temp[i] = tempVal;
	}
	return Temp;
}

void UBlueprintBoxRandomJunk::FreeMem(UObject* Object)
{
	//stacked like this because 'IsPendingKill' will throw an exception if it isnt valid. ie, i dont think i can do it on the same line.
	if (IsValid(Object)) {
		Object->UObject::ConditionalBeginDestroy();
	}

}

void UBlueprintBoxRandomJunk::FreeMemArray(TArray<UObject*> Object)
{
	//stacked like this because 'IsPendingKill' will throw an exception if it isnt valid. ie, i dont think i can do it on the same line.
	for (UObject* obj : Object)
	{
		if (IsValid(obj)) {
			obj->UObject::ConditionalBeginDestroy();
		}
	}

}

void FindRecursivlyInternally(TArray<FString>& FileNames, const TCHAR* StartDirectory, const TCHAR* Filename, bool Files, bool Directories, int32 Index)
{

	FString CurrentSearch = FString(StartDirectory) / Filename;
	TArray<FString> Result;
	IFileManager::Get().FindFiles(Result, *CurrentSearch, Files, Directories);


	for (int32 i = 0; i < Result.Num(); i++)
	{
		FileNames.Add(FString(StartDirectory) / Result[i]);
	}

	int32 locIndex = Index;
	locIndex--;
	if (locIndex < 1) {
		return;
	}

	TArray<FString> SubDirs;
	FString RecursiveDirSearch = FString(StartDirectory) / TEXT("*");
	IFileManager::Get().FindFiles(SubDirs, *RecursiveDirSearch, false, true);

	for (int32 SubDirIdx = 0; SubDirIdx < SubDirs.Num(); SubDirIdx++)
	{
		FString SubDir = FString(StartDirectory) / SubDirs[SubDirIdx];
		FindRecursivlyInternally(FileNames, *SubDir, Filename, Files, Directories, locIndex);
	}
}

void FindRecursivly(TArray<FString>& FileNames, const TCHAR* StartDirectory, const TCHAR* Filename, bool Files, bool Directories, int32 Index)
{
	FileNames.Empty();
	FindRecursivlyInternally(FileNames, StartDirectory, Filename, Files, Directories, Index);
}

void UBlueprintBoxRandomJunk::FindFilesDirectories(UBlueprintBoxCore* CoreRef, const FString& StartDirectory, const FString& Wildcard, const int32 RecursionAmount, bool FindFiles, bool FindDirectories, const FFilesDelegate& result)
{

	TArray<FString> FoundFiles;
	FString WildcardTemp = Wildcard;
	FFindFileSucess Status;
	FFilesReturn ret;
	ret.FoundFiles = FoundFiles;

	if (Wildcard.IsEmpty())
	{
		WildcardTemp = TEXT("*.*");
	}

	AsyncTask(ENamedThreads::AnyThread, [CoreRef, StartDirectory, WildcardTemp, FindFiles, FindDirectories, FoundFiles, Status, result, ret, RecursionAmount]() mutable {

		if (!(CoreRef->IsValidLowLevel())) {

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("pointer is invalid"));
			ret.Status = BadObjRefernce;

			AsyncTask(ENamedThreads::GameThread, [FoundFiles, Status, result, ret]()
			{
				result.ExecuteIfBound(ret);
			});
		}

		if (!(IFileManager::Get().DirectoryExists(*StartDirectory))) {

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Directory Doesnt Exist"));
			Status = BadDirectoryName;

			AsyncTask(ENamedThreads::GameThread, [FoundFiles, Status, result, ret]()
			{
				result.ExecuteIfBound(ret);
			});
		}


		FindRecursivly(FoundFiles, *StartDirectory, *WildcardTemp, FindFiles, FindDirectories, RecursionAmount);

		//IFileManager::Get().FindFilesRecursive(FoundFiles, *StartDirectory, *WildcardTemp, FindFiles, FindDirectories, bClearFilenameArray);

		ret.Status = Success;
		ret.FoundFiles = FoundFiles;

		AsyncTask(ENamedThreads::GameThread, [result, ret]()
		{
			result.ExecuteIfBound(ret);
		});
	});

}

//is directly copied from LowEntryExtendedStandardLibrary. all credit goes to them. i just wanted it locally
void GetMousePosition(int32& X, int32& Y)
{
	X = 0;
	Y = 0;

	if (GEngine == nullptr)
	{
		return;
	}

	UGameViewportClient* ViewportClient = GEngine->GameViewport;
	if (ViewportClient == nullptr)
	{
		return;
	}

	FViewport* Viewport = ViewportClient->Viewport;
	if (Viewport == nullptr)
	{
		return;
	}

	int32 MouseX = Viewport->GetMouseX();
	int32 MouseY = Viewport->GetMouseY();
	if ((MouseX < 0) || (MouseY < 0))
	{
		return;
	}

	FIntPoint Size = Viewport->GetSizeXY();
	if ((Size.X <= 0) || (Size.Y <= 0))
	{
		return;
	}
	if ((Size.X < MouseX) || (Size.Y < MouseY))
	{
		return;
	}

	X = MouseX;
	Y = MouseY;
}

void UBlueprintBoxRandomJunk::ScreenSpaceToWorldSpace(UGameUserSettings* GameUserSettings, AActor* Camera, float Height, float FOV, float& WorldSpaceX, float& WorldSpaceY)
{
	//there are minimal comments because i made it, but even i dont understand it. a whole lot of trial and error to get it working

	FVector Location = Camera->GetActorLocation();
	FRotator Rotation = Camera->GetActorRotation();

	UGameUserSettings* Setting = GameUserSettings->GetGameUserSettings();
	FIntPoint ScreenRez = Setting->GetDesktopResolution();
	double ScreenX = ScreenRez.X;
	double ScreenY = ScreenRez.Y;

	int32 TempMouseX = 0;
	int32 TempMouseY = 0;
	GetMousePosition(TempMouseX, TempMouseY);

	//precasting
	double MouseX = TempMouseX;
	double MouseY = TempMouseY;

	double CorrectedFOV = 0.0;
	double DivBy90 = FOV / 90.0;
	double SubBy90 = FOV - 90.0;

	//idk why these constants work. its very likely they are wrong, but they work okay between 60 and 120, which is good enough for me.
	double OddConst = 0.0065;
	if (FMath::FloorToInt(DivBy90 + 0.0001)) {
		OddConst = 0.012;
	}

	CorrectedFOV = DivBy90 * powl(DivBy90, ((SubBy90 * OddConst) + 0.545));

	//checks if its fullscreen windowed or just windowed. full screen i dont really use
	if (Setting->GetFullscreenMode() == EWindowMode::Windowed) {
		ScreenRez = Setting->GetScreenResolution();
		ScreenX = ScreenRez.X;
		ScreenY = ScreenRez.Y;
	}

	//no idea what the following math does. idk. run it through chatGPT for actual comments.

	double VerticalCheck = (((MouseY / ScreenY) - 0.5) * FOV);

	double MouseVertAxis = (ScreenY / ScreenX) * VerticalCheck * 2.0;

	double AxisHyp = hypot(MouseVertAxis, 1.0);

	MouseVertAxis = FMath::Square(MouseVertAxis) - (FMath::Square(AxisHyp) + 1.0);

	MouseVertAxis = MouseVertAxis / (AxisHyp * 2.0);

	MouseVertAxis = AcosD(MouseVertAxis) - 180.0;

	if (VerticalCheck <= 0.0) {
		MouseVertAxis = MouseVertAxis * -1.0;
	}

	double Tempheight = Location.Z - Height;

	double MouseXone = (((MouseY / ScreenY) - 0.5) * FOV) * 2 * CosD(MouseVertAxis);

	double Yaw1 = SinD(Rotation.Yaw * -1.0);

	double VertAndPitch = MouseVertAxis + Rotation.Pitch;

	double MouseYone = SinD(VertAndPitch - 90.0) * Tempheight / SinD(VertAndPitch);

	double MouseXother = MouseXone * VertAndPitch * hypot(MouseYone, Tempheight);

	double RotYaw = CosD(Rotation.Yaw);

	WorldSpaceX = MouseXother + Location.X + (MouseYone * RotYaw);

	double MouseYother = MouseXone * RotYaw * hypot(MouseYone, Tempheight);

	WorldSpaceY = MouseYother + Location.Y + (SinD(Rotation.Yaw) * MouseYone);

}

TArray<FTransform> UBlueprintBoxRandomJunk::GetInstanceTransforms(UInstancedStaticMeshComponent* ISM, bool UsingWorldSpace)
{
	int32 totalInstances = ISM->GetInstanceCount();

	TArray<FTransform> ReturnArray;
	ReturnArray.SetNumUninitialized(totalInstances);
	for (int i = 0; i < totalInstances; i++) {
		ISM->GetInstanceTransform(i, ReturnArray[i], UsingWorldSpace);
	}

	return ReturnArray;
}

TArray<FTransform> UBlueprintBoxRandomJunk::GetInstanceTransformsUsingIndex(UInstancedStaticMeshComponent* ISM, const TArray<int32>& transforms, bool UsingWorldSpace)
{
	TArray<FTransform> ReturnArray;
	FTransform trans;
	for (int32 item : transforms) {
		ISM->GetInstanceTransform(item, trans, UsingWorldSpace);
		ReturnArray.Add(trans);
	}
	return ReturnArray;
}

TArray<int32> UBlueprintBoxRandomJunk::BoxOverlap(const TArray<FTransform>& Transforms, const FBox& Box)
{
	TArray<int32> Result;

	FVector scale;
	FVector loc;

	for (int32 Index = 0; Index < Transforms.Num(); Index++)
	{

		scale = Transforms[Index].GetScale3D() * 50;
		loc = Transforms[Index].GetLocation();

		FBox InstanceBox(loc - scale, loc + scale);

		if (Box.Intersect(InstanceBox))
		{
			Result.Add(Index);
		}
	}

	return Result;
}

bool UBlueprintBoxRandomJunk::IsWithinSphere(float Radius, FVector Center, FVector Point) {
	
	FVector delta = Center - Point;
	delta = FMath::Square(delta);
	double hypt = FMath::Abs(delta.X) + FMath::Abs(delta.Y) + FMath::Abs(delta.Z);
	double rad = FMath::Abs(FMath::Square(Radius));
	
	if (hypt < rad) {
		return true;
	}
	return false;
}

bool UBlueprintBoxRandomJunk::IsWithinBox(FVector Scale, FVector Center, FVector Point)
{
	//gets it relative to zero
	FVector point = GetAbs(Point - Center);
	FVector ScaleCM = Scale * 100;

	if ((point.X <= ScaleCM.X) && (point.Y <= ScaleCM.Y) && (point.Y <= ScaleCM.Y)) {
		return true;
	}
	return false;
}

void UBlueprintBoxRandomJunk::Spiral(int32 n, int32& X, int32& Y)
{
	if (n == 0) { X = 0; Y = 0; return; }
	n = n - 1;

	// Compute the radius of the spiral
	int r = FMath::FloorToInt((FMath::Sqrt(double(n + 1)) - 1) / 2) + 1;

	// Compute p: the sum of points in inner square
	int p = (8 * r * (r - 1)) / 2;

	// Compute side length of the current square's outer side
	int en = r * 2;

	// Compute the position on the current square's edge
	int a = (1 + n - p) % (r * 8);

	// Determine the face (0: top, 1: right, 2: bottom, 3: left) and calculate the position
	switch (a / (r * 2)) {
		case 0:
			X = a - r;  // x coordinate
			Y = -r;     // y coordinate
			break;
		case 1:
			X = r;
			Y = (a % en) - r;
			break;
		case 2:
			X = r - (a % en);
			Y = r;
			break;
		case 3:
			X = -r;
			Y = r - (a % en);
			break;
	}
}

void UBlueprintBoxRandomJunk::ArrayMathInt(const TArray<int32> Input, const TArray<FMathOperation> MathTypes, TArray<int32>& Return)
{
	TArray<int32> ReturnArray;
	ReturnArray.Reserve(Input.Num());

	for (int32 i = 0; i < Input.Num(); i++) {
		int32 Value = Input[i];
		for (FMathOperation Type : MathTypes) {
			switch (Type.Type) {
				case Add:
					Value = int32(Value + Type.Value);
					break;
				case Subtract:
					Value = int32(Value - Type.Value);
					break;
				case Multiply:
					Value = int32(Value * Type.Value);
					break;
				case Divide:
					Value = int32(Value / Type.Value);
					break;
			}
		}
		ReturnArray[i] = Value;
	}
	Return = ReturnArray;
}

void UBlueprintBoxRandomJunk::ArrayMathInt64(const TArray<int64> Input, const TArray<FMathOperation> MathTypes, TArray<int64>& Return)
{
	TArray<int64> ReturnArray;
	ReturnArray.Reserve(Input.Num());

	for (int32 i = 0; i < Input.Num(); i++) {
		int32 Value = Input[i];
		for (FMathOperation Type : MathTypes) {
			switch (Type.Type) {
			case Add:
				Value = int64(Value + Type.Value);
				break;
			case Subtract:
				Value = int64(Value - Type.Value);
				break;
			case Multiply:
				Value = int64(Value * Type.Value);
				break;
			case Divide:
				Value = int64(Value / Type.Value);
				break;
			}
		}
		ReturnArray[i] = Value;
	}
	Return = ReturnArray;
}

void UBlueprintBoxRandomJunk::ArrayMathfloat(const TArray<float> Input, const TArray<FMathOperation> MathTypes, TArray<float>& Return)
{
	TArray<float> ReturnArray;
	ReturnArray.Reserve(Input.Num());

	for (int32 i = 0; i < Input.Num(); i++) {
		int32 Value = Input[i];
		for (FMathOperation Type : MathTypes) {
			switch (Type.Type) {
			case Add:
				Value = Value + Type.Value;
				break;
			case Subtract:
				Value = Value - Type.Value;
				break;
			case Multiply:
				Value = Value * Type.Value;
				break;
			case Divide:
				Value = Value / Type.Value;
				break;
			}
		}
		ReturnArray[i] = Value;
	}
	Return = ReturnArray;
}
