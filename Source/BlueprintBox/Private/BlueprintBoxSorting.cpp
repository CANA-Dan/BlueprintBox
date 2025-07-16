// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "BlueprintBoxSorting.h"
#include "GameFramework/Actor.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "Engine/Engine.h"
#include "Components/InstancedStaticMeshComponent.h"
#include <cmath>

//helper function to get the specific transform type requested.
float UBlueprintBoxSorting::getActorAxis(AActor* ActorRef, FActorTransform SortingAxis) {
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

//helper function to get the specific transform type requested.
float UBlueprintBoxSorting::getTransformAxis(FTransform Transform, FActorTransform SortingAxis) {
	switch (SortingAxis) {
	case LocationX:
	{
		return Transform.GetLocation().X;
	}
	case LocationY:
	{
		return Transform.GetLocation().Y;
	}
	case LocationZ:
	{
		return Transform.GetLocation().Z;
	}
	case RotationX:
	{
		return Transform.GetRotation().Vector().X;
	}
	case RotationY:
	{
		return Transform.GetRotation().Vector().Y;
	}
	case RotationZ:
	{
		return Transform.GetRotation().Vector().Z;
	}
	case ScaleX:
	{
		return Transform.GetScale3D().X;
	}
	case ScaleY:
	{
		return Transform.GetScale3D().Y;
	}
	case ScaleZ:
	{
		return Transform.GetScale3D().Z;
	}
	}
	return 0.0;
}

float UBlueprintBoxSorting::getVectorAxis(FVector Vector, FVectorAxis Axis) {
	switch (Axis) {
	case X:
	{
		return Vector.X;
	}
	case Y:
	{
		return Vector.Y;
	}
	case Z:
	{
		return Vector.Z;
	}
	default:
	{
		return 0.f;
	}
	}
}

int64 GetDigitAtColumn(int64 num, int64 column) {
	int64 DigitAtColumn = floor(double(num) / powl(10, double(column)));
	return DigitAtColumn - floor((double(DigitAtColumn) * 0.1l)) * 10;
}

void UBlueprintBoxSorting::RadixSortActorsTransform(TArray<AActor*> ActorArray, FActorTransform SortingAxis, TArray<AActor*>& SortedItems, TArray<int32>& NewIndexes, float Accuracy)
{
	TArray<AActor*> RadixActorArray = ActorArray;
	TArray<AActor*> TempActorArray = ActorArray;
	TArray<int32> NewIndexArr;
	TArray<int32> TempIndexArr;
	NewIndexArr.SetNumUninitialized(TempActorArray.Num());

	int64 DigitLength = 0;

	int32 TotalItems = RadixActorArray.Num();
	double HighestVal = 0.0;
	double LowestVal = 0.0;
	double transform = 0.0;

	//find the highest and lowest value
	for (int32 i = 0; i < TotalItems; i++) {
		NewIndexArr[i] = i;
		transform = getActorAxis(RadixActorArray[i], SortingAxis);
		HighestVal = FGenericPlatformMath::Max<double>(HighestVal, transform);
		LowestVal = FGenericPlatformMath::Min<double>(HighestVal, transform);
	}

	TempIndexArr = NewIndexArr;

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
			transform = (getActorAxis(RadixActorArray[j], SortingAxis) + LowestVal) * Accuracy;
			DigAtColIndex = GetDigitAtColumn(int64(floor(transform)), ForLoop);
			RadixSortCounter[DigAtColIndex] = RadixSortCounter[DigAtColIndex] + 1;
		}

		// cant remember what this does, but something important im sure
		for (int32 index = 1; index <= 9; index++) {
			RadixSortCounter[index] = RadixSortCounter[index] + RadixSortCounter[index - 1];
		}

		int32 Rev = TotalItems - 1;
		//the reverse for loop for sorting each digit into its bins
		for (int32 i = Rev; i >= 0; i--) {

			transform = (getActorAxis(RadixActorArray[i], SortingAxis) + LowestVal) * Accuracy;
			DigAtColIndex = GetDigitAtColumn(int64(floor(transform)), ForLoop);
			RadixSortCounter[DigAtColIndex] = RadixSortCounter[DigAtColIndex] - 1;
			int32 arrayindex = RadixSortCounter[DigAtColIndex];
			TempActorArray[arrayindex] = RadixActorArray[i];
			TempIndexArr[arrayindex] = NewIndexArr[i];
		}

		RadixActorArray = TempActorArray;
		NewIndexArr = TempIndexArr;
	}

	SortedItems = RadixActorArray;
	NewIndexes = NewIndexArr;
}

void UBlueprintBoxSorting::RadixSortISMTransform(UInstancedStaticMeshComponent* ISM, FActorTransform SortingAxis, TArray<int32>& SortedItems, float Accuracy)
{

	TArray<FTransform> RadixInstanceArray;
	int32 num = ISM->GetInstanceCount();
	RadixInstanceArray.SetNum(num);

	for (int i = 0; i < num; i++) {
		ISM->GetInstanceTransform(i, RadixInstanceArray[i], false);
	}

	TArray<FTransform> TempInstanceArray = RadixInstanceArray;
	TArray<int32> NewIndexArr;
	TArray<int32> TempIndexArr;
	NewIndexArr.SetNumUninitialized(TempInstanceArray.Num());

	int64 DigitLength = 0;

	int32 TotalItems = RadixInstanceArray.Num();
	double HighestVal = 0.0;
	double LowestVal = 0.0;
	double transform = 0.0;

	//find the highest and lowest value
	for (int32 i = 0; i < TotalItems; i++) {
		NewIndexArr[i] = i;
		transform = getTransformAxis(RadixInstanceArray[i], SortingAxis);
		HighestVal = FGenericPlatformMath::Max<double>(HighestVal, transform);
		LowestVal = FGenericPlatformMath::Min<double>(HighestVal, transform);
	}

	TempIndexArr = NewIndexArr;

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
			transform = (getTransformAxis(RadixInstanceArray[j], SortingAxis) + LowestVal) * Accuracy;
			DigAtColIndex = GetDigitAtColumn(int64(floor(transform)), ForLoop);
			RadixSortCounter[DigAtColIndex] = RadixSortCounter[DigAtColIndex] + 1;
		}

		// cant remember what this does, but something important im sure
		for (int32 index = 1; index <= 9; index++) {
			RadixSortCounter[index] = RadixSortCounter[index] + RadixSortCounter[index - 1];
		}

		int32 Rev = TotalItems - 1;
		//the reverse for loop for sorting each digit into its bins
		for (int32 i = Rev; i >= 0; i--) {

			transform = (getTransformAxis(RadixInstanceArray[i], SortingAxis) + LowestVal) * Accuracy;
			DigAtColIndex = GetDigitAtColumn(int64(floor(transform)), ForLoop);
			RadixSortCounter[DigAtColIndex] = RadixSortCounter[DigAtColIndex] - 1;
			int32 arrayindex = RadixSortCounter[DigAtColIndex];
			TempInstanceArray[arrayindex] = RadixInstanceArray[i];
			TempIndexArr[arrayindex] = NewIndexArr[i];
		}

		RadixInstanceArray = TempInstanceArray;
		NewIndexArr = TempIndexArr;
	}

	SortedItems = NewIndexArr;
}

void UBlueprintBoxSorting::RadixSortVectors(TArray<FVector> VectorArray, FVectorAxis SortingAxis, TArray<FVector>& SortedItems, TArray<int32>& NewIndexes, float Accuracy)
{
	TArray<FVector> RadixVectorArray = VectorArray;
	TArray<FVector> TempVectorArray = VectorArray;
	TArray<int32> NewIndexArr;
	TArray<int32> TempIndexArr;
	NewIndexArr.SetNumUninitialized(TempVectorArray.Num());

	int64 DigitLength = 0;

	int32 TotalItems = RadixVectorArray.Num();
	double HighestVal = 0.0;
	double LowestVal = 0.0;
	double transform = 0.0;

	//find the highest and lowest value
	for (int32 i = 0; i < TotalItems; i++) {
		NewIndexArr[i] = i;
		transform = getVectorAxis(RadixVectorArray[i], SortingAxis);
		HighestVal = FGenericPlatformMath::Max<double>(HighestVal, transform);
		LowestVal = FGenericPlatformMath::Min<double>(HighestVal, transform);
	}

	TempIndexArr = NewIndexArr;

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
			transform = (getVectorAxis(RadixVectorArray[j], SortingAxis) + LowestVal) * Accuracy;
			DigAtColIndex = GetDigitAtColumn(int64(floor(transform)), ForLoop);
			RadixSortCounter[DigAtColIndex] = RadixSortCounter[DigAtColIndex] + 1;
		}

		// cant remember what this does, but something important im sure
		for (int32 index = 1; index <= 9; index++) {
			RadixSortCounter[index] = RadixSortCounter[index] + RadixSortCounter[index - 1];
		}

		int32 Rev = TotalItems - 1;
		//the reverse for loop for sorting each digit into its bins
		for (int32 i = Rev; i >= 0; i--) {

			transform = (getVectorAxis(RadixVectorArray[i], SortingAxis) + LowestVal) * Accuracy;
			DigAtColIndex = GetDigitAtColumn(int64(floor(transform)), ForLoop);
			RadixSortCounter[DigAtColIndex] = RadixSortCounter[DigAtColIndex] - 1;
			int32 arrayindex = RadixSortCounter[DigAtColIndex];
			TempVectorArray[arrayindex] = RadixVectorArray[i];
			TempIndexArr[arrayindex] = NewIndexArr[i];

		}

		RadixVectorArray = TempVectorArray;
		NewIndexArr = TempIndexArr;
	}

	SortedItems = TempVectorArray;
	NewIndexes = TempIndexArr;
}

void UBlueprintBoxSorting::RadixSortTransforms(TArray<FTransform> TransformArray, FActorTransform SortingAxis, TArray<FTransform>& SortedItems, TArray<int32>& NewIndexes, float Accuracy)
{
	TArray<FTransform> RadixVectorArray = TransformArray;
	TArray<FTransform> TempVectorArray = TransformArray;
	TArray<int32> NewIndexArr;
	TArray<int32> TempIndexArr;
	NewIndexArr.SetNumUninitialized(TempVectorArray.Num());

	int64 DigitLength = 0;

	int32 TotalItems = RadixVectorArray.Num();
	double HighestVal = 0.0;
	double LowestVal = 0.0;
	double transform = 0.0;

	//find the highest and lowest value
	for (int32 i = 0; i < TotalItems; i++) {
		NewIndexArr[i] = i;
		transform = getTransformAxis(RadixVectorArray[i], SortingAxis);
		HighestVal = FGenericPlatformMath::Max<double>(HighestVal, transform);
		LowestVal = FGenericPlatformMath::Min<double>(HighestVal, transform);
	}

	TempIndexArr = NewIndexArr;

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
			transform = (getTransformAxis(RadixVectorArray[j], SortingAxis) + LowestVal) * Accuracy;
			DigAtColIndex = GetDigitAtColumn(int64(floor(transform)), ForLoop);
			RadixSortCounter[DigAtColIndex] = RadixSortCounter[DigAtColIndex] + 1;
		}

		// cant remember what this does, but something important im sure
		for (int32 index = 1; index <= 9; index++) {
			RadixSortCounter[index] = RadixSortCounter[index] + RadixSortCounter[index - 1];
		}

		int32 Rev = TotalItems - 1;
		//the reverse for loop for sorting each digit into its bins
		for (int32 i = Rev; i >= 0; i--) {

			transform = (getTransformAxis(RadixVectorArray[i], SortingAxis) + LowestVal) * Accuracy;
			DigAtColIndex = GetDigitAtColumn(int64(floor(transform)), ForLoop);
			RadixSortCounter[DigAtColIndex] = RadixSortCounter[DigAtColIndex] - 1;
			int32 arrayindex = RadixSortCounter[DigAtColIndex];
			TempVectorArray[arrayindex] = RadixVectorArray[i];
			TempIndexArr[arrayindex] = NewIndexArr[i];

		}

		RadixVectorArray = TempVectorArray;
		NewIndexArr = TempIndexArr;
	}

	SortedItems = TempVectorArray;
	NewIndexes = TempIndexArr;
}

void UBlueprintBoxSorting::CompareStringArrays(TArray<FString> ArrayA, TArray<FString> ArrayB, TArray<FString>& DiffA, TArray<FString>& DiffB, TArray<FString>& Parity)
{
	//making two sets so i can avoid TArray::RemoveAt, which is slow for doing random single item removal
	TArray<FString> Sames;
	TSet<FString> SetA;
	TSet<FString> SetB;

	//makes a set with the strings.
	for (const FString& Element : ArrayA) {
		SetA.Add(Element);
	}
	for (const FString& Element : ArrayB) {
		SetB.Add(Element);
	}


	//checks if a theres a discrepancy, and if there is, remove it from the array and set.
	for (int32 i = ArrayA.Num() - 1; i >= 0; i--) {
		FString string = ArrayA[i];


		if (SetB.Contains(string)) {
			SetA.Remove(string);
			SetB.Remove(string);
			Sames.Add(string);
		}
	}

	Parity = Sames;
	DiffA = SetA.Array();
	DiffB = SetB.Array();
}
