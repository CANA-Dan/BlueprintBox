// Some copyright should be here...

using UnrealBuildTool;
using System.IO;

public class AnalysisPlugin : ModuleRules
{
	public AnalysisPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });

		PrivateDependencyModuleNames.AddRange(new string[] { "AudioAnalysisTools", "RuntimeAudioImporter"});

		AddEngineThirdPartyPrivateStaticDependencies(Target, "Kiss_FFT");

		//PrivateIncludePaths.AddRange( new string[] { "AnalysisPlugin/ThirdParty/midifile/include"))});
	}
}
