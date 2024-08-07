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
		const FMatrix& Matrix = Transforms[Index].ToMatrixWithScale();

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

//all three functions below are pulled from the Simple noise generators plugin, but its using a bad random value algorithum, and it doesnt provide very accurate prelin noise at high scales
//Perlin Noise 1D
float UBlueprintBoxRandomJunk::PerlinNoise1D(float X, float Scale, int32 Seed)
{
	if (Scale <= 0.f) Scale = 0.01f;
	if (X == 0.f) X = 0.01f;

	// Generate pseudo-random offsets from the seed
	srand(Seed);
	double OffsetX = rand();

	// Adjust coordinates based on scale and apply the offsets
	double AdjustedX = (X / Scale) + OffsetX;

	// Generate Perlin noise value
	double NoiseValue = FMath::PerlinNoise2D(FVector2D(AdjustedX, 1.0f)) * 2;

	return NoiseValue;
}

float UBlueprintBoxRandomJunk::PerlinNoise2D(float X, float Y, float Scale, int32 Seed)
{
	// Ensure non-zero values
	if (Scale <= 0.0) Scale = 0.001;
	if (X == 0.0) X = 0.001;
	if (Y == 0.0) Y = 0.001;

	// Generate pseudo-random offsets from the seed
	srand(Seed);
	double OffsetX = rand();
	double OffsetY = rand();

	// Adjust coordinates based on scale and apply the offsets
	double AdjustedX = (X / Scale) + OffsetX;
	double AdjustedY = (Y / Scale) + OffsetY;

	// Generate Perlin noise value
	double NoiseValue = FMath::PerlinNoise2D(FVector2D(AdjustedX, AdjustedY));

	return NoiseValue;
}

//Perlin Noise 3D
float UBlueprintBoxRandomJunk::PerlinNoise3D(float X, float Y, float Z, float Scale, int32 Seed)
{
	// Ensure non-zero values
	if (Scale <= 0.0) Scale = 0.001;
	if (X == 0.0) X = 0.001;
	if (Y == 0.0) Y = 0.001;
	if (Z == 0.0) Z = 0.001;

	// Generate pseudo-random offsets from the seed
	srand(Seed);
	double OffsetX = rand();
	double OffsetY = rand();
	double OffsetZ = rand();

	// Adjust coordinates based on scale and apply the offsets
	double AdjustedX = (X / Scale) + OffsetX;
	double AdjustedY = (Y / Scale) + OffsetY;
	double AdjustedZ = (Z / Scale) + OffsetZ;

	// Generate Perlin noise value using Unreal's built-in FMath function for 3D
	double NoiseValue = FMath::PerlinNoise3D(FVector(AdjustedX, AdjustedY, AdjustedZ));

	return NoiseValue;
}
