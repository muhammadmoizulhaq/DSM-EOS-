// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineIdentityInterface.h"

#include "SMGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FSessionsDataStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString SessionName;
	UPROPERTY(BlueprintReadWrite)
	FString SessionID;
	UPROPERTY(BlueprintReadWrite)
	int32 SessionPing;
	UPROPERTY(BlueprintReadWrite)
	int32 SessionTotalConnections;
	UPROPERTY(BlueprintReadWrite)
	int32 SessionConnectedConnections;
	UPROPERTY(BlueprintReadWrite)
	FName MapName;
	UPROPERTY(BlueprintReadWrite)
	bool bIsWaitingForSession;
};

USTRUCT(BlueprintType)
struct FUserDataStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString MyPlayerName;
	UPROPERTY(BlueprintReadWrite)
	int32 MyPlayerID;
};

UCLASS()
class SAMPLEMULTIPLAYER_API USMGameInstance : public UGameInstance
{
	GENERATED_BODY()
protected:
	IOnlineSessionPtr MyOnlineSessionPtr;
	IOnlineIdentityPtr MyOnlineIdentityPtr;
	TSharedPtr<FOnlineSessionSearch> MyOnlineSessionSearch;
public:
	USMGameInstance();
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "DSMS|Utils")
	FSessionsDataStruct MySessionsDataStruct;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "DSMS|Utils")
	FUserDataStruct MyUserDataStruct;
	virtual void Init() override;
	void InitSessioning();
	UFUNCTION(BlueprintCallable, Category = "DSMS|Utils")
	void HostSession(FName InSessionName);
	UFUNCTION(BlueprintCallable, Category = "DSMS|Auth")
	void NewLogin(FString InToken);
	void OnNewLoginComplete(int32 InLocalUserNum, bool bWassSuccessful, const FUniqueNetId& InUserId, const FString& InError);
	UFUNCTION(BlueprintCallable, Category = "DSMS|Sessions")
	void CreateNewSession(FName InSessionName);
	void OnCreateSessionComplete(FName InSessionName, bool bWasSuccessful);
	void OnDestroySessionComplete(FName InSessionName, bool bWasSuccessful);
	UFUNCTION(BlueprintCallable, Category = "DSMS|Sessions")
	void FindAllSessions();
	void OnFindSessionComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName InSessionName, EOnJoinSessionCompleteResult::Type InJoinResult);
	UFUNCTION(BlueprintCallable, Category = "DSMS|Sessions")
	void JoinMySessionWithName(FName InSessionName);
	UFUNCTION(BlueprintCallable, Category = "DSMS|Sessions")
	FString JoinSessionWithID(FString InSessionID);
};