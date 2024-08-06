// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "BlueprintBoxCore.h"
#include "BlueprintBoxRandomJunk.generated.h"


UENUM(BlueprintType)
enum FFindFileSucess
{

	Success,

	BadObjRefernce,

	BadDirectoryName,

};

//Used for the async file finding function.
USTRUCT(BlueprintType)
struct FFilesReturn
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<FString> FoundFiles;

	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<FFindFileSucess> Status;

};

DECLARE_DYNAMIC_DELEGATE_OneParam(FFilesDelegate, FFilesReturn, Output);

UCLASS(BlueprintType, Category = "Blueprint Box | Random Junk")
class BLUEPRINTBOX_API UBlueprintBoxRandomJunk : public UBlueprintBoxCore
{

	GENERATED_BODY()

public:

	//Allows you to find any refernces to an object.
	//Rama made a tutorial on this. Im just grabbing it.
	UFUNCTION(BlueprintCallable, Category = "Blueprint Box | Random Junk", DisplayName = "Get Object References")
	static void GetObjReferences(UObject* Obj, TArray<UObject*>& OutReferencedObjects);

	//allows you to set the custom data of a large amount of Instanced Static Meshes at the same time.
	//@param InstanceIndexes - all the instaces you want to update.
	//@param CustomDataIndexs - this is the custom datas that you want to update. if you only have 1 custom data values, make an array with a length of 1
	//@param CustomDataValue - the value of the custom data. make the array length the same as Custom Data Indexs.
	UFUNCTION(BlueprintCallable, Category = "Blueprint Box | Random Junk", DisplayName = "Set Custom Data Values")
	static TArray<bool> SetCustomDataValues(UInstancedStaticMeshComponent* ISM, TArray<int32> InstanceIndexes, TArray<int32> CustomDataIndexs, TArray<float> CustomDataValue, bool MarkRenderStateDirty);

	//allows you to flip the values of in an array of floats
	//if A is found it will be swapped with B, vice-versa
	UFUNCTION(BlueprintCallable, Category = "Blueprint Box | Random Junk", DisplayName = "Swap Floats")
	static TArray<double> SwapFloats(TArray<double> Input, double A, double B);

	//Forefully Allows you to mark objects for deletion.
	//If the object is in use by the render thread forcefully deleting can cause issues or crashing, so use this only when you are sure the object is no longer being visually referenced.
	UFUNCTION(BlueprintCallable, Category = "Blueprint Box | Random Junk", DisplayName = "Destruct Object")
	static void FreeMem(UObject* Object);

	//Forefully Allows you to mark objects for deletion.
	//If the object is in use by the render thread forcefully deleting can cause issues or crashing, so use this only when you are sure the object is no longer being visually referenced.
	UFUNCTION(BlueprintCallable, Category = "Blueprint Box | Random Junk", DisplayName = "Destruct Object Array")
	static void FreeMemArray(TArray<UObject*> Object);

	//Was pulled from the BP File Utilities plugin. I wanted to make some modifications to this, so i pulled it over to my own plugin.
	//Its now Async and will only run if the directory is valid, and it will also only recursivly search up to the level specified.
	//Finds all the files and/or directories within the given directory and any sub-directories.
	//Files can be found with an optional file extension filter.
	//@param StartDirectory - The absolute path to the directory to start the search. Ex: "C:\UE4\Pictures"
	//@param FoundPaths - All the paths (directories and/or files) found
	//@param Wildcard - Wildcard that can be used to find files or directories with specific text in their name. \n E.g *.png to find all files ending with the png extension, *images* to find anything with the word "images" in it. \n Otherwise FileExtension can be of the form .EXT or just EXT and only files with that extension will be returned. \n Does not apply to directories
	//@param RecursionAmount - how many folder layers to search. set to 0 to only search the first layer
	//@param FindFiles - Whether or not to find files
	//@param FindDirectories - Whether or not to find directories
	UFUNCTION(BlueprintCallable, meta = (Category = "Blueprint Box | Random Junk", DisplayName = "Find Files/Directories", Latent))
	virtual void FindFilesDirectories(const FString& StartDirectory, const FString& Wildcard, const int32 RecursionAmount, bool FindFiles, bool FindDirectories, const FFilesDelegate& result);

	//Converts your screenspace mouse position into a world space position along the horizontal plane.
	//@param Height - the height off the horizontal plane.
	UFUNCTION(BlueprintCallable, Category = "Blueprint Box | Random Junk", DisplayName = "Screen Space To World Space")
	static void ScreenSpaceToWorldSpace(UGameUserSettings* GameUserSettings, AActor* Camera, float Height, float FOV, float& WorldSpaceX, float& WorldSpaceY);

	//gets all the transforms from an Instanced Static Mesh Object.
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "Blueprint Box | Random Junk", DisplayName = "Get Instance Transforms"))
	static TArray<FTransform> GetInstanceTransforms(UInstancedStaticMeshComponent* ISM, bool UsingWorldSpace);

	//gets the specified transforms from an Instanced Static Mesh Object.
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "Blueprint Box | Random Junk", DisplayName = "Get Instance Transforms (using Index Array)"))
	static TArray<FTransform> GetInstanceTransformsUsingIndex(UInstancedStaticMeshComponent* ISM, const TArray<int32>& transforms, bool UsingWorldSpace);

	//returns an array of all the overlapping instances by index. to be used in conjunction with an instanced static mesh.
	//note that this function is very quick, but also very specific in use. it expects the size of the mesh to be relative to 1 meter, and be a cube.
	//this function was created because the original function that comes native with ISM's is broken.
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (Category = "Blueprint Box | Random Junk", DisplayName = "Box Overlap Detection"))
	static TArray<int32> BoxOverlap(const TArray<FTransform>& Transforms, const FBox& Box);

	//detects if a point is within a sphere.
	//@param Radius - Radius in cm.
	//@param Center - the center point of the sphere.
	//@param Point - the point you'd like to check
	UFUNCTION(BlueprintCallable, meta = (Category = "Blueprint Box | Random Junk", DisplayName = "Is Within Sphere"))
	static bool IsWithinSphere(double Radius, FVector Center, FVector Point);

	//a smoothed perlin noise 1D function
	UFUNCTION(BlueprintCallable, meta = (Category = "Blueprint Box | Random Junk", DisplayName = "Perlin Noise 1D"))
	static double PerlinNoise1D(double X, double Scale, int32 Seed);

	//a smoothed perlin noise 2D function
	UFUNCTION(BlueprintCallable, meta = (Category = "Blueprint Box | Random Junk", DisplayName = "Perlin Noise 2D"))
	static double PerlinNoise2D(double X, double Y, double Scale, int32 Seed);

	//a smoothed perlin noise 3D function
	UFUNCTION(BlueprintCallable, meta = (Category = "Blueprint Box | Random Junk", DisplayName = "Perlin Noise 3D"))
	static double PerlinNoise3D(double X, double Y, double Z, double Scale, int32 Seed);

	private:

};
