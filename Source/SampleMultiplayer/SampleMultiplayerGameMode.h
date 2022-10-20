// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SampleMultiplayerGameMode.generated.h"

class APlayerController;

UCLASS(minimalapi)
class ASampleMultiplayerGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	/**
	* override
	* Accept or reject a player attempting to join the server.  Fails login if you set the ErrorMessage to a non-empty string.
	* PreLogin is called before Login.  Significant game time may pass before Login is called
	*
	* @param	Options					The URL options (e.g. name/spectator) the player has passed
	* @param	Address					The network address of the player
	* @param	UniqueId				The unique id the player has passed to the server
	* @param	ErrorMessage			When set to a non-empty value, the player will be rejected using the error message set
	*/
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	/**
	* override
	* Called after a successful login.  This is the first place it is safe to call replicated functions on the PlayerController.
	*/
	virtual void PostLogin(APlayerController* NewPlayer);
	/**
	* All player controller connected to the server.
	*/
	UPROPERTY()
	TArray<APlayerController*> MyNewControllerArr;
};