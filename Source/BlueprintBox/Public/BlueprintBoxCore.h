
#pragma once
#include "BlueprintBoxCore.generated.h"

UENUM(BlueprintType)
enum FGenerationStatus
{

	Loop			UMETA(DisplayName = "Continue Looping"),

	InvalidObject	UMETA(DisplayName = "Objects Failed to Verify"),

	DontLoop		UMETA(DisplayName = "End Reached"),

};

//Output from the delegate. break apart to get the goodies inside.
USTRUCT(BlueprintType)
struct FSpectrogramOutput
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, meta = (ToolTip = "generation status"))
	TEnumAsByte<FGenerationStatus> Status;

	UPROPERTY(BlueprintReadWrite, meta = (ToolTip = "Stick back into the function"))
	int32 ChunkIndex;

	UPROPERTY(BlueprintReadWrite, meta = (ToolTip = "Stick back into the function"))
	int32 ThreadID;

	UPROPERTY(BlueprintReadWrite, meta = (ToolTip = "Where in the song this particular chunk is representing in seconds", DisplayName = "Time (Seconds)"))
	int32 Time;

	UPROPERTY(BlueprintReadWrite, meta = (ToolTip = "The texture for this chunk. set to linear greyscale to use in a material"))
	TWeakObjectPtr<UTexture2D> Texture;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGeneratedTextures, FSpectrogramOutput, Output);

UCLASS(BlueprintType, Category = "Blueprint Box | Core")
class BLUEPRINTBOX_API UBlueprintBoxCore : public UBlueprintFunctionLibrary
{

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "Blueprint Box | Audio Analysis")
	FGeneratedTextures DoneCalculatingFFT;

	//Used for multithreading a veriety of functions. Its EXTREMELY important that you turn this into an object reference.
	//Otherwise, GC may come along and wipe this, thinking its not in use (even tho it is).
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "Blueprint Box | Core", DisplayName = "Create Blueprint Box Object"))
	static UBlueprintBoxCore* CreateBPBoxObject();

	//spectrogram done all its calculations
	void DoneCalculatingFFT_Internal(FSpectrogramOutput output, UBlueprintBoxCore* Ref);
};