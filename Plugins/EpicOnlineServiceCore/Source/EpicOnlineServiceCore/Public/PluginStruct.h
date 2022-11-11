// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "PluginStruct.generated.h"

/** Native version of the UObject based config data */
struct FEpicOnlineServiceArtifactSettings
{
	FString ArtifactName;
	FString ClientId;
	FString ClientSecret;
	FString ProductId;
	FString SandboxId;
	FString DeploymentId;
	FString EncryptionKey;

	void ParseRawArrayEntry(const FString& InRawLine);
};

USTRUCT(BlueprintType, Category="Epic Online Services Core | Settings")
struct FConfigData
{
	GENERATED_BODY()

public:
	/** This needs to match what the launcher passes in the -epicapp command line arg */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EOS Settings")
	FString ArtifactName;
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
	FEpicOnlineServiceArtifactSettings ToNative() const;
};