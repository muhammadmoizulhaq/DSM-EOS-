// Copyright Epic Games, Inc. All Rights Reserved.

#include "SampleMultiplayerGameMode.h"
#include "GameFramework/PlayerController.h"
#include "SMPlayerController.h"

void ASampleMultiplayerGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
}

void ASampleMultiplayerGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	MyNewControllerArr.Add(NewPlayer);

	UE_LOG(LogTemp, Warning, TEXT("Totla Players: %d"), MyNewControllerArr.Num());
}