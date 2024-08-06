// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "BlueprintBoxCasts.h"

TSet<FString> UBlueprintBoxCasts::StringToSet(TArray<FString> A)
{
	TSet<FString> Set;
	for (const FString& Element : A) {
		Set.Add(Element);
	}

	return Set;
}

TSet<int32> UBlueprintBoxCasts::IntToSet(TArray<int32> A)
{
	TSet<int32> Set;
	for (const int32& Element : A) {
		Set.Add(Element);
	}

	return Set;
}

TArray<int32> UBlueprintBoxCasts::SetToInt(TSet<int32> A)
{
	return A.Array();
}



TArray<FTransform> UBlueprintBoxCasts::LocToTransform(TArray<FVector> Locations, FRotator DefaultRotation, FVector DefaultScale)
{
	TArray<FTransform> Transforms;
	Transforms.SetNumUninitialized(Locations.Num());

	int32 len = Locations.Num();
	for (int i = 0; i < len; i++) {

		Transforms[i] = FTransform(DefaultRotation, Locations[i], DefaultScale);
	}
	return Transforms;
}

TArray<FTransform> UBlueprintBoxCasts::LocAndScaleToTransform(TArray<FVector> Locations, TArray<FVector> Scale, FRotator DefaultRotation)
{
	int32 size = fmax(Scale.Num(), Locations.Num());
	TArray<FVector> Loc = Locations;
	TArray<FVector> Sca = Scale;
	Loc.SetNumZeroed(size);
	Sca.SetNumZeroed(size);

	TArray<FTransform> Transforms;
	Transforms.SetNumUninitialized(size);

	int32 len = Locations.Num();
	for (int i = 0; i < len; i++) {

		Transforms[i] = FTransform(DefaultRotation, Loc[i], Sca[i]);
	}
	return Transforms;
}

TArray<FVector> UBlueprintBoxCasts::Generatevectors(FVector Spacing, int32 count)
{
	TArray<FVector> ret;
	ret.SetNum(count);
	double X = Spacing.X;
	double Y = Spacing.Y;
	double Z = Spacing.Z;

	for (int i = 0; i < count; i++) {
		ret[i] = FVector(i * X, i * Y, i * Z);
	}

	return ret;
}
