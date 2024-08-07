// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "BlueprintBoxCore.h"
#include "BlueprintBoxCasts.generated.h"

UCLASS(BlueprintType, Category = "Blueprint Box | Casts")
class BLUEPRINTBOX_API UBlueprintBoxCasts : public UBlueprintBoxCore
{

	GENERATED_BODY()

public:

	//converts a string array into a string set
	UFUNCTION(blueprintcallable, BlueprintPure, meta = (category = "Blueprint Box | Casts", CompactNodeTitle = "->", BlueprintAutocast))
	static TSet<FString> StringArrayToSet(TArray<FString> A);

	//convert an int32 array into an int32 set
	UFUNCTION(blueprintcallable, BlueprintPure, meta = (category = "Blueprint Box | Casts", CompactNodeTitle = "->", BlueprintAutocast))
	static TSet<int32> IntArrayToSet(TArray<int32> A);

	//convert an set to array
	UFUNCTION(blueprintcallable, BlueprintPure, meta = (category = "Blueprint Box | Casts", CompactNodeTitle = "->", BlueprintAutocast))
	static TArray<int32> SetToIntArray(TSet<int32> A);

	//convert location to a transform
	UFUNCTION(blueprintcallable, meta = (category = "Blueprint Box | Casts", DisplayName = "Location to Transform"))
	static TArray<FTransform> LocToTransform(TArray<FVector> Locations, FRotator DefaultRotation, FVector DefaultScale);

	//convert location and scale to a transform
	//any missing data on one of the arrays will be set to 0
	UFUNCTION(blueprintcallable, meta = (category = "Blueprint Box | Casts", DisplayName = "Location & Scale to Transform"))
	static TArray<FTransform> LocAndScaleToTransform(TArray<FVector> Locations, TArray<FVector> Scale, FRotator DefaultRotation);

	//allows you to make a procedural amount of vectors for testing stuff
	//@param Spacing - allows you to set the spacing of the vectors
	UFUNCTION(blueprintcallable, meta = (category = "Blueprint Box | Casts", DisplayName = "Generate Vectors"))
	static TArray<FVector> Generatevectors(FVector Spacing, int32 count);
};
