// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "PluginStruct.generated.h"

USTRUCT(BlueprintType, Category="Epic Online Services Core | Settings")
struct FConfigData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Epic Online Services Core | Settings | Config Data")
	FString ArgumentName;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Epic Online Services Core | Settings | Config Data")
	FString ClientId;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Epic Online Services Core | Settings | Config Data")
	FString ClientSecret;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Epic Online Services Core | Settings | Config Data")
	FString ProductId;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Epic Online Services Core | Settings | Config Data")
	FString SandboxId;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Epic Online Services Core | Settings | Config Data")
	FString DeploymentId;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Epic Online Services Core | Settings | Config Data")
	FString EncryptionKey = "1111111111111111111111111111111111111111111111111111111111111111";
};