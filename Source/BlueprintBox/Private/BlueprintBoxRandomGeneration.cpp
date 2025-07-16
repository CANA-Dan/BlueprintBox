// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "BlueprintBoxRandomGeneration.h"
#include "Math/UnrealMathUtility.h"
#include "Math/MathFwd.h"

float UBlueprintBoxRandomGeneration::ValueNoise1D(float X, float Scale, int32 Seed)
{	
	const uint32 limit = 0 - 1;

	if (Scale <= 0.0) Scale = 0.001;

	float LocX = X / Scale;

	//allows me to get a random value, with location data
	srand(Seed);
	int RandA = rand();
	srand(LocX);
	int RandB = rand();
	int totalRand = RandA + RandB;

	//gets rand A, B
	srand(totalRand);
	RandA = rand();
	RandB = rand();

	float A = floorf(LocX);
	float Fvalue = A - LocX;

	return FMath::Lerp(float(RandA) / float(limit), float(RandB) / float(limit), Fvalue);
}

float UBlueprintBoxRandomGeneration::ValueNoise2D(float X, float Y, float Scale, int32 Seed)
{
	float lim = 256.f;
	
	if (Scale <= 0.0) Scale = 0.001;

	float LocX = X / Scale;
	float LocY = Y / Scale;

	//allows me to get a random value, with location data
	srand(Seed);
	int SeedRand = rand();
	int Rand = 0;
	srand(LocX);
	Rand = rand();
	int RandX = SeedRand + Rand;
	srand(LocY);
	Rand = rand();
	int RandY = SeedRand + Rand;

	//gets rand A, B, C, D
	srand(RandX);
	float A = rand();
	srand(RandX + 1);
	float B = rand();
	srand(RandY);
	float C = rand();
	srand(RandY + 1);
	float D = rand();

	float fX = floorf(LocX);
	float XFvalue = fX - LocX;

	float fY = floorf(LocY);
	float YFvalue = fY - LocY;

	return FMath::BiLerp(A / lim, B / lim, C / lim, D / lim, XFvalue, YFvalue);
}

float UBlueprintBoxRandomGeneration::PerlinNoise2D(float X, float Y, float Scale, int32 Seed)
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


float UBlueprintBoxRandomGeneration::PerlinNoise3D(float X, float Y, float Z, float Scale, int32 Seed)
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