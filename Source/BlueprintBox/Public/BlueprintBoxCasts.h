// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "BlueprintBoxCore.h"
#include "BlueprintBoxCasts.generated.h"

UCLASS(BlueprintType, Category = "Blueprint Box | Casts")
class BLUEPRINTBOX_API UBlueprintBoxCasts : public UBlueprintBoxCore
{

	GENERATED_BODY()

public:

	//converts a string array into a string set. Be sure to set to a variable if you indend to pull from more than once.
	UFUNCTION(blueprintcallable, BlueprintPure, meta = (category = "Blueprint Box | Casts", CompactNodeTitle = "->", BlueprintAutocast))
	static TSet<FString> StringArrayToSet(TArray<FString> A);

	//convert an int32 array into an int32 set. Be sure to set to a variable if you indend to pull from more than once.
	UFUNCTION(blueprintcallable, BlueprintPure, meta = (category = "Blueprint Box | Casts", CompactNodeTitle = "->", BlueprintAutocast))
	static TSet<int32> IntArrayToSet(TArray<int32> A);

	//convert an set to array. Be sure to set to a variable if you indend to pull from more than once.
	UFUNCTION(blueprintcallable, BlueprintPure, meta = (category = "Blueprint Box | Casts", CompactNodeTitle = "->", BlueprintAutocast))
	static TArray<int32> SetToIntArray(TSet<int32> A);

	//convert location to a transform
	UFUNCTION(blueprintcallable, meta = (category = "Blueprint Box | Casts", DisplayName = "Location to Transform"))
	static TArray<FTransform> LocToTransform(TArray<FVector> Locations, FRotator DefaultRotation, FVector DefaultScale);

	//allows you to speicfy how long you want the mantissa to be. obviously removes accuracy, so use with care
	//@param L - how many digits you want
	UFUNCTION(blueprintcallable, BlueprintPure, meta = (category = "Blueprint Box | Casts", DisplayName = "Round Mantissa"))
	static void RoundMantissa(double A, uint8 L, double &B);

	//convert location and scale to a transform
	//any missing data on one of the arrays will be set to 0
	UFUNCTION(blueprintcallable, meta = (category = "Blueprint Box | Casts", DisplayName = "Location & Scale to Transform"))
	static TArray<FTransform> LocAndScaleToTransform(TArray<FVector> Locations, TArray<FVector> Scale, FRotator DefaultRotation);

	//allows you to make a procedural amount of vectors for testing stuff
	//@param Spacing - allows you to set the spacing of the vectors
	UFUNCTION(blueprintcallable, meta = (category = "Blueprint Box | Casts", DisplayName = "Generate Vectors"))
	static TArray<FVector> Generatevectors(FVector Spacing, int32 count);

	//WARNING! set the return arrays to variables if you intend to pull from this split/cast more than once. expensive, and nothing is cached because its pure.
	UFUNCTION(blueprintcallable, BlueprintPure, meta = (category = "Blueprint Box | Casts", CompactNodeTitle = "->", BlueprintAutocast))
	static void SplitTransformArray(TArray<FTransform> in, TArray<FVector>& Location, TArray<FRotator>& Rotation, TArray<FVector>& Scale);

	//Allows you to provide an array of Locations and a scale, and get an array of boxes out the other side. meant to scan an arbitrary array of ISM positions for overlaps
	UFUNCTION(blueprintcallable, meta = (category = "Blueprint Box | Casts", DisplayName = "Locations To Boxs"))
	static TArray<FBox> LocationsToBoxs(TArray<FVector> Locations, FVector Scale);

	//Allows you to provide an array of Transforms, and get an array of boxes out the other side. meant to scan an arbitrary array of ISM positions for overlaps.
	//Scale is based off meters, and rotation is always north
	UFUNCTION(blueprintcallable, meta = (category = "Blueprint Box | Casts", DisplayName = "Transforms To Boxs"))
	static TArray<FBox> TransformsToBoxs(TArray<FTransform> Transforms);

	UFUNCTION(blueprintcallable, meta = (category = "Blueprint Box | Casts", DisplayName = "Split Box Array"))
	static void SplitBoxArray(TArray<FBox> in, TArray<FVector>& BoxMin, TArray<FVector>& BoxMax);

	//expects both arrays to be the same length. it will return nothing if they are not the same length
	UFUNCTION(blueprintcallable, meta = (category = "Blueprint Box | Casts", DisplayName = "Make Box Array"))
	static TArray<FBox> MakeBoxArray(TArray<FVector> BoxMin, TArray<FVector> BoxMax);

	//returns all transforms with a rotation of 0,0,0
	UFUNCTION(blueprintcallable, meta = (category = "Blueprint Box | Casts", DisplayName = "Boxes to Transforms"))
	static TArray<FTransform> BoxsToTransforms(TArray<FBox> in);

};
