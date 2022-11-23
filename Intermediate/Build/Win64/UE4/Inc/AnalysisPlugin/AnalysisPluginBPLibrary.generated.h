// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FSpectrogramOutput;
struct FMidiStruct;
class UAnalysisPluginBPLibrary;
struct FWaveformInput;
struct FSpectrogramInput;
struct FColor;
#ifdef ANALYSISPLUGIN_AnalysisPluginBPLibrary_generated_h
#error "AnalysisPluginBPLibrary.generated.h already included, missing '#pragma once' in AnalysisPluginBPLibrary.h"
#endif
#define ANALYSISPLUGIN_AnalysisPluginBPLibrary_generated_h

#define ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_161_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FMidiStruct_Statics; \
	ANALYSISPLUGIN_API static class UScriptStruct* StaticStruct();


template<> ANALYSISPLUGIN_API UScriptStruct* StaticStruct<struct FMidiStruct>();

#define ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_148_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FSpectrogramTextures_Statics; \
	ANALYSISPLUGIN_API static class UScriptStruct* StaticStruct();


template<> ANALYSISPLUGIN_API UScriptStruct* StaticStruct<struct FSpectrogramTextures>();

#define ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_129_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FSpectrogramOutput_Statics; \
	ANALYSISPLUGIN_API static class UScriptStruct* StaticStruct();


template<> ANALYSISPLUGIN_API UScriptStruct* StaticStruct<struct FSpectrogramOutput>();

#define ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_50_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FWaveformInput_Statics; \
	ANALYSISPLUGIN_API static class UScriptStruct* StaticStruct();


template<> ANALYSISPLUGIN_API UScriptStruct* StaticStruct<struct FWaveformInput>();

#define ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_17_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FSpectrogramInput_Statics; \
	ANALYSISPLUGIN_API static class UScriptStruct* StaticStruct();


template<> ANALYSISPLUGIN_API UScriptStruct* StaticStruct<struct FSpectrogramInput>();

#define ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_169_DELEGATE \
struct _Script_AnalysisPlugin_eventGeneratedTextures_Parms \
{ \
	FSpectrogramOutput Output; \
}; \
static inline void FGeneratedTextures_DelegateWrapper(const FMulticastScriptDelegate& GeneratedTextures, FSpectrogramOutput Output) \
{ \
	_Script_AnalysisPlugin_eventGeneratedTextures_Parms Parms; \
	Parms.Output=Output; \
	GeneratedTextures.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_175_SPARSE_DATA
#define ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_175_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execByteArrayToIntAndChar); \
	DECLARE_FUNCTION(execImportMidiFromDisk); \
	DECLARE_FUNCTION(execCalculateSpectrogramAsync); \
	DECLARE_FUNCTION(execMakeWaveformColorArray); \
	DECLARE_FUNCTION(execMakeSpectrogramColorArray); \
	DECLARE_FUNCTION(execCalculateFFT); \
	DECLARE_FUNCTION(execCreateAnalysisPluginRef);


#define ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_175_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execByteArrayToIntAndChar); \
	DECLARE_FUNCTION(execImportMidiFromDisk); \
	DECLARE_FUNCTION(execCalculateSpectrogramAsync); \
	DECLARE_FUNCTION(execMakeWaveformColorArray); \
	DECLARE_FUNCTION(execMakeSpectrogramColorArray); \
	DECLARE_FUNCTION(execCalculateFFT); \
	DECLARE_FUNCTION(execCreateAnalysisPluginRef);


#define ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_175_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAnalysisPluginBPLibrary(); \
	friend struct Z_Construct_UClass_UAnalysisPluginBPLibrary_Statics; \
public: \
	DECLARE_CLASS(UAnalysisPluginBPLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AnalysisPlugin"), NO_API) \
	DECLARE_SERIALIZER(UAnalysisPluginBPLibrary)


#define ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_175_INCLASS \
private: \
	static void StaticRegisterNativesUAnalysisPluginBPLibrary(); \
	friend struct Z_Construct_UClass_UAnalysisPluginBPLibrary_Statics; \
public: \
	DECLARE_CLASS(UAnalysisPluginBPLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AnalysisPlugin"), NO_API) \
	DECLARE_SERIALIZER(UAnalysisPluginBPLibrary)


#define ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_175_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAnalysisPluginBPLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAnalysisPluginBPLibrary) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAnalysisPluginBPLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAnalysisPluginBPLibrary); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAnalysisPluginBPLibrary(UAnalysisPluginBPLibrary&&); \
	NO_API UAnalysisPluginBPLibrary(const UAnalysisPluginBPLibrary&); \
public:


#define ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_175_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAnalysisPluginBPLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAnalysisPluginBPLibrary(UAnalysisPluginBPLibrary&&); \
	NO_API UAnalysisPluginBPLibrary(const UAnalysisPluginBPLibrary&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAnalysisPluginBPLibrary); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAnalysisPluginBPLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAnalysisPluginBPLibrary)


#define ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_175_PRIVATE_PROPERTY_OFFSET
#define ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_171_PROLOG
#define ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_175_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_175_PRIVATE_PROPERTY_OFFSET \
	ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_175_SPARSE_DATA \
	ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_175_RPC_WRAPPERS \
	ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_175_INCLASS \
	ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_175_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_175_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_175_PRIVATE_PROPERTY_OFFSET \
	ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_175_SPARSE_DATA \
	ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_175_RPC_WRAPPERS_NO_PURE_DECLS \
	ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_175_INCLASS_NO_PURE_DECLS \
	ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h_175_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> ANALYSISPLUGIN_API UClass* StaticClass<class UAnalysisPluginBPLibrary>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ParEdit_Plugins_AnalysisPlugin_Source_AnalysisPlugin_Public_AnalysisPluginBPLibrary_h


#define FOREACH_ENUM_FMIDITYPE(op) \
	op(NoteOff) \
	op(NoteOn) \
	op(Aftertouch) \
	op(PatchChange) \
	op(ChannelPressure) \
	op(PitchBend) \
	op(SystemMessage) 
#define FOREACH_ENUM_FGENERATIONTYPE(op) \
	op(Waveform) \
	op(Spectrogram) 
#define FOREACH_ENUM_FSPECTROGRAMBANDTYPE(op) \
	op(Left) \
	op(Right) \
	op(Combined) 
#define FOREACH_ENUM_FGENERATIONSTATUS(op) \
	op(Loop) \
	op(InvalidObject) \
	op(DontLoop) 
PRAGMA_ENABLE_DEPRECATION_WARNINGS
