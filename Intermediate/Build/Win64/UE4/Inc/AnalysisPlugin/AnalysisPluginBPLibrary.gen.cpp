// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AnalysisPlugin/Public/AnalysisPluginBPLibrary.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAnalysisPluginBPLibrary() {}
// Cross Module References
	ANALYSISPLUGIN_API UFunction* Z_Construct_UDelegateFunction_AnalysisPlugin_GeneratedTextures__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_AnalysisPlugin();
	ANALYSISPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FSpectrogramOutput();
	ANALYSISPLUGIN_API UEnum* Z_Construct_UEnum_AnalysisPlugin_FMidiType();
	ANALYSISPLUGIN_API UEnum* Z_Construct_UEnum_AnalysisPlugin_FGenerationType();
	ANALYSISPLUGIN_API UEnum* Z_Construct_UEnum_AnalysisPlugin_FSpectrogramBandType();
	ANALYSISPLUGIN_API UEnum* Z_Construct_UEnum_AnalysisPlugin_FGenerationStatus();
	ANALYSISPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FMidiStruct();
	ANALYSISPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FSpectrogramTextures();
	ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
	ANALYSISPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FWaveformInput();
	RUNTIMEAUDIOIMPORTER_API UClass* Z_Construct_UClass_UImportedSoundWave_NoRegister();
	AUDIOANALYSISTOOLS_API UClass* Z_Construct_UClass_UAudioAnalysisToolsLibrary_NoRegister();
	ANALYSISPLUGIN_API UScriptStruct* Z_Construct_UScriptStruct_FSpectrogramInput();
	ANALYSISPLUGIN_API UClass* Z_Construct_UClass_UAnalysisPluginBPLibrary_NoRegister();
	ANALYSISPLUGIN_API UClass* Z_Construct_UClass_UAnalysisPluginBPLibrary();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FColor();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_AnalysisPlugin_GeneratedTextures__DelegateSignature_Statics
	{
		struct _Script_AnalysisPlugin_eventGeneratedTextures_Parms
		{
			FSpectrogramOutput Output;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_Output;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_AnalysisPlugin_GeneratedTextures__DelegateSignature_Statics::NewProp_Output = { "Output", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_AnalysisPlugin_eventGeneratedTextures_Parms, Output), Z_Construct_UScriptStruct_FSpectrogramOutput, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_AnalysisPlugin_GeneratedTextures__DelegateSignature_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_AnalysisPlugin_GeneratedTextures__DelegateSignature_Statics::NewProp_Output,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_AnalysisPlugin_GeneratedTextures__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_AnalysisPlugin_GeneratedTextures__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_AnalysisPlugin, nullptr, "GeneratedTextures__DelegateSignature", nullptr, nullptr, sizeof(_Script_AnalysisPlugin_eventGeneratedTextures_Parms), Z_Construct_UDelegateFunction_AnalysisPlugin_GeneratedTextures__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_AnalysisPlugin_GeneratedTextures__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_AnalysisPlugin_GeneratedTextures__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_AnalysisPlugin_GeneratedTextures__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_AnalysisPlugin_GeneratedTextures__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UDelegateFunction_AnalysisPlugin_GeneratedTextures__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	static UEnum* FMidiType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_AnalysisPlugin_FMidiType, Z_Construct_UPackage__Script_AnalysisPlugin(), TEXT("FMidiType"));
		}
		return Singleton;
	}
	template<> ANALYSISPLUGIN_API UEnum* StaticEnum<FMidiType>()
	{
		return FMidiType_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_FMidiType(FMidiType_StaticEnum, TEXT("/Script/AnalysisPlugin"), TEXT("FMidiType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_AnalysisPlugin_FMidiType_Hash() { return 3081864507U; }
	UEnum* Z_Construct_UEnum_AnalysisPlugin_FMidiType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_AnalysisPlugin();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("FMidiType"), 0, Get_Z_Construct_UEnum_AnalysisPlugin_FMidiType_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "NoteOff", (int64)NoteOff },
				{ "NoteOn", (int64)NoteOn },
				{ "Aftertouch", (int64)Aftertouch },
				{ "PatchChange", (int64)PatchChange },
				{ "ChannelPressure", (int64)ChannelPressure },
				{ "PitchBend", (int64)PitchBend },
				{ "SystemMessage", (int64)SystemMessage },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "Aftertouch.DisplayName", "AfterTouch" },
				{ "Aftertouch.Name", "Aftertouch" },
				{ "BlueprintType", "true" },
				{ "ChannelPressure.DisplayName", "ChannelPressure" },
				{ "ChannelPressure.Name", "ChannelPressure" },
				{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
				{ "NoteOff.DisplayName", "Note Off" },
				{ "NoteOff.Name", "NoteOff" },
				{ "NoteOn.DisplayName", "Note On" },
				{ "NoteOn.Name", "NoteOn" },
				{ "PatchChange.DisplayName", "Patch Change" },
				{ "PatchChange.Name", "PatchChange" },
				{ "PitchBend.DisplayName", "PitchBend" },
				{ "PitchBend.Name", "PitchBend" },
				{ "SystemMessage.DisplayName", "non-musical command" },
				{ "SystemMessage.Name", "SystemMessage" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_AnalysisPlugin,
				nullptr,
				"FMidiType",
				"FMidiType",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::Regular,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* FGenerationType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_AnalysisPlugin_FGenerationType, Z_Construct_UPackage__Script_AnalysisPlugin(), TEXT("FGenerationType"));
		}
		return Singleton;
	}
	template<> ANALYSISPLUGIN_API UEnum* StaticEnum<FGenerationType>()
	{
		return FGenerationType_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_FGenerationType(FGenerationType_StaticEnum, TEXT("/Script/AnalysisPlugin"), TEXT("FGenerationType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_AnalysisPlugin_FGenerationType_Hash() { return 2598192549U; }
	UEnum* Z_Construct_UEnum_AnalysisPlugin_FGenerationType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_AnalysisPlugin();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("FGenerationType"), 0, Get_Z_Construct_UEnum_AnalysisPlugin_FGenerationType_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "Waveform", (int64)Waveform },
				{ "Spectrogram", (int64)Spectrogram },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
				{ "Spectrogram.DisplayName", "Spectrogram" },
				{ "Spectrogram.Name", "Spectrogram" },
				{ "Waveform.DisplayName", "Waveform" },
				{ "Waveform.Name", "Waveform" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_AnalysisPlugin,
				nullptr,
				"FGenerationType",
				"FGenerationType",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::Regular,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* FSpectrogramBandType_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_AnalysisPlugin_FSpectrogramBandType, Z_Construct_UPackage__Script_AnalysisPlugin(), TEXT("FSpectrogramBandType"));
		}
		return Singleton;
	}
	template<> ANALYSISPLUGIN_API UEnum* StaticEnum<FSpectrogramBandType>()
	{
		return FSpectrogramBandType_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_FSpectrogramBandType(FSpectrogramBandType_StaticEnum, TEXT("/Script/AnalysisPlugin"), TEXT("FSpectrogramBandType"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_AnalysisPlugin_FSpectrogramBandType_Hash() { return 2955993959U; }
	UEnum* Z_Construct_UEnum_AnalysisPlugin_FSpectrogramBandType()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_AnalysisPlugin();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("FSpectrogramBandType"), 0, Get_Z_Construct_UEnum_AnalysisPlugin_FSpectrogramBandType_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "Left", (int64)Left },
				{ "Right", (int64)Right },
				{ "Combined", (int64)Combined },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "Combined.DisplayName", "Left and Right Combined" },
				{ "Combined.Name", "Combined" },
				{ "Combined.ToolTip", "Merges both left and right into a single texture" },
				{ "Left.DisplayName", "Left Audio" },
				{ "Left.Name", "Left" },
				{ "Left.ToolTip", "Provides the left audio only" },
				{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
				{ "Right.DisplayName", "Right Audio" },
				{ "Right.Name", "Right" },
				{ "Right.ToolTip", "Provides the right audio only" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_AnalysisPlugin,
				nullptr,
				"FSpectrogramBandType",
				"FSpectrogramBandType",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::Regular,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
	static UEnum* FGenerationStatus_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_AnalysisPlugin_FGenerationStatus, Z_Construct_UPackage__Script_AnalysisPlugin(), TEXT("FGenerationStatus"));
		}
		return Singleton;
	}
	template<> ANALYSISPLUGIN_API UEnum* StaticEnum<FGenerationStatus>()
	{
		return FGenerationStatus_StaticEnum();
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_FGenerationStatus(FGenerationStatus_StaticEnum, TEXT("/Script/AnalysisPlugin"), TEXT("FGenerationStatus"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_AnalysisPlugin_FGenerationStatus_Hash() { return 3734568490U; }
	UEnum* Z_Construct_UEnum_AnalysisPlugin_FGenerationStatus()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_AnalysisPlugin();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("FGenerationStatus"), 0, Get_Z_Construct_UEnum_AnalysisPlugin_FGenerationStatus_Hash(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "Loop", (int64)Loop },
				{ "InvalidObject", (int64)InvalidObject },
				{ "DontLoop", (int64)DontLoop },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "BlueprintType", "true" },
				{ "DontLoop.DisplayName", "End Reached" },
				{ "DontLoop.Name", "DontLoop" },
				{ "InvalidObject.DisplayName", "Objects Failed to Verify" },
				{ "InvalidObject.Name", "InvalidObject" },
				{ "Loop.DisplayName", "Continue Looping" },
				{ "Loop.Name", "Loop" },
				{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_AnalysisPlugin,
				nullptr,
				"FGenerationStatus",
				"FGenerationStatus",
				Enumerators,
				UE_ARRAY_COUNT(Enumerators),
				RF_Public|RF_Transient|RF_MarkAsNative,
				EEnumFlags::None,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				(uint8)UEnum::ECppForm::Regular,
				METADATA_PARAMS(Enum_MetaDataParams, UE_ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
class UScriptStruct* FMidiStruct::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ANALYSISPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FMidiStruct_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FMidiStruct, Z_Construct_UPackage__Script_AnalysisPlugin(), TEXT("MidiStruct"), sizeof(FMidiStruct), Get_Z_Construct_UScriptStruct_FMidiStruct_Hash());
	}
	return Singleton;
}
template<> ANALYSISPLUGIN_API UScriptStruct* StaticStruct<FMidiStruct>()
{
	return FMidiStruct::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FMidiStruct(FMidiStruct::StaticStruct, TEXT("/Script/AnalysisPlugin"), TEXT("MidiStruct"), false, nullptr, nullptr);
static struct FScriptStruct_AnalysisPlugin_StaticRegisterNativesFMidiStruct
{
	FScriptStruct_AnalysisPlugin_StaticRegisterNativesFMidiStruct()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("MidiStruct")),new UScriptStruct::TCppStructOps<FMidiStruct>);
	}
} ScriptStruct_AnalysisPlugin_StaticRegisterNativesFMidiStruct;
	struct Z_Construct_UScriptStruct_FMidiStruct_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Status_MetaData[];
#endif
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Status;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FMidiStruct_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FMidiStruct_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMidiStruct>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FMidiStruct_Statics::NewProp_Status_MetaData[] = {
		{ "Category", "MidiStruct" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "generation status" },
	};
#endif
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FMidiStruct_Statics::NewProp_Status = { "Status", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FMidiStruct, Status), Z_Construct_UEnum_AnalysisPlugin_FGenerationStatus, METADATA_PARAMS(Z_Construct_UScriptStruct_FMidiStruct_Statics::NewProp_Status_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMidiStruct_Statics::NewProp_Status_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FMidiStruct_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMidiStruct_Statics::NewProp_Status,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FMidiStruct_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AnalysisPlugin,
		nullptr,
		&NewStructOps,
		"MidiStruct",
		sizeof(FMidiStruct),
		alignof(FMidiStruct),
		Z_Construct_UScriptStruct_FMidiStruct_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMidiStruct_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FMidiStruct_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMidiStruct_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FMidiStruct()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FMidiStruct_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_AnalysisPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("MidiStruct"), sizeof(FMidiStruct), Get_Z_Construct_UScriptStruct_FMidiStruct_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FMidiStruct_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FMidiStruct_Hash() { return 1518753763U; }
class UScriptStruct* FSpectrogramTextures::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ANALYSISPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FSpectrogramTextures_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FSpectrogramTextures, Z_Construct_UPackage__Script_AnalysisPlugin(), TEXT("SpectrogramTextures"), sizeof(FSpectrogramTextures), Get_Z_Construct_UScriptStruct_FSpectrogramTextures_Hash());
	}
	return Singleton;
}
template<> ANALYSISPLUGIN_API UScriptStruct* StaticStruct<FSpectrogramTextures>()
{
	return FSpectrogramTextures::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FSpectrogramTextures(FSpectrogramTextures::StaticStruct, TEXT("/Script/AnalysisPlugin"), TEXT("SpectrogramTextures"), false, nullptr, nullptr);
static struct FScriptStruct_AnalysisPlugin_StaticRegisterNativesFSpectrogramTextures
{
	FScriptStruct_AnalysisPlugin_StaticRegisterNativesFSpectrogramTextures()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("SpectrogramTextures")),new UScriptStruct::TCppStructOps<FSpectrogramTextures>);
	}
} ScriptStruct_AnalysisPlugin_StaticRegisterNativesFSpectrogramTextures;
	struct Z_Construct_UScriptStruct_FSpectrogramTextures_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Time_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Time;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Texture_MetaData[];
#endif
		static const UE4CodeGen_Private::FWeakObjectPropertyParams NewProp_Texture;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSpectrogramTextures_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FSpectrogramTextures_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FSpectrogramTextures>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSpectrogramTextures_Statics::NewProp_Time_MetaData[] = {
		{ "Category", "SpectrogramTextures" },
		{ "DisplayName", "Time (Seconds)" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "Where in the song this particular chunk is representing in seconds" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FSpectrogramTextures_Statics::NewProp_Time = { "Time", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSpectrogramTextures, Time), METADATA_PARAMS(Z_Construct_UScriptStruct_FSpectrogramTextures_Statics::NewProp_Time_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpectrogramTextures_Statics::NewProp_Time_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSpectrogramTextures_Statics::NewProp_Texture_MetaData[] = {
		{ "Category", "SpectrogramTextures" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "The texture for this chunk" },
	};
#endif
	const UE4CodeGen_Private::FWeakObjectPropertyParams Z_Construct_UScriptStruct_FSpectrogramTextures_Statics::NewProp_Texture = { "Texture", nullptr, (EPropertyFlags)0x0014000000000004, UE4CodeGen_Private::EPropertyGenFlags::WeakObject, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSpectrogramTextures, Texture), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(Z_Construct_UScriptStruct_FSpectrogramTextures_Statics::NewProp_Texture_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpectrogramTextures_Statics::NewProp_Texture_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FSpectrogramTextures_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpectrogramTextures_Statics::NewProp_Time,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpectrogramTextures_Statics::NewProp_Texture,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FSpectrogramTextures_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AnalysisPlugin,
		nullptr,
		&NewStructOps,
		"SpectrogramTextures",
		sizeof(FSpectrogramTextures),
		alignof(FSpectrogramTextures),
		Z_Construct_UScriptStruct_FSpectrogramTextures_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpectrogramTextures_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FSpectrogramTextures_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpectrogramTextures_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FSpectrogramTextures()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FSpectrogramTextures_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_AnalysisPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("SpectrogramTextures"), sizeof(FSpectrogramTextures), Get_Z_Construct_UScriptStruct_FSpectrogramTextures_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FSpectrogramTextures_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FSpectrogramTextures_Hash() { return 1479607452U; }
class UScriptStruct* FSpectrogramOutput::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ANALYSISPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FSpectrogramOutput_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FSpectrogramOutput, Z_Construct_UPackage__Script_AnalysisPlugin(), TEXT("SpectrogramOutput"), sizeof(FSpectrogramOutput), Get_Z_Construct_UScriptStruct_FSpectrogramOutput_Hash());
	}
	return Singleton;
}
template<> ANALYSISPLUGIN_API UScriptStruct* StaticStruct<FSpectrogramOutput>()
{
	return FSpectrogramOutput::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FSpectrogramOutput(FSpectrogramOutput::StaticStruct, TEXT("/Script/AnalysisPlugin"), TEXT("SpectrogramOutput"), false, nullptr, nullptr);
static struct FScriptStruct_AnalysisPlugin_StaticRegisterNativesFSpectrogramOutput
{
	FScriptStruct_AnalysisPlugin_StaticRegisterNativesFSpectrogramOutput()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("SpectrogramOutput")),new UScriptStruct::TCppStructOps<FSpectrogramOutput>);
	}
} ScriptStruct_AnalysisPlugin_StaticRegisterNativesFSpectrogramOutput;
	struct Z_Construct_UScriptStruct_FSpectrogramOutput_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Status_MetaData[];
#endif
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_Status;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ChunkIndex_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ChunkIndex;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Time_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Time;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_Texture_MetaData[];
#endif
		static const UE4CodeGen_Private::FWeakObjectPropertyParams NewProp_Texture;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "//Output from the delegate. break apart to get the goodies inside.\n" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "Output from the delegate. break apart to get the goodies inside." },
	};
#endif
	void* Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FSpectrogramOutput>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::NewProp_Status_MetaData[] = {
		{ "Category", "SpectrogramOutput" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "generation status" },
	};
#endif
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::NewProp_Status = { "Status", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSpectrogramOutput, Status), Z_Construct_UEnum_AnalysisPlugin_FGenerationStatus, METADATA_PARAMS(Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::NewProp_Status_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::NewProp_Status_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::NewProp_ChunkIndex_MetaData[] = {
		{ "Category", "SpectrogramOutput" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "Stick back into the function" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::NewProp_ChunkIndex = { "ChunkIndex", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSpectrogramOutput, ChunkIndex), METADATA_PARAMS(Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::NewProp_ChunkIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::NewProp_ChunkIndex_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::NewProp_Time_MetaData[] = {
		{ "Category", "SpectrogramOutput" },
		{ "DisplayName", "Time (Seconds)" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "Where in the song this particular chunk is representing in seconds" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::NewProp_Time = { "Time", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSpectrogramOutput, Time), METADATA_PARAMS(Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::NewProp_Time_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::NewProp_Time_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::NewProp_Texture_MetaData[] = {
		{ "Category", "SpectrogramOutput" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "The texture for this chunk" },
	};
#endif
	const UE4CodeGen_Private::FWeakObjectPropertyParams Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::NewProp_Texture = { "Texture", nullptr, (EPropertyFlags)0x0014000000000004, UE4CodeGen_Private::EPropertyGenFlags::WeakObject, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSpectrogramOutput, Texture), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::NewProp_Texture_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::NewProp_Texture_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::NewProp_Status,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::NewProp_ChunkIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::NewProp_Time,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::NewProp_Texture,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AnalysisPlugin,
		nullptr,
		&NewStructOps,
		"SpectrogramOutput",
		sizeof(FSpectrogramOutput),
		alignof(FSpectrogramOutput),
		Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FSpectrogramOutput()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FSpectrogramOutput_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_AnalysisPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("SpectrogramOutput"), sizeof(FSpectrogramOutput), Get_Z_Construct_UScriptStruct_FSpectrogramOutput_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FSpectrogramOutput_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FSpectrogramOutput_Hash() { return 3364133187U; }
class UScriptStruct* FWaveformInput::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ANALYSISPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FWaveformInput_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FWaveformInput, Z_Construct_UPackage__Script_AnalysisPlugin(), TEXT("WaveformInput"), sizeof(FWaveformInput), Get_Z_Construct_UScriptStruct_FWaveformInput_Hash());
	}
	return Singleton;
}
template<> ANALYSISPLUGIN_API UScriptStruct* StaticStruct<FWaveformInput>()
{
	return FWaveformInput::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FWaveformInput(FWaveformInput::StaticStruct, TEXT("/Script/AnalysisPlugin"), TEXT("WaveformInput"), false, nullptr, nullptr);
static struct FScriptStruct_AnalysisPlugin_StaticRegisterNativesFWaveformInput
{
	FScriptStruct_AnalysisPlugin_StaticRegisterNativesFWaveformInput()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("WaveformInput")),new UScriptStruct::TCppStructOps<FWaveformInput>);
	}
} ScriptStruct_AnalysisPlugin_StaticRegisterNativesFWaveformInput;
	struct Z_Construct_UScriptStruct_FWaveformInput_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ImportedSoundWave_MetaData[];
#endif
		static const UE4CodeGen_Private::FWeakObjectPropertyParams NewProp_ImportedSoundWave;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AudioAnalysisObject_MetaData[];
#endif
		static const UE4CodeGen_Private::FWeakObjectPropertyParams NewProp_AudioAnalysisObject;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ThreadCount_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ThreadCount;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_WaveformSampleRate_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_WaveformSampleRate;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_WaveformAudioGranularity_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_WaveformAudioGranularity;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FWaveformInput_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "//Input nodes for the waveform. Allows you to simplify your setup when it comes to making a thread pool.\n" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "Input nodes for the waveform. Allows you to simplify your setup when it comes to making a thread pool." },
	};
#endif
	void* Z_Construct_UScriptStruct_FWaveformInput_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FWaveformInput>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_ImportedSoundWave_MetaData[] = {
		{ "Category", "WaveformInput" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FWeakObjectPropertyParams Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_ImportedSoundWave = { "ImportedSoundWave", nullptr, (EPropertyFlags)0x0014000000000004, UE4CodeGen_Private::EPropertyGenFlags::WeakObject, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FWaveformInput, ImportedSoundWave), Z_Construct_UClass_UImportedSoundWave_NoRegister, METADATA_PARAMS(Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_ImportedSoundWave_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_ImportedSoundWave_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_AudioAnalysisObject_MetaData[] = {
		{ "Category", "WaveformInput" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FWeakObjectPropertyParams Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_AudioAnalysisObject = { "AudioAnalysisObject", nullptr, (EPropertyFlags)0x0014000000000004, UE4CodeGen_Private::EPropertyGenFlags::WeakObject, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FWaveformInput, AudioAnalysisObject), Z_Construct_UClass_UAudioAnalysisToolsLibrary_NoRegister, METADATA_PARAMS(Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_AudioAnalysisObject_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_AudioAnalysisObject_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_ThreadCount_MetaData[] = {
		{ "Category", "WaveformInput" },
		{ "Comment", "//Allows you to tell the function how many threads are going to be used total.\n" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "Allows you to tell the function how many threads are going to be used total." },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_ThreadCount = { "ThreadCount", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FWaveformInput, ThreadCount), METADATA_PARAMS(Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_ThreadCount_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_ThreadCount_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_WaveformSampleRate_MetaData[] = {
		{ "Category", "WaveformInput" },
		{ "Comment", "//Determines how often you wish to sample the original sound wave. Values higher than 2^14 will not generate.\n" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "Determines how often you wish to sample the original sound wave. Values higher than 2^14 will not generate." },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_WaveformSampleRate = { "WaveformSampleRate", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FWaveformInput, WaveformSampleRate), METADATA_PARAMS(Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_WaveformSampleRate_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_WaveformSampleRate_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_WaveformAudioGranularity_MetaData[] = {
		{ "Category", "WaveformInput" },
		{ "Comment", "//Determines the audio granularity of the waveform. also determines the texture width. Recommended to be an even number. Values of 256 are recommended.\n" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "Determines the audio granularity of the waveform. also determines the texture width. Recommended to be an even number. Values of 256 are recommended." },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_WaveformAudioGranularity = { "WaveformAudioGranularity", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FWaveformInput, WaveformAudioGranularity), METADATA_PARAMS(Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_WaveformAudioGranularity_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_WaveformAudioGranularity_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FWaveformInput_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_ImportedSoundWave,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_AudioAnalysisObject,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_ThreadCount,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_WaveformSampleRate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FWaveformInput_Statics::NewProp_WaveformAudioGranularity,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FWaveformInput_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AnalysisPlugin,
		nullptr,
		&NewStructOps,
		"WaveformInput",
		sizeof(FWaveformInput),
		alignof(FWaveformInput),
		Z_Construct_UScriptStruct_FWaveformInput_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FWaveformInput_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FWaveformInput_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FWaveformInput_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FWaveformInput()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FWaveformInput_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_AnalysisPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("WaveformInput"), sizeof(FWaveformInput), Get_Z_Construct_UScriptStruct_FWaveformInput_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FWaveformInput_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FWaveformInput_Hash() { return 2943384082U; }
class UScriptStruct* FSpectrogramInput::StaticStruct()
{
	static class UScriptStruct* Singleton = NULL;
	if (!Singleton)
	{
		extern ANALYSISPLUGIN_API uint32 Get_Z_Construct_UScriptStruct_FSpectrogramInput_Hash();
		Singleton = GetStaticStruct(Z_Construct_UScriptStruct_FSpectrogramInput, Z_Construct_UPackage__Script_AnalysisPlugin(), TEXT("SpectrogramInput"), sizeof(FSpectrogramInput), Get_Z_Construct_UScriptStruct_FSpectrogramInput_Hash());
	}
	return Singleton;
}
template<> ANALYSISPLUGIN_API UScriptStruct* StaticStruct<FSpectrogramInput>()
{
	return FSpectrogramInput::StaticStruct();
}
static FCompiledInDeferStruct Z_CompiledInDeferStruct_UScriptStruct_FSpectrogramInput(FSpectrogramInput::StaticStruct, TEXT("/Script/AnalysisPlugin"), TEXT("SpectrogramInput"), false, nullptr, nullptr);
static struct FScriptStruct_AnalysisPlugin_StaticRegisterNativesFSpectrogramInput
{
	FScriptStruct_AnalysisPlugin_StaticRegisterNativesFSpectrogramInput()
	{
		UScriptStruct::DeferCppStructOps(FName(TEXT("SpectrogramInput")),new UScriptStruct::TCppStructOps<FSpectrogramInput>);
	}
} ScriptStruct_AnalysisPlugin_StaticRegisterNativesFSpectrogramInput;
	struct Z_Construct_UScriptStruct_FSpectrogramInput_Statics
	{
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ImportedSoundWave_MetaData[];
#endif
		static const UE4CodeGen_Private::FWeakObjectPropertyParams NewProp_ImportedSoundWave;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_AudioAnalysisObject_MetaData[];
#endif
		static const UE4CodeGen_Private::FWeakObjectPropertyParams NewProp_AudioAnalysisObject;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ThreadCount_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ThreadCount;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SpectrogramSamples_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_SpectrogramSamples;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SpectrogramBands_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_SpectrogramBands;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BandsMin_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_BandsMin;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_BandsMax_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_BandsMax;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UE4CodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSpectrogramInput_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "//Input nodes for the fft. Allows you to simplify your setup when it comes to making a thread pool.\n" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "Input nodes for the fft. Allows you to simplify your setup when it comes to making a thread pool." },
	};
#endif
	void* Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FSpectrogramInput>();
	}
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_ImportedSoundWave_MetaData[] = {
		{ "Category", "SpectrogramInput" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FWeakObjectPropertyParams Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_ImportedSoundWave = { "ImportedSoundWave", nullptr, (EPropertyFlags)0x0014000000000004, UE4CodeGen_Private::EPropertyGenFlags::WeakObject, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSpectrogramInput, ImportedSoundWave), Z_Construct_UClass_UImportedSoundWave_NoRegister, METADATA_PARAMS(Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_ImportedSoundWave_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_ImportedSoundWave_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_AudioAnalysisObject_MetaData[] = {
		{ "Category", "SpectrogramInput" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FWeakObjectPropertyParams Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_AudioAnalysisObject = { "AudioAnalysisObject", nullptr, (EPropertyFlags)0x0014000000000004, UE4CodeGen_Private::EPropertyGenFlags::WeakObject, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSpectrogramInput, AudioAnalysisObject), Z_Construct_UClass_UAudioAnalysisToolsLibrary_NoRegister, METADATA_PARAMS(Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_AudioAnalysisObject_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_AudioAnalysisObject_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_ThreadCount_MetaData[] = {
		{ "Category", "SpectrogramInput" },
		{ "Comment", "//Allows you to tell the function how many threads are going to be used total\n" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "Allows you to tell the function how many threads are going to be used total" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_ThreadCount = { "ThreadCount", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSpectrogramInput, ThreadCount), METADATA_PARAMS(Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_ThreadCount_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_ThreadCount_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_SpectrogramSamples_MetaData[] = {
		{ "Category", "SpectrogramInput" },
		{ "Comment", "//Determines how many times you wish for the spectrogram to calculate a second. 256 is reccommended.\n" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "Determines how many times you wish for the spectrogram to calculate a second. 256 is reccommended." },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_SpectrogramSamples = { "SpectrogramSamples", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSpectrogramInput, SpectrogramSamples), METADATA_PARAMS(Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_SpectrogramSamples_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_SpectrogramSamples_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_SpectrogramBands_MetaData[] = {
		{ "Category", "SpectrogramInput" },
		{ "Comment", "//Determines how many bands you wish for the spectrogram to calculate. Value MUST be a multiple of two. 256 is reccommended.\n" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "Determines how many bands you wish for the spectrogram to calculate. Value MUST be a multiple of two. 256 is reccommended." },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_SpectrogramBands = { "SpectrogramBands", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSpectrogramInput, SpectrogramBands), METADATA_PARAMS(Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_SpectrogramBands_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_SpectrogramBands_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_BandsMin_MetaData[] = {
		{ "Category", "SpectrogramInput" },
		{ "Comment", "//defines how many bands you wish to chop from the low frequencies of the texture, as a float from 0 to 1. set to 0 to include everything from 0 up.\n" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "defines how many bands you wish to chop from the low frequencies of the texture, as a float from 0 to 1. set to 0 to include everything from 0 up." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_BandsMin = { "BandsMin", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSpectrogramInput, BandsMin), METADATA_PARAMS(Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_BandsMin_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_BandsMin_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_BandsMax_MetaData[] = {
		{ "Category", "SpectrogramInput" },
		{ "Comment", "//defines how many bands you wish to chop from the high frequencies of the texture, as a float from 0 to 1. set to 1 to include everything from 1 down.\n" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "defines how many bands you wish to chop from the high frequencies of the texture, as a float from 0 to 1. set to 1 to include everything from 1 down." },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_BandsMax = { "BandsMax", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FSpectrogramInput, BandsMax), METADATA_PARAMS(Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_BandsMax_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_BandsMax_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FSpectrogramInput_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_ImportedSoundWave,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_AudioAnalysisObject,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_ThreadCount,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_SpectrogramSamples,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_SpectrogramBands,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_BandsMin,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FSpectrogramInput_Statics::NewProp_BandsMax,
	};
	const UE4CodeGen_Private::FStructParams Z_Construct_UScriptStruct_FSpectrogramInput_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_AnalysisPlugin,
		nullptr,
		&NewStructOps,
		"SpectrogramInput",
		sizeof(FSpectrogramInput),
		alignof(FSpectrogramInput),
		Z_Construct_UScriptStruct_FSpectrogramInput_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpectrogramInput_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000001),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FSpectrogramInput_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FSpectrogramInput_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FSpectrogramInput()
	{
#if WITH_HOT_RELOAD
		extern uint32 Get_Z_Construct_UScriptStruct_FSpectrogramInput_Hash();
		UPackage* Outer = Z_Construct_UPackage__Script_AnalysisPlugin();
		static UScriptStruct* ReturnStruct = FindExistingStructIfHotReloadOrDynamic(Outer, TEXT("SpectrogramInput"), sizeof(FSpectrogramInput), Get_Z_Construct_UScriptStruct_FSpectrogramInput_Hash(), false);
#else
		static UScriptStruct* ReturnStruct = nullptr;
#endif
		if (!ReturnStruct)
		{
			UE4CodeGen_Private::ConstructUScriptStruct(ReturnStruct, Z_Construct_UScriptStruct_FSpectrogramInput_Statics::ReturnStructParams);
		}
		return ReturnStruct;
	}
	uint32 Get_Z_Construct_UScriptStruct_FSpectrogramInput_Hash() { return 1519713515U; }
	DEFINE_FUNCTION(UAnalysisPluginBPLibrary::execByteArrayToIntAndChar)
	{
		P_GET_TARRAY(uint8,Z_Param_ArrayOfMidiBytes);
		P_GET_PROPERTY(FIntProperty,Z_Param_Index);
		P_GET_PROPERTY_REF(FByteProperty,Z_Param_Out_byte);
		P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_SixteenBitInt);
		P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_TwentyFourBitInt);
		P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_ThiryTwoBitInt);
		P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_Char);
		P_FINISH;
		P_NATIVE_BEGIN;
		UAnalysisPluginBPLibrary::ByteArrayToIntAndChar(Z_Param_ArrayOfMidiBytes,Z_Param_Index,Z_Param_Out_byte,Z_Param_Out_SixteenBitInt,Z_Param_Out_TwentyFourBitInt,Z_Param_Out_ThiryTwoBitInt,Z_Param_Out_Char);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UAnalysisPluginBPLibrary::execImportMidiFromDisk)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_Path);
		P_GET_STRUCT_REF(FMidiStruct,Z_Param_Out_MidiReturn);
		P_GET_TARRAY_REF(uint8,Z_Param_Out_ArrayOfMidiBytes);
		P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_ErrorLog);
		P_FINISH;
		P_NATIVE_BEGIN;
		UAnalysisPluginBPLibrary::ImportMidiFromDisk(Z_Param_Path,Z_Param_Out_MidiReturn,Z_Param_Out_ArrayOfMidiBytes,Z_Param_Out_ErrorLog);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UAnalysisPluginBPLibrary::execCalculateSpectrogramAsync)
	{
		P_GET_OBJECT(UAnalysisPluginBPLibrary,Z_Param_AnalysisPluginRef);
		P_GET_PROPERTY(FByteProperty,Z_Param_type);
		P_GET_STRUCT(FWaveformInput,Z_Param_WaveformInput);
		P_GET_STRUCT(FSpectrogramInput,Z_Param_SpectrogramInput);
		P_GET_PROPERTY(FIntProperty,Z_Param_ChunkIndex);
		P_GET_PROPERTY(FIntProperty,Z_Param_ThreadID);
		P_FINISH;
		P_NATIVE_BEGIN;
		UAnalysisPluginBPLibrary::CalculateSpectrogramAsync(Z_Param_AnalysisPluginRef,FGenerationType(Z_Param_type),Z_Param_WaveformInput,Z_Param_SpectrogramInput,Z_Param_ChunkIndex,Z_Param_ThreadID);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UAnalysisPluginBPLibrary::execMakeWaveformColorArray)
	{
		P_GET_STRUCT(FWaveformInput,Z_Param_WaveformValues);
		P_GET_PROPERTY(FIntProperty,Z_Param_ChunkIndex);
		P_GET_PROPERTY(FIntProperty,Z_Param_ThreadId);
		P_GET_PROPERTY_REF(FByteProperty,Z_Param_Out_ContinueLooping);
		P_GET_TARRAY_REF(FColor,Z_Param_Out_color);
		P_FINISH;
		P_NATIVE_BEGIN;
		UAnalysisPluginBPLibrary::MakeWaveformColorArray(Z_Param_WaveformValues,Z_Param_ChunkIndex,Z_Param_ThreadId,(TEnumAsByte<FGenerationStatus>&)(Z_Param_Out_ContinueLooping),Z_Param_Out_color);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UAnalysisPluginBPLibrary::execMakeSpectrogramColorArray)
	{
		P_GET_STRUCT(FSpectrogramInput,Z_Param_SpectrogramValues);
		P_GET_PROPERTY(FIntProperty,Z_Param_ChunkIndex);
		P_GET_PROPERTY(FIntProperty,Z_Param_ThreadId);
		P_GET_PROPERTY_REF(FByteProperty,Z_Param_Out_ContinueLooping);
		P_GET_TARRAY_REF(FColor,Z_Param_Out_color);
		P_FINISH;
		P_NATIVE_BEGIN;
		UAnalysisPluginBPLibrary::MakeSpectrogramColorArray(Z_Param_SpectrogramValues,Z_Param_ChunkIndex,Z_Param_ThreadId,(TEnumAsByte<FGenerationStatus>&)(Z_Param_Out_ContinueLooping),Z_Param_Out_color);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UAnalysisPluginBPLibrary::execCalculateFFT)
	{
		P_GET_TARRAY(float,Z_Param_samples);
		P_GET_PROPERTY(FIntProperty,Z_Param_NumChannels);
		P_GET_PROPERTY(FIntProperty,Z_Param_SampleRate);
		P_GET_TARRAY_REF(float,Z_Param_Out_OutFrequencies);
		P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_Warnings);
		P_FINISH;
		P_NATIVE_BEGIN;
		UAnalysisPluginBPLibrary::CalculateFFT(Z_Param_samples,Z_Param_NumChannels,Z_Param_SampleRate,Z_Param_Out_OutFrequencies,Z_Param_Out_Warnings);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UAnalysisPluginBPLibrary::execCreateAnalysisPluginRef)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UAnalysisPluginBPLibrary**)Z_Param__Result=UAnalysisPluginBPLibrary::CreateAnalysisPluginRef();
		P_NATIVE_END;
	}
	void UAnalysisPluginBPLibrary::StaticRegisterNativesUAnalysisPluginBPLibrary()
	{
		UClass* Class = UAnalysisPluginBPLibrary::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "ByteArrayToIntAndChar", &UAnalysisPluginBPLibrary::execByteArrayToIntAndChar },
			{ "CalculateFFT", &UAnalysisPluginBPLibrary::execCalculateFFT },
			{ "CalculateSpectrogramAsync", &UAnalysisPluginBPLibrary::execCalculateSpectrogramAsync },
			{ "CreateAnalysisPluginRef", &UAnalysisPluginBPLibrary::execCreateAnalysisPluginRef },
			{ "ImportMidiFromDisk", &UAnalysisPluginBPLibrary::execImportMidiFromDisk },
			{ "MakeSpectrogramColorArray", &UAnalysisPluginBPLibrary::execMakeSpectrogramColorArray },
			{ "MakeWaveformColorArray", &UAnalysisPluginBPLibrary::execMakeWaveformColorArray },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics
	{
		struct AnalysisPluginBPLibrary_eventByteArrayToIntAndChar_Parms
		{
			TArray<uint8> ArrayOfMidiBytes;
			int32 Index;
			uint8 byte;
			int32 SixteenBitInt;
			int32 TwentyFourBitInt;
			int32 ThiryTwoBitInt;
			FString Char;
		};
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_ArrayOfMidiBytes_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ArrayOfMidiBytes;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_Index;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_byte;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_SixteenBitInt;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_TwentyFourBitInt;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ThiryTwoBitInt;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Char;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::NewProp_ArrayOfMidiBytes_Inner = { "ArrayOfMidiBytes", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::NewProp_ArrayOfMidiBytes = { "ArrayOfMidiBytes", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventByteArrayToIntAndChar_Parms, ArrayOfMidiBytes), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::NewProp_Index = { "Index", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventByteArrayToIntAndChar_Parms, Index), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::NewProp_byte = { "byte", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventByteArrayToIntAndChar_Parms, byte), nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::NewProp_SixteenBitInt = { "SixteenBitInt", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventByteArrayToIntAndChar_Parms, SixteenBitInt), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::NewProp_TwentyFourBitInt = { "TwentyFourBitInt", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventByteArrayToIntAndChar_Parms, TwentyFourBitInt), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::NewProp_ThiryTwoBitInt = { "ThiryTwoBitInt", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventByteArrayToIntAndChar_Parms, ThiryTwoBitInt), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::NewProp_Char = { "Char", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventByteArrayToIntAndChar_Parms, Char), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::NewProp_ArrayOfMidiBytes_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::NewProp_ArrayOfMidiBytes,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::NewProp_Index,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::NewProp_byte,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::NewProp_SixteenBitInt,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::NewProp_TwentyFourBitInt,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::NewProp_ThiryTwoBitInt,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::NewProp_Char,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::Function_MetaDataParams[] = {
		{ "Category", "Analysis Plugin | Midi Stuff (unfinished)" },
		{ "Comment", "//Allows you to convert an array of bytes into its higher value counterparts\n" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "Allows you to convert an array of bytes into its higher value counterparts" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAnalysisPluginBPLibrary, nullptr, "ByteArrayToIntAndChar", nullptr, nullptr, sizeof(AnalysisPluginBPLibrary_eventByteArrayToIntAndChar_Parms), Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics
	{
		struct AnalysisPluginBPLibrary_eventCalculateFFT_Parms
		{
			TArray<float> samples;
			int32 NumChannels;
			int32 SampleRate;
			TArray<float> OutFrequencies;
			FString Warnings;
		};
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_samples_Inner;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_samples_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_samples;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NumChannels_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_NumChannels;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_SampleRate_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_SampleRate;
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_OutFrequencies_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_OutFrequencies;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Warnings;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_samples_Inner = { "samples", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_samples_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_samples = { "samples", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventCalculateFFT_Parms, samples), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_samples_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_samples_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_NumChannels_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_NumChannels = { "NumChannels", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventCalculateFFT_Parms, NumChannels), METADATA_PARAMS(Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_NumChannels_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_NumChannels_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_SampleRate_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_SampleRate = { "SampleRate", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventCalculateFFT_Parms, SampleRate), METADATA_PARAMS(Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_SampleRate_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_SampleRate_MetaData)) };
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_OutFrequencies_Inner = { "OutFrequencies", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_OutFrequencies = { "OutFrequencies", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventCalculateFFT_Parms, OutFrequencies), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_Warnings = { "Warnings", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventCalculateFFT_Parms, Warnings), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_samples_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_samples,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_NumChannels,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_SampleRate,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_OutFrequencies_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_OutFrequencies,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::NewProp_Warnings,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::Function_MetaDataParams[] = {
		{ "Category", "Analysis Plugin | Audio Analysis" },
		{ "Comment", "//Calculates the frequency spectrum from a given array of samples. Used internaly for \"MakeSpectrogramColorArray\", but avalible to the user in blueprints.\n//@param Samples - The Samples to use to generate the spectrogram\n//@param Channel - The channel of the sound to calculate.  Specify 0 to combine channels together\n//@param StartTime - The beginning of the window to calculate the spectrum of\n//@param TimeLength - The duration of the window to calculate the spectrum of\n//@return OutSpectrum - The resulting spectrum\n" },
		{ "DisplayName", "(Internal) Calculate FFT" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "Calculates the frequency spectrum from a given array of samples. Used internaly for \"MakeSpectrogramColorArray\", but avalible to the user in blueprints.\n@param Samples - The Samples to use to generate the spectrogram\n@param Channel - The channel of the sound to calculate.  Specify 0 to combine channels together\n@param StartTime - The beginning of the window to calculate the spectrum of\n@param TimeLength - The duration of the window to calculate the spectrum of\n@return OutSpectrum - The resulting spectrum" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAnalysisPluginBPLibrary, nullptr, "CalculateFFT", nullptr, nullptr, sizeof(AnalysisPluginBPLibrary_eventCalculateFFT_Parms), Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync_Statics
	{
		struct AnalysisPluginBPLibrary_eventCalculateSpectrogramAsync_Parms
		{
			UAnalysisPluginBPLibrary* AnalysisPluginRef;
			TEnumAsByte<FGenerationType> type;
			FWaveformInput WaveformInput;
			FSpectrogramInput SpectrogramInput;
			int32 ChunkIndex;
			int32 ThreadID;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_AnalysisPluginRef;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_type;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_WaveformInput;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_SpectrogramInput;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ChunkIndex;
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ThreadID;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync_Statics::NewProp_AnalysisPluginRef = { "AnalysisPluginRef", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventCalculateSpectrogramAsync_Parms, AnalysisPluginRef), Z_Construct_UClass_UAnalysisPluginBPLibrary_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync_Statics::NewProp_type = { "type", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventCalculateSpectrogramAsync_Parms, type), Z_Construct_UEnum_AnalysisPlugin_FGenerationType, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync_Statics::NewProp_WaveformInput = { "WaveformInput", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventCalculateSpectrogramAsync_Parms, WaveformInput), Z_Construct_UScriptStruct_FWaveformInput, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync_Statics::NewProp_SpectrogramInput = { "SpectrogramInput", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventCalculateSpectrogramAsync_Parms, SpectrogramInput), Z_Construct_UScriptStruct_FSpectrogramInput, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync_Statics::NewProp_ChunkIndex = { "ChunkIndex", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventCalculateSpectrogramAsync_Parms, ChunkIndex), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync_Statics::NewProp_ThreadID = { "ThreadID", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventCalculateSpectrogramAsync_Parms, ThreadID), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync_Statics::NewProp_AnalysisPluginRef,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync_Statics::NewProp_type,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync_Statics::NewProp_WaveformInput,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync_Statics::NewProp_SpectrogramInput,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync_Statics::NewProp_ChunkIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync_Statics::NewProp_ThreadID,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync_Statics::Function_MetaDataParams[] = {
		{ "Category", "Analysis Plugin | Audio Analysis" },
		{ "Comment", "//Allows you to generate a spectrogram texture asynchronously. Take a look on my github for how to set this up (or make a thread pool)\n//Make sure that you leave, at minimum, 1 thread (for the game thread) in order for things to work smoothly in the background. 2 is much more ideal, as it leaves one for your OS.\n// \n//Because the texture generation must lock the mutex (ie all threads must wait for the opperation to be complete), there is a max cap on how many threads you can run if your textures are large enough and are generated fast enough.\n//My CPU can only handel 13 threads at 1024 by 512 for the spectrogram, and 6 threads at 96 by 1024 for the waveform, before i start to experance lag and stuttering.\n//@param AnalysisPluginRef - reference to \"Create Analysis Plugin Ref\"\n//@param type - What texture you wish to generate.\n//@param WaveformInput - Input nodes for the waveform. Allows you to simplify your setup when it comes to making a thread pool. Best to leave these as constant values once the spectrogram is running.\n//@param SpectrogramInput - Input nodes for the fft. Allows you to simplify your setup when it comes to making a thread pool. Best to leave these as constant values once the spectrogram is running.\n//@param ChunkIndex - Plug 'Output Chunk Index' that you get from the delegate back in here if you intend to loop across the entire song\n//@param ThreadId - Allows you to give the thread calculation offset so that chunks can be generated correctly.\n" },
		{ "DisplayName", "Calculate Spectrogram Async" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "Allows you to generate a spectrogram texture asynchronously. Take a look on my github for how to set this up (or make a thread pool)\nMake sure that you leave, at minimum, 1 thread (for the game thread) in order for things to work smoothly in the background. 2 is much more ideal, as it leaves one for your OS.\n\nBecause the texture generation must lock the mutex (ie all threads must wait for the opperation to be complete), there is a max cap on how many threads you can run if your textures are large enough and are generated fast enough.\nMy CPU can only handel 13 threads at 1024 by 512 for the spectrogram, and 6 threads at 96 by 1024 for the waveform, before i start to experance lag and stuttering.\n@param AnalysisPluginRef - reference to \"Create Analysis Plugin Ref\"\n@param type - What texture you wish to generate.\n@param WaveformInput - Input nodes for the waveform. Allows you to simplify your setup when it comes to making a thread pool. Best to leave these as constant values once the spectrogram is running.\n@param SpectrogramInput - Input nodes for the fft. Allows you to simplify your setup when it comes to making a thread pool. Best to leave these as constant values once the spectrogram is running.\n@param ChunkIndex - Plug 'Output Chunk Index' that you get from the delegate back in here if you intend to loop across the entire song\n@param ThreadId - Allows you to give the thread calculation offset so that chunks can be generated correctly." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAnalysisPluginBPLibrary, nullptr, "CalculateSpectrogramAsync", nullptr, nullptr, sizeof(AnalysisPluginBPLibrary_eventCalculateSpectrogramAsync_Parms), Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAnalysisPluginBPLibrary_CreateAnalysisPluginRef_Statics
	{
		struct AnalysisPluginBPLibrary_eventCreateAnalysisPluginRef_Parms
		{
			UAnalysisPluginBPLibrary* ReturnValue;
		};
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_CreateAnalysisPluginRef_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventCreateAnalysisPluginRef_Parms, ReturnValue), Z_Construct_UClass_UAnalysisPluginBPLibrary_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAnalysisPluginBPLibrary_CreateAnalysisPluginRef_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_CreateAnalysisPluginRef_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAnalysisPluginBPLibrary_CreateAnalysisPluginRef_Statics::Function_MetaDataParams[] = {
		{ "Category", "Analysis Plugin | Core" },
		{ "Comment", "//Used for multithreading and other such internal things. Its EXTREMELY important that you turn this into an object reference.\n//Otherwise, GC may come along and wipe this, thinking its not in use (even tho it is).\n" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "Used for multithreading and other such internal things. Its EXTREMELY important that you turn this into an object reference.\nOtherwise, GC may come along and wipe this, thinking its not in use (even tho it is)." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_CreateAnalysisPluginRef_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAnalysisPluginBPLibrary, nullptr, "CreateAnalysisPluginRef", nullptr, nullptr, sizeof(AnalysisPluginBPLibrary_eventCreateAnalysisPluginRef_Parms), Z_Construct_UFunction_UAnalysisPluginBPLibrary_CreateAnalysisPluginRef_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAnalysisPluginBPLibrary_CreateAnalysisPluginRef_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAnalysisPluginBPLibrary_CreateAnalysisPluginRef_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAnalysisPluginBPLibrary_CreateAnalysisPluginRef_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAnalysisPluginBPLibrary_CreateAnalysisPluginRef()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAnalysisPluginBPLibrary_CreateAnalysisPluginRef_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAnalysisPluginBPLibrary_ImportMidiFromDisk_Statics
	{
		struct AnalysisPluginBPLibrary_eventImportMidiFromDisk_Parms
		{
			FString Path;
			FMidiStruct MidiReturn;
			TArray<uint8> ArrayOfMidiBytes;
			FString ErrorLog;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_Path;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_MidiReturn;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_ArrayOfMidiBytes_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_ArrayOfMidiBytes;
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ErrorLog;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_ImportMidiFromDisk_Statics::NewProp_Path = { "Path", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventImportMidiFromDisk_Parms, Path), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_ImportMidiFromDisk_Statics::NewProp_MidiReturn = { "MidiReturn", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventImportMidiFromDisk_Parms, MidiReturn), Z_Construct_UScriptStruct_FMidiStruct, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_ImportMidiFromDisk_Statics::NewProp_ArrayOfMidiBytes_Inner = { "ArrayOfMidiBytes", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_ImportMidiFromDisk_Statics::NewProp_ArrayOfMidiBytes = { "ArrayOfMidiBytes", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventImportMidiFromDisk_Parms, ArrayOfMidiBytes), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_ImportMidiFromDisk_Statics::NewProp_ErrorLog = { "ErrorLog", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventImportMidiFromDisk_Parms, ErrorLog), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAnalysisPluginBPLibrary_ImportMidiFromDisk_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_ImportMidiFromDisk_Statics::NewProp_Path,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_ImportMidiFromDisk_Statics::NewProp_MidiReturn,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_ImportMidiFromDisk_Statics::NewProp_ArrayOfMidiBytes_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_ImportMidiFromDisk_Statics::NewProp_ArrayOfMidiBytes,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_ImportMidiFromDisk_Statics::NewProp_ErrorLog,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAnalysisPluginBPLibrary_ImportMidiFromDisk_Statics::Function_MetaDataParams[] = {
		{ "Category", "Analysis Plugin | Midi Stuff (unfinished)" },
		{ "Comment", "//Allows you to load a midi file into a usable format in unreal engine\n" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "Allows you to load a midi file into a usable format in unreal engine" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_ImportMidiFromDisk_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAnalysisPluginBPLibrary, nullptr, "ImportMidiFromDisk", nullptr, nullptr, sizeof(AnalysisPluginBPLibrary_eventImportMidiFromDisk_Parms), Z_Construct_UFunction_UAnalysisPluginBPLibrary_ImportMidiFromDisk_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAnalysisPluginBPLibrary_ImportMidiFromDisk_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAnalysisPluginBPLibrary_ImportMidiFromDisk_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAnalysisPluginBPLibrary_ImportMidiFromDisk_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAnalysisPluginBPLibrary_ImportMidiFromDisk()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAnalysisPluginBPLibrary_ImportMidiFromDisk_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics
	{
		struct AnalysisPluginBPLibrary_eventMakeSpectrogramColorArray_Parms
		{
			FSpectrogramInput SpectrogramValues;
			int32 ChunkIndex;
			int32 ThreadId;
			TEnumAsByte<FGenerationStatus> ContinueLooping;
			TArray<FColor> color;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_SpectrogramValues;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ChunkIndex_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ChunkIndex;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ThreadId_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ThreadId;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_ContinueLooping;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_color_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_color;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::NewProp_SpectrogramValues = { "SpectrogramValues", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventMakeSpectrogramColorArray_Parms, SpectrogramValues), Z_Construct_UScriptStruct_FSpectrogramInput, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::NewProp_ChunkIndex_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::NewProp_ChunkIndex = { "ChunkIndex", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventMakeSpectrogramColorArray_Parms, ChunkIndex), METADATA_PARAMS(Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::NewProp_ChunkIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::NewProp_ChunkIndex_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::NewProp_ThreadId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::NewProp_ThreadId = { "ThreadId", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventMakeSpectrogramColorArray_Parms, ThreadId), METADATA_PARAMS(Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::NewProp_ThreadId_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::NewProp_ThreadId_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::NewProp_ContinueLooping = { "ContinueLooping", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventMakeSpectrogramColorArray_Parms, ContinueLooping), Z_Construct_UEnum_AnalysisPlugin_FGenerationStatus, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::NewProp_color_Inner = { "color", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::NewProp_color = { "color", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventMakeSpectrogramColorArray_Parms, color), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::NewProp_SpectrogramValues,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::NewProp_ChunkIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::NewProp_ThreadId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::NewProp_ContinueLooping,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::NewProp_color_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::NewProp_color,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::Function_MetaDataParams[] = {
		{ "Category", "Analysis Plugin | Audio Analysis" },
		{ "Comment", "//Generates an array of pixels (one second per chunk). Intended to be turned into a texture. Used internaly for \"Calculate Spectrogram Async\", but avalible to the user in blueprints.\n//@param SpectrogramValues - Input nodes for the fft. Allows you to simplify your setup when it comes to making a thread pool. Best to leave these as constant values once the spectrogram is running.\n//@param ChunkIndex - What index you wish to calculate and generate. This variable should be thread specific.\n//@param ThreadId - Allows you to give the thread calculation offset so that chunks can be generated correctly. Set 0 for a single thread.\n" },
		{ "DisplayName", "(Internal) Make Spectrogram Color Array" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "Generates an array of pixels (one second per chunk). Intended to be turned into a texture. Used internaly for \"Calculate Spectrogram Async\", but avalible to the user in blueprints.\n@param SpectrogramValues - Input nodes for the fft. Allows you to simplify your setup when it comes to making a thread pool. Best to leave these as constant values once the spectrogram is running.\n@param ChunkIndex - What index you wish to calculate and generate. This variable should be thread specific.\n@param ThreadId - Allows you to give the thread calculation offset so that chunks can be generated correctly. Set 0 for a single thread." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAnalysisPluginBPLibrary, nullptr, "MakeSpectrogramColorArray", nullptr, nullptr, sizeof(AnalysisPluginBPLibrary_eventMakeSpectrogramColorArray_Parms), Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics
	{
		struct AnalysisPluginBPLibrary_eventMakeWaveformColorArray_Parms
		{
			FWaveformInput WaveformValues;
			int32 ChunkIndex;
			int32 ThreadId;
			TEnumAsByte<FGenerationStatus> ContinueLooping;
			TArray<FColor> color;
		};
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_WaveformValues;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ChunkIndex_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ChunkIndex;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_ThreadId_MetaData[];
#endif
		static const UE4CodeGen_Private::FIntPropertyParams NewProp_ThreadId;
		static const UE4CodeGen_Private::FBytePropertyParams NewProp_ContinueLooping;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_color_Inner;
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_color;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::NewProp_WaveformValues = { "WaveformValues", nullptr, (EPropertyFlags)0x0010000000000080, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventMakeWaveformColorArray_Parms, WaveformValues), Z_Construct_UScriptStruct_FWaveformInput, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::NewProp_ChunkIndex_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::NewProp_ChunkIndex = { "ChunkIndex", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventMakeWaveformColorArray_Parms, ChunkIndex), METADATA_PARAMS(Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::NewProp_ChunkIndex_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::NewProp_ChunkIndex_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::NewProp_ThreadId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UE4CodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::NewProp_ThreadId = { "ThreadId", nullptr, (EPropertyFlags)0x0010000000000082, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventMakeWaveformColorArray_Parms, ThreadId), METADATA_PARAMS(Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::NewProp_ThreadId_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::NewProp_ThreadId_MetaData)) };
	const UE4CodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::NewProp_ContinueLooping = { "ContinueLooping", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventMakeWaveformColorArray_Parms, ContinueLooping), Z_Construct_UEnum_AnalysisPlugin_FGenerationStatus, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::NewProp_color_Inner = { "color", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FColor, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::NewProp_color = { "color", nullptr, (EPropertyFlags)0x0010000000000180, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AnalysisPluginBPLibrary_eventMakeWaveformColorArray_Parms, color), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::NewProp_WaveformValues,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::NewProp_ChunkIndex,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::NewProp_ThreadId,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::NewProp_ContinueLooping,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::NewProp_color_Inner,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::NewProp_color,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::Function_MetaDataParams[] = {
		{ "Category", "Analysis Plugin | Audio Analysis" },
		{ "Comment", "///Generates an array of pixels (one second per chunk). Intended to be turned into a texture. Used internaly for \"Calculate Spectrogram Async\", but avalible to the user in blueprints.\n//@param WaveformValues - Input nodes for the waveform. Allows you to simplify your setup when it comes to making a thread pool. Best to leave these as constant values once the waveform is generating.\n//@param ChunkIndex - What index you wish to calculate and generate. This variable should be thread specific.\n//@param ThreadId - Allows you to give the thread calculation offset so that chunks can be generated correctly. Set 0 for a single thread.\n" },
		{ "DisplayName", "(Internal) Make Waveform Color Array" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
		{ "ToolTip", "Generates an array of pixels (one second per chunk). Intended to be turned into a texture. Used internaly for \"Calculate Spectrogram Async\", but avalible to the user in blueprints.\n@param WaveformValues - Input nodes for the waveform. Allows you to simplify your setup when it comes to making a thread pool. Best to leave these as constant values once the waveform is generating.\n@param ChunkIndex - What index you wish to calculate and generate. This variable should be thread specific.\n@param ThreadId - Allows you to give the thread calculation offset so that chunks can be generated correctly. Set 0 for a single thread." },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAnalysisPluginBPLibrary, nullptr, "MakeWaveformColorArray", nullptr, nullptr, sizeof(AnalysisPluginBPLibrary_eventMakeWaveformColorArray_Parms), Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UAnalysisPluginBPLibrary_NoRegister()
	{
		return UAnalysisPluginBPLibrary::StaticClass();
	}
	struct Z_Construct_UClass_UAnalysisPluginBPLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DoneCalculating_MetaData[];
#endif
		static const UE4CodeGen_Private::FMulticastDelegatePropertyParams NewProp_DoneCalculating;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAnalysisPluginBPLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_AnalysisPlugin,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UAnalysisPluginBPLibrary_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UAnalysisPluginBPLibrary_ByteArrayToIntAndChar, "ByteArrayToIntAndChar" }, // 405687217
		{ &Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateFFT, "CalculateFFT" }, // 434240642
		{ &Z_Construct_UFunction_UAnalysisPluginBPLibrary_CalculateSpectrogramAsync, "CalculateSpectrogramAsync" }, // 3324704989
		{ &Z_Construct_UFunction_UAnalysisPluginBPLibrary_CreateAnalysisPluginRef, "CreateAnalysisPluginRef" }, // 1538911075
		{ &Z_Construct_UFunction_UAnalysisPluginBPLibrary_ImportMidiFromDisk, "ImportMidiFromDisk" }, // 119073782
		{ &Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeSpectrogramColorArray, "MakeSpectrogramColorArray" }, // 845903177
		{ &Z_Construct_UFunction_UAnalysisPluginBPLibrary_MakeWaveformColorArray, "MakeWaveformColorArray" }, // 824967775
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAnalysisPluginBPLibrary_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Category", "Analysis Plugin | Core" },
		{ "IncludePath", "AnalysisPluginBPLibrary.h" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAnalysisPluginBPLibrary_Statics::NewProp_DoneCalculating_MetaData[] = {
		{ "Category", "Analysis Plugin | Audio Analysis" },
		{ "ModuleRelativePath", "Public/AnalysisPluginBPLibrary.h" },
	};
#endif
	const UE4CodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UAnalysisPluginBPLibrary_Statics::NewProp_DoneCalculating = { "DoneCalculating", nullptr, (EPropertyFlags)0x0010000010080000, UE4CodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAnalysisPluginBPLibrary, DoneCalculating), Z_Construct_UDelegateFunction_AnalysisPlugin_GeneratedTextures__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UAnalysisPluginBPLibrary_Statics::NewProp_DoneCalculating_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAnalysisPluginBPLibrary_Statics::NewProp_DoneCalculating_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAnalysisPluginBPLibrary_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAnalysisPluginBPLibrary_Statics::NewProp_DoneCalculating,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAnalysisPluginBPLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAnalysisPluginBPLibrary>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UAnalysisPluginBPLibrary_Statics::ClassParams = {
		&UAnalysisPluginBPLibrary::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UAnalysisPluginBPLibrary_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UAnalysisPluginBPLibrary_Statics::PropPointers),
		0,
		0x008000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UAnalysisPluginBPLibrary_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UAnalysisPluginBPLibrary_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAnalysisPluginBPLibrary()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UAnalysisPluginBPLibrary_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UAnalysisPluginBPLibrary, 3990444812);
	template<> ANALYSISPLUGIN_API UClass* StaticClass<UAnalysisPluginBPLibrary>()
	{
		return UAnalysisPluginBPLibrary::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UAnalysisPluginBPLibrary(Z_Construct_UClass_UAnalysisPluginBPLibrary, &UAnalysisPluginBPLibrary::StaticClass, TEXT("/Script/AnalysisPlugin"), TEXT("UAnalysisPluginBPLibrary"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAnalysisPluginBPLibrary);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
