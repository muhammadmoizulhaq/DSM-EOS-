// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/RuntimeOptionsBase.h"

#include "PluginStruct.h"

#include "EpicOnlineServicesSettings.generated.h"

UCLASS(config = Engine, defaultconfig, meta = (DisplayName = "Epic Online Services Core"))
class EPICONLINESERVICECORE_API UEpicOnlineServicesSettings : public URuntimeOptionsBase
{
	GENERATED_BODY()
public:
	/**
	* If set to true will be used as server hosted sessions, default false.
	*/
	UPROPERTY(Config, EditAnywhere, Category = "Epic Online Services Core | Settings")
	bool IsDedicatedServer = false;
	UPROPERTY(Config, EditAnywhere, Category = "Epic Online Services Core | Settings")
	FConfigData CoreConfigData;
};