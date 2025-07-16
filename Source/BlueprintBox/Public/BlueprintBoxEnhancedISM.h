// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Components/InstancedStaticMeshComponent.h"
#include "BlueprintBoxEnhancedISM.generated.h"

UCLASS(BlueprintType, Category = "Blueprint Box | Enhanced ISM")
class BLUEPRINTBOX_API UBlueprintBoxEnhancedISM : public UInstancedStaticMeshComponent
{

	GENERATED_BODY()

public:
	
	//sets the chunk size in meters. a large chunk will reduce memory but make finding random instances slower, while a small chunk will do the oppisite. recommended to have around 100 to 200 instances in a chunk
	UPROPERTY(BlueprintReadWrite)
	FIntVector ChunkSize;
	
	TMap<FIntVector, UInstancedStaticMeshComponent*> Chunks;

	// spawns an instance.
	// to update the scene, be sure to call 
	//@param IgnoreOverlap - toggles if you want it to check for overlap. True means it will spawn as normal, and False wil do the overlap detection and will not spawn a mesh if detects an overlap
	UFUNCTION(blueprintcallable, meta = (category = "Blueprint Box | Enhanced ISM", DisplayName = "Add Instance"))
	static bool AddInstanceChunked(UBlueprintBoxEnhancedISM* EISM, FTransform Transform, bool IgnoreOverlap = true);

	
};
