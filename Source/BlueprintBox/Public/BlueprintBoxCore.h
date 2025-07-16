
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

DECLARE_DYNAMIC_DELEGATE(FThreadTypeSwitch);

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

	//for spectral reassignment when doing fft
	TArray<float> HannWindow;
	TArray<float> TimeWeightedHannWindow;
	TArray<float> HannDerivativeWindow;

	static void PrecomputeHannWindows(int32 SamplesToRead, UBlueprintBoxCore* Ref);

	//spectrogram done all its calculations
	void DoneCalculatingFFT_Internal(FSpectrogramOutput output, UBlueprintBoxCore* Ref);

	//Runs any code attached to the event thats bound to `Thread Delegate`, on a thread type of your choice. Could be main, could be async, ect.
	// 
	//!!!WARNING FOR ASYNC THREADS!!!
	//DO NOT make or destroy objects on async threads!
	//DO NOT write to variables that other async threads may write to!
	//ENSURE that all objects that are called are valid at all times!
	//Blueprints do not have safeguards for async code, so use with caution.
	//If you need to make objects or write to shared variables, temporarily move back to the main thread.
	//@Param GameThread - Set to false to run the code on an async thread
	UFUNCTION(blueprintcallable, meta = (category = "Blueprint Box | Core", DisplayName = "Run on Any Thread"))
	void RunThreadType(const FThreadTypeSwitch& DelegateReturn, bool GameThread = true);
};