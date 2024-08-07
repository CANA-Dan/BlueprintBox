// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "BlueprintBoxCore.h"
#include "BlueprintBoxSorting.generated.h"


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
enum FVectorAxis
{

	X		UMETA(DisplayName = "X"),

	Y		UMETA(DisplayName = "Y"),

	Z		UMETA(DisplayName = "Z"),

};

UCLASS(BlueprintType, Category = "Blueprint Box | Sorting")
class BLUEPRINTBOX_API UBlueprintBoxSorting : public UBlueprintBoxCore
{

	GENERATED_BODY()

public:

	//This uses a somewhat unoptimized radix sorting algorithm to sort actors on any transform. Unpotimized because I made it from scratch, but still way faster than the base sort function in C++. i think.
	//@param SortingAxis - what axis you want to sort by. will sort both positive and negative numbers
	//@param Accuracy - because transforms are floats, this allows you to dial in how accurate deep the radix sorter goes. low values like 1 or 0.1 will be faster but less accurate. high values 100 or 1000 will be slower but more accurate.
	UFUNCTION(blueprintcallable, meta = (category = "Blueprint Box | Sorting", displayname = "Radix sort actors transform"))
	static void RadixSortActorsTransform(TArray<AActor*> ActorArray, FActorTransform SortingAxis, TArray<AActor*>& SortedItems, TArray<int32>& NewIndexes, float Accuracy = 1000.f);

	//This uses a somewhat unoptimized radix sorting algorithm to sort actors on any transform. Unpotimized because I made it from scratch, but still way faster than the base sort function in C++. i think.
	//@param SortingAxis - what axis you want to sort by. will sort both positive and negative numbers
	//@param Accuracy - because transforms are floats, this allows you to dial in how accurate deep the radix sorter goes. low values like 1 or 0.1 will be faster but less accurate. high values 100 or 1000 will be slower but more accurate.
	//@param SortedItems - because instanced static meshes are called based on index, you can intterate thriugh them this way via proxy
	UFUNCTION(blueprintcallable, meta = (category = "Blueprint Box | Sorting", displayname = "Radix sort ISM transform"))
	static void RadixSortISMTransform(UInstancedStaticMeshComponent* ISM, FActorTransform SortingAxis, TArray<int32>& SortedItems, float Accuracy = 1000.f);

	//This uses a somewhat unoptimized radix sorting algorithm to sort vectors on x, y, or z. Unpotimized because I made it from scratch, but still way faster than the base sort function in C++. i think.
	//@param SortingAxis - what axis you want to sort by. will sort both positive and negative numbers
	//@param Accuracy - because Vectors are floats, this allows you to dial in how accurate deep the radix sorter goes. low values like 1 or 0.1 will be faster but less accurate. high values 100 or 1000 will be slower but more accurate.
	//@param NewIndexes - returns the new indexes. allows you to translate any other data accompanying the input vector
	UFUNCTION(blueprintcallable, category = "Blueprint Box | Sorting", displayname = "Radix sort Vectors")
	static void RadixSortVectors(TArray<FVector> VectorArray, FVectorAxis SortingAxis, TArray<FVector>& SortedItems, TArray<int32>& NewIndexes, float Accuracy = 1000.f);

	//Give two string arrays in, and get two string arrays out, each one will contain what is missing from the other.
	//For example ["red", "yellow", "orange", "green", "pink"], ["orange", "red", "blue", "green"] would return ["yellow", "pink"], ["blue"]
	//@param DiffA - returns only the things contained in Array A
	//@param DiffB - returns only the things contained in Array B
	//@param Parity - returns anything that appears in both Array A and Array B
	UFUNCTION(blueprintcallable, category = "Blueprint Box | Sorting", displayname = "Compare String Arrays")
	static void CompareStringArrays(TArray<FString> ArrayA, TArray<FString> ArrayB, TArray<FString>& DiffA, TArray<FString>& DiffB, TArray<FString>& Parity);

	//A programatic way to get actor transform on a specific axis.
	UFUNCTION(blueprintcallable, BlueprintPure, category = "Blueprint Box | Sorting", displayname = "Get Actor axis")
	static float getActorAxis(AActor* ActorRef, FActorTransform Axis);

	//A programatic way to get transform on a specific axis.
	UFUNCTION(blueprintcallable, BlueprintPure, category = "Blueprint Box | Sorting", displayname = "Get Transform axis")
	static float getTransformAxis(FTransform Transform, FActorTransform SortingAxis);

	//A programatic way to get a vector axis
	UFUNCTION(blueprintcallable, BlueprintPure, category = "Blueprint Box | Sorting", displayname = "Get Vector Axis")
	static float getVectorAxis(FVector Vector, FVectorAxis Axis);

};
