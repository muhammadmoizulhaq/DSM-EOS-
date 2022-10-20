// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SampleMultiplayer : ModuleRules
{
	public SampleMultiplayer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "OnlineSubsystem", "OnlineSubsystemEOS", "OnlineSubsystemUtils" });
		
		//PrivateDefinitions.Add("WITH_EOS_SDK=true");
		PrivateDefinitions.Add("WITH_EOS_RTC=true");

        PublicIncludePaths.AddRange(new string[]
        {
            "SampleMultiplayer/EOS/SDK/Include",
        });

        //PublicIncludePaths.Add(Path.Combine(EngineDirectory, "Plugins/Online/OnlineSubsystemEOS/Source/OnlineSubsystemEOS/Private/"));

        //PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "EOS/SDK/Include"));
    }
}
