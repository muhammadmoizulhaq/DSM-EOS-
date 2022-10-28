// Copyright Epic Games, Inc. All Rights Reserved.

#include "EpicOnlineServiceCore.h"
#include "Core.h"
#include "Modules/ModuleManager.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FEpicOnlineServiceCoreModule"

void FEpicOnlineServiceCoreModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	// Get the base directory of this plugin
	FString BaseDir = IPluginManager::Get().FindPlugin("EpicOnlineServiceCore")->GetBaseDir();
	// Add on the relative location of the third party dll and load it
	FString LibraryPath;
#if PLATFORM_WINDOWS
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/EpicOnlineServiceCoreLibrary/Win64/EOSSDK-Win64-Shipping.dll"));
#elif PLATFORM_MAC
    LibraryPath = FPaths::Combine(*BaseDir, TEXT("Source/ThirdParty/EpicOnlineServiceCoreLibrary/Mac/Release/libEOSSDK-Mac-Shipping.dylib"));
#elif PLATFORM_LINUX
	LibraryPath = FPaths::Combine(*BaseDir, TEXT("Binaries/ThirdParty/EpicOnlineServiceCoreLibrary/Linux/x86_64-unknown-linux-gnu/libEOSSDK-Linux-Shipping.so"));
#endif // PLATFORM_WINDOWS

	EOSCoreHandle = !LibraryPath.IsEmpty() ? FPlatformProcess::GetDllHandle(*LibraryPath) : nullptr;

	if (EOSCoreHandle)
	{
		// Call the test function in the third party library that opens a message box
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("EOSCore Library", "Successfully load eos core library"));
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("EOSCore Library Error", "Failed to load eos core library"));
	}
}

void FEpicOnlineServiceCoreModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	// Free the dll handle
	FPlatformProcess::FreeDllHandle(EOSCoreHandle);
	EOSCoreHandle = nullptr;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEpicOnlineServiceCoreModule, EpicOnlineServiceCore)