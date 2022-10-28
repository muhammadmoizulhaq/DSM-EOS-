// Fill out your copyright notice in the Description page of Project Settings.

#include "SMGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

#include "OnlineSubsystemEOS.h"
//#include "OnlineSubsystemEOS.cpp"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"

USMGameInstance::USMGameInstance()
{
}

void USMGameInstance::Init()
{
	Super::Init();

	/*FString MySessionName = "";
	if (FParse::Value(FCommandLine::Get(), TEXT("EOSLobbySession"), MySessionName))
	{
		MySessionName = MySessionName.Replace(TEXT("="), TEXT(""));
		MySessionsDataStruct.SessionName = MySessionName;
		UE_LOG(LogTemp, Warning, TEXT("Running Session Name: %s"), *MySessionsDataStruct.SessionName);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Session Name found. Setting to default name."));
	}
	InitSessioning();
	if (IsDedicatedServerInstance())
	{
		NewLogin(TEXT("moiz"));
		UE_LOG(LogTemp, Warning, TEXT("Dedicated Server Instance is running!"));
		if (MySessionsDataStruct.SessionName.IsEmpty())
		{
			if (GetWorld()->URL.Port == 7777)
			{
				MySessionsDataStruct.MapName = TEXT("Server_Lobby");
				HostSession(MySessionsDataStruct.MapName);
			}
			else if (GetWorld()->URL.Port == 7778)
			{
				MySessionsDataStruct.MapName = TEXT("Server_Room");
				HostSession(MySessionsDataStruct.MapName);
			}
		}
		else
		{
			MySessionsDataStruct.MapName = FName(*MySessionsDataStruct.SessionName);
			HostSession(MySessionsDataStruct.MapName);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Dedicated Server Instance is not running!"));
	}*/
}

void USMGameInstance::InitSessioning()
{
	//IOnlineSubsystem* MyOnlineSubsystem = IOnlineSubsystem::Get();
	const IOnlineSubsystem* MyOnlineSubsystem = FOnlineSubsystemEOS::Get(EOS_SUBSYSTEM);
	if (MyOnlineSubsystem != nullptr)
	{
		MyOnlineSessionPtr = MyOnlineSubsystem->GetSessionInterface();
		if (IsRunningClientOnly())
		{
			MyOnlineIdentityPtr = MyOnlineSubsystem->GetIdentityInterface();
		}
		if (MyOnlineSessionPtr.IsValid() && MyOnlineIdentityPtr.IsValid())
		{
			MyOnlineSessionPtr->OnCreateSessionCompleteDelegates.AddUObject(this, &USMGameInstance::OnCreateSessionComplete);
			MyOnlineSessionPtr->OnDestroySessionCompleteDelegates.AddUObject(this, &USMGameInstance::OnDestroySessionComplete);
			MyOnlineSessionPtr->OnFindSessionsCompleteDelegates.AddUObject(this, &USMGameInstance::OnFindSessionComplete);
			MyOnlineSessionPtr->OnJoinSessionCompleteDelegates.AddUObject(this, &USMGameInstance::OnJoinSessionComplete);
			if (IsRunningClientOnly())
			{
				MyOnlineIdentityPtr->OnLoginCompleteDelegates->AddUObject(this, &USMGameInstance::OnNewLoginComplete);
			}
			if (IsRunningClientOnly())
			{
				MyOnlineSessionSearch = MakeShareable(new FOnlineSessionSearch());
				if (MyOnlineSessionSearch.IsValid())
				{
					MyOnlineSessionSearch->bIsLanQuery = false;
					UE_LOG(LogTemp, Warning, TEXT("Server Starting session search!"));
					MyOnlineSessionPtr->FindSessions(0, MyOnlineSessionSearch.ToSharedRef());
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Subsystem!"));
	}
}

void USMGameInstance::HostSession(FName InSessionName)
{
	if (MyOnlineSessionPtr.IsValid())
	{
		auto MyExistingSession = MyOnlineSessionPtr->GetNamedSession(InSessionName);;
		if (MyExistingSession != nullptr)
		{
			MyOnlineSessionPtr->DestroySession(InSessionName);
		}
		else
		{
			CreateNewSession(InSessionName);
		}
	}
}

void USMGameInstance::NewLogin(FString InToken)
{
	if (MyOnlineIdentityPtr.IsValid())
	{
		FOnlineAccountCredentials MyOnlineAccountCredentials;
		//MyOnlineAccountCredentials.Id = InUserID;
		MyOnlineAccountCredentials.Id = FString("127.0.0.1:7777");
		MyOnlineAccountCredentials.Token = InToken;
		//MyOnlineAccountCredentials.Token = FString();
		MyOnlineAccountCredentials.Type = FString("developer");

		MyOnlineIdentityPtr->Login(0, MyOnlineAccountCredentials);
	}
}

void USMGameInstance::OnNewLoginComplete(int32 InLocalUserNum, bool bWassSuccessful, const FUniqueNetId& InUserId, const FString& InError)
{
	UE_LOG(LogTemp, Warning, TEXT("LoggedIn: %d"), bWassSuccessful);
	if (bWassSuccessful && MyOnlineIdentityPtr.IsValid())
	{
		MyUserDataStruct.MyPlayerName = MyOnlineIdentityPtr.Get()->GetPlayerNickname(InUserId);
		UE_LOG(LogTemp, Warning, TEXT("%s Logged In."), *MyUserDataStruct.MyPlayerName);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Login Error: %s"), *InError);
	}
}

void USMGameInstance::CreateNewSession(FName InSessionName)
{
	MySessionsDataStruct.SessionName = InSessionName.ToString();
	if (MyOnlineSessionPtr.IsValid())
	{
		FOnlineSessionSettings MyOnlineSessionSetting;
		MyOnlineSessionSetting.bAllowInvites = true;
		MyOnlineSessionSetting.bAllowJoinInProgress = true;
		MyOnlineSessionSetting.bAllowJoinViaPresence = true;
		MyOnlineSessionSetting.bIsDedicated = true;
		MyOnlineSessionSetting.bIsLANMatch = false;
		MyOnlineSessionSetting.bShouldAdvertise = true;
		MyOnlineSessionSetting.bUseLobbiesIfAvailable = true;
		MyOnlineSessionSetting.bUseLobbiesVoiceChatIfAvailable = true;
		MyOnlineSessionSetting.bUsesPresence = true;
		MyOnlineSessionSetting.bUsesStats = true;
		MyOnlineSessionSetting.NumPrivateConnections = 5;
		MyOnlineSessionSetting.NumPublicConnections = 5;
		MyOnlineSessionSetting.Set(SEARCH_KEYWORDS, FString(InSessionName.ToString()), EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

		MyOnlineSessionPtr->CreateSession(0, InSessionName, MyOnlineSessionSetting);
	}
}

void USMGameInstance::OnCreateSessionComplete(FName InSessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UWorld* MyWorld = GetWorld();
		if (!ensure(MyWorld != nullptr)) { return; }
		UE_LOG(LogTemp, Warning, TEXT("Session Created."));
		FString MySessionInfo = MyOnlineSessionPtr->GetNamedSession(InSessionName)->GetSessionIdStr();
		UE_LOG(LogTemp, Warning, TEXT("Created Session ID: %s"), *MySessionInfo);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Session is not created."));
	}
}

void USMGameInstance::OnDestroySessionComplete(FName InSessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Warning, TEXT("Matchmaking session Destroyed."));
		CreateNewSession(MySessionsDataStruct.MapName);
	}
}

void USMGameInstance::FindAllSessions()
{
	MyOnlineSessionSearch = MakeShareable(new FOnlineSessionSearch());

	if (MyOnlineSessionSearch.IsValid())
	{
		MyOnlineSessionSearch->bIsLanQuery = false;
		UE_LOG(LogTemp, Warning, TEXT("Client Invoked: Starting to find Sessions."));
		MyOnlineSessionPtr->FindSessions(0, MyOnlineSessionSearch.ToSharedRef());
	}
}

void USMGameInstance::OnFindSessionComplete(bool bWasSuccessful)
{
	if (bWasSuccessful && MyOnlineSessionSearch.IsValid())
	{
		if (!IsRunningClientOnly())
		{
			UE_LOG(LogTemp, Warning, TEXT("Find Session Complete."));
			for (FOnlineSessionSearchResult& MyOnlineSessionSearchResult : MyOnlineSessionSearch->SearchResults)
			{
				UE_LOG(LogTemp, Warning, TEXT("Found Session ID: %s"), *MyOnlineSessionSearchResult.GetSessionIdStr());
				FString MyName;
				if (MyOnlineSessionSearchResult.Session.SessionSettings.Get(SEARCH_KEYWORDS, MyName))
				{
					UE_LOG(LogTemp, Warning, TEXT("Session Name: %s"), *MyName);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("No Session Name found!"));
				}
			}
		}
		else
		{
			if (!ensure(UGameplayStatics::GetPlayerController(this, 0) != nullptr)) { return; }
			if (UGameplayStatics::GetPlayerController(this, 0) != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Finished finding sessions."));
				for (FOnlineSessionSearchResult& MyOnlineSessionSearchResult : MyOnlineSessionSearch->SearchResults)
				{
					UE_LOG(LogTemp, Warning, TEXT("Found Session named: %s"), *MyOnlineSessionSearchResult.GetSessionIdStr());
					FString MySearchName;
					MyOnlineSessionSearchResult.Session.SessionSettings.Get(TEXT("EOSLobbySession"), MySearchName);
					//MySessionsDataStruct->SessionName = MyOnlineSessionSearchResult.GetSessionIdStr();
					MySessionsDataStruct.SessionName = MyOnlineSessionSearchResult.Session.GetSessionIdStr();
					MySessionsDataStruct.SessionPing = MyOnlineSessionSearchResult.PingInMs;
					MySessionsDataStruct.SessionTotalConnections = MyOnlineSessionSearchResult.Session.SessionSettings.NumPublicConnections;;
					MySessionsDataStruct.SessionConnectedConnections = MyOnlineSessionSearchResult.Session.NumOpenPublicConnections;
				}
			}
			if (MySessionsDataStruct.bIsWaitingForSession)
			{
				UE_LOG(LogTemp, Warning, TEXT("Client is about to connect."));
				MySessionsDataStruct.bIsWaitingForSession = false;
				FString MySessionNameToSeaarch = FString::FromInt(MyUserDataStruct.MyPlayerID) + "_UserSession";
				JoinMySessionWithName(*MySessionNameToSeaarch);
			}
		}
	}
}

void USMGameInstance::OnJoinSessionComplete(FName InSessionName, EOnJoinSessionCompleteResult::Type InJoinResult)
{
	if (!MyOnlineSessionPtr.IsValid()) { return; }
	FString MyAddress;
	if (!MyOnlineSessionPtr->GetResolvedConnectString(InSessionName, MyAddress))
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not get connect string."));
		return;
	}
	APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (MyPlayerController)
	{
		MyPlayerController->ClientTravel(MyAddress, ETravelType::TRAVEL_Absolute);
	}
	UE_LOG(LogTemp, Warning, TEXT("Session Joined."));
}

void USMGameInstance::JoinMySessionWithName(FName InSessionName)
{
	if (MyOnlineSessionPtr.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Session Find (join by name): %s"), *InSessionName.ToString());
		for (FOnlineSessionSearchResult& MyOnlineSessionSearchResult : MyOnlineSessionSearch->SearchResults)
		{
			FString MySessionName;
			if (MyOnlineSessionSearchResult.Session.SessionSettings.Get(TEXT("EOSLobbySession"), MySessionName))
			{
				UE_LOG(LogTemp, Warning, TEXT("Found session to join: %s"), *MyOnlineSessionSearchResult.GetSessionIdStr());
				MyOnlineSessionPtr->JoinSession(0, *MyOnlineSessionSearchResult.GetSessionIdStr(), MyOnlineSessionSearchResult);
				MySessionsDataStruct.SessionID = *MyOnlineSessionSearchResult.GetSessionIdStr();
				MySessionsDataStruct.SessionID = *MyOnlineSessionSearchResult.GetSessionIdStr();
				break;
			}
		}
	}
}

FString USMGameInstance::JoinSessionWithID(FString InSessionID)
{
	for (FOnlineSessionSearchResult& MyOnlineSessionSearchResult : MyOnlineSessionSearch->SearchResults)
	{
		if (*MyOnlineSessionSearchResult.GetSessionIdStr() == InSessionID)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found session to join: %s"), *MyOnlineSessionSearchResult.GetSessionIdStr());
			MyOnlineSessionPtr->JoinSession(0, *MyOnlineSessionSearchResult.GetSessionIdStr(), MyOnlineSessionSearchResult);
			MySessionsDataStruct.SessionID = *MyOnlineSessionSearchResult.GetSessionIdStr();
			return MySessionsDataStruct.SessionID;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Session entered not found!"));
	return FString(TEXT("No session joined"));
}