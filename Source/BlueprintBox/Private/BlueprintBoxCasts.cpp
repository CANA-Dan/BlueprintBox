// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "BlueprintBoxCasts.h"

TSet<FString> UBlueprintBoxCasts::StringArrayToSet(TArray<FString> A)
{
	TSet<FString> Set;
	for (const FString& Element : A) {
		Set.Add(Element);
	}

	return Set;
}

TSet<int32> UBlueprintBoxCasts::IntArrayToSet(TArray<int32> A)
{
	TSet<int32> Set;
	for (const int32& Element : A) {
		Set.Add(Element);
	}

	return Set;
}

TArray<int32> UBlueprintBoxCasts::SetToIntArray(TSet<int32> A)
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

void UBlueprintBoxCasts::RoundMantissa(double A, uint8 L, double& B)
{
	//gets the mounts of digits you want to keep by approximation. eg, 6 * 3.321... is about 19.9
	uint8 b = ceil(L * 3.3219280948873626);
	//52 is within the length of the mantissa in a double
	if (b > 52) {
		return;
	}

	//makes the bit mask. bits accuracy goes from left to right, so this bitmap nulls the end of the mantissa.
	constexpr uint64_t mantissaMask = ((uint64_t)1 << 52) - 1;
	uint64_t keepMask = ~(((uint64_t)1 << (52 - b)) - 1);

	//cast double to uint64
	uint64_t raw;
	std::memcpy(&raw, &A, sizeof(raw));

	// applies the bit mask.
	raw &= (mantissaMask & keepMask) | (~mantissaMask);

	//cast back to double
	double result;
	std::memcpy(&result, &raw, sizeof(result));
	B = result;

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

	for (int i = 0; i < size; i++) {

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

void UBlueprintBoxCasts::SplitTransformArray(TArray<FTransform> in, TArray<FVector>& Location, TArray<FRotator>& Rotation, TArray<FVector>& Scale)
{
	
	//avoiding reserve in the future when i use add
	Location.Reserve(in.Num()); Rotation.Reserve(in.Num()); Scale.Reserve(in.Num());

	for (FTransform Temp : in) {
		Location.Add(Temp.GetLocation());
		Rotation.Add(Temp.GetRotation().Rotator());
		Scale.Add(Temp.GetScale3D());

	}
}

TArray<FBox> UBlueprintBoxCasts::LocationsToBoxs(TArray<FVector> Locations, FVector Scale)
{
	TArray<FBox> TempArray;
	FBox Temp;

	TempArray.Reserve(Locations.Num());
	for (FVector Loc : Locations) {
		TempArray.Add(Temp.BuildAABB(Loc, Scale / 2.f));
	}
	
	return TempArray;
}

TArray<FBox> UBlueprintBoxCasts::TransformsToBoxs(TArray<FTransform> Transforms)
{
	TArray<FBox> TempArray;
	FBox Temp;

	TempArray.Reserve(Transforms.Num());
	for (FTransform Trans : Transforms) {
		TempArray.Add(Temp.BuildAABB(Trans.GetLocation(), Trans.GetScale3D() / 2.f));
	}

	return TempArray;
}

void UBlueprintBoxCasts::SplitBoxArray(TArray<FBox> in, TArray<FVector>& BoxMin, TArray<FVector>& BoxMax)
{
	BoxMin.Reserve(in.Num());
	BoxMax.Reserve(in.Num());

	for (FBox boxy : in) {
		BoxMin.Add(boxy.Min); BoxMax.Add(boxy.Max);
	}

}

TArray<FBox> UBlueprintBoxCasts::MakeBoxArray(TArray<FVector> BoxMin, TArray<FVector> BoxMax)
{
	TArray<FBox> TempArray;
	FBox Temp;
	if (BoxMin.Num() == BoxMax.Num()) {

		TempArray.Reserve(BoxMin.Num());
		for (int i = 0; i < BoxMin.Num(); i++) {
			Temp = FBox(BoxMin[i], BoxMax[i]);
		}

		return TempArray;
	}
	return TArray<FBox> ();
}

TArray<FTransform> UBlueprintBoxCasts::BoxsToTransforms(TArray<FBox> in)
{
	TArray<FTransform> TempArray;
	TempArray.Reserve(in.Num());
	FTransform Temp;

	for (FBox boxy : in) {
		Temp.SetLocation(boxy.GetCenter());
		Temp.GetRotation().MakeFromRotator(FRotator(0,0,0));
		Temp.SetScale3D(boxy.GetSize()/100);

		TempArray.Add(Temp);
	}

	return TempArray;
}


