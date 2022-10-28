// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EOSNetworkManager.generated.h"

UCLASS()
class EPICONLINESERVICECORE_API UEOSNetworkManager : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Epic Online Services Core | Init")
	static const UEOSNetworkManager* IntEOSNetworkManager();
};