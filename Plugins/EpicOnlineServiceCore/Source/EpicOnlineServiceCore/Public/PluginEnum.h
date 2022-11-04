// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "PluginEnum.generated.h"

/** Login Mode */
UENUM(BlueprintType, Category="")
enum class ELoginType : uint8
{
	/** Nothing Here */
	NONE = 0 UMETA(DisplayName = "None"),
	/** Login using a user id and password token */
	IDPASSWORD = 1 UMETA(DisplayName = "ID Password"),
	/** Login using an exchange code */
	EXCHANGECODE = 2 UMETA(DisplayName = "Exchange Code"),
	/** Login using a device code */
	DEVICECODE = 3 UMETA(DisplayName = "Device Code"),
	/** Login using credentials from the EOS SDK Dev Auth Tool */
	DEVAUTH = 4 UMETA(DisplayName = "Dev Auth"),
	/** Login using the account portal */
	ACCOUNTPORTAL = 5 UMETA(DisplayName = "Account Portal"),
	/** Login using persistent auth */
	PERSISTENTAUTH = 6 UMETA(DisplayName = "Persistent Auth"),
	/** Login using external auth */
	EXTERNALAUTH = 7 UMETA(DisplayName = "External Auth"),
};

/** Login External Type */
enum class ELoginExternalType : uint8
{
	/** None */
	NONE = 0 UMETA(DisplayName = "None"),
	/** Login using Steam */
	STEAM = 1 UMETA(DisplayName = "Steam"),
};