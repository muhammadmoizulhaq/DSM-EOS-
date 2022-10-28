// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class EOSCore : ModuleRules
{
	public EOSCore(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Lib", "EOSSDK-Win64-Shipping.lib"));
			// Delay-load the DLL, so we can load it from the right place first
			PublicDelayLoadDLLs.Add("EOSSDK-Win64-Shipping.dll");
			// Ensure that the DLL is staged along with the executable
			RuntimeDependencies.Add("$(PluginDir)/Binaries/Win64/EOSSDK-Win64-Shipping.dll");
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Mac", "Release", "libEOSSDK-Mac-Shipping.dylib"));
            RuntimeDependencies.Add("$(PluginDir)/Source/ThirdParty/EOSCore/Bin/libEOSSDK-Mac-Shipping.dylib");
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
		{
			string LinusSoPath = Path.Combine("$(PluginDir)", "Binaries", "ThirdParty", "EOSCore", "Linux", "x86_64-unknown-linux-gnu", "libEOSSDK-Linux-Shipping.so");
			PublicAdditionalLibraries.Add(LinusSoPath);
			PublicDelayLoadDLLs.Add(LinusSoPath);
			RuntimeDependencies.Add(LinusSoPath);
		}
	}
}