#pragma once
#include "BlueprintBoxCore.h"
#include "BlueprintBoxRandomGeneration.generated.h"

UCLASS(BlueprintType, Category = "Blueprint Box | Random Generation")
class BLUEPRINTBOX_API UBlueprintBoxRandomGeneration : public UBlueprintBoxCore
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "Blueprint Box | Random Generation", DisplayName = "Value Noise 2D"))
	static float ValueNoise1D(float X, float Scale, int32 Seed);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "Blueprint Box | Random Generation", DisplayName = "Value Noise 2D"))
	static float ValueNoise2D(float X, float Y, float Scale, int32 Seed);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "Blueprint Box | Random Generation", DisplayName = "Perlin Noise 2D"))
	static float PerlinNoise2D(float X, float Y, float Scale, int32 Seed);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "Blueprint Box | Random Generation", DisplayName = "Perlin Noise 3D"))
	static float PerlinNoise3D(float X, float Y, float Z, float Scale, int32 Seed);

};