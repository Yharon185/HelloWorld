// Fill out your copyright notice in the Description page of Project Settings.


#include "MG_MyGameInstance.h"

#include "InterchangeResult.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "GameFramework/GameModeBase.h"
#include "Online/OnlineSessionNames.h"

UMG_MyGameInstance::UMG_MyGameInstance()
{
	FoundSessions = MakeShareable(new FOnlineSessionSearch());
	FoundSessions->MaxSearchResults = 10;
	FoundSessions->bIsLanQuery = true;
	FoundSessions->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);
}

void UMG_MyGameInstance::Init()
{
	Super::Init();

	const IOnlineSubsystem* ossRef = Online::GetSubsystem(GetWorld());

	if (!ossRef)
		return;

	const IOnlineIdentityPtr identityRef = ossRef->GetIdentityInterface();

	if (!identityRef)
		return;
	
	identityRef->OnLoginCompleteDelegates->AddUObject(this, &UMG_MyGameInstance::EOSLoginComplete);

	const IOnlineSessionPtr sessionRef = ossRef->GetSessionInterface();

	if(!sessionRef)
		return;

	sessionRef->OnCreateSessionCompleteDelegates.AddUObject(this, &UMG_MyGameInstance::SessionCreateComplete);

	sessionRef->OnFindSessionsCompleteDelegates.AddUObject(this, &UMG_MyGameInstance::SessionFindComplete);

	sessionRef->OnJoinSessionCompleteDelegates.AddUObject(this, &UMG_MyGameInstance::SessionJoinComplete);
}

void UMG_MyGameInstance::LoginEOS()
{
	const IOnlineSubsystem* ossRef = Online::GetSubsystem(GetWorld());

	if (!ossRef)
		return;

	const IOnlineIdentityPtr identityRef = ossRef->GetIdentityInterface();

	if (!identityRef)
		return;

	// set up account credentials that login expects
	// account portal is a login portal that opens when you try to log in
	FOnlineAccountCredentials accCreds;
	accCreds.Id = FString();
	accCreds.Token = FString();
	accCreds.Type = FString(TEXT("accountportal"));
	

	// run login portal
	identityRef->Login(0,accCreds);
}

bool UMG_MyGameInstance::IsLoggedIn() const
{
	const IOnlineSubsystem* ossRef = Online::GetSubsystem(GetWorld());

	if (!ossRef)
		return false;

	const IOnlineIdentityPtr identityRef = ossRef->GetIdentityInterface();

	if (!identityRef)
		return false;

	return identityRef->GetLoginStatus(0) == ELoginStatus::LoggedIn;
}

FString UMG_MyGameInstance::GetDisplayName() const
{
	if (!IsLoggedIn())
		return FString(TEXT("Display Name"));

	const IOnlineIdentityPtr identityRef = Online::GetSubsystem(GetWorld())->GetIdentityInterface();

	return identityRef->GetPlayerNickname(0);
}

bool UMG_MyGameInstance::IsInSession() const
{
	if (!IsLoggedIn())
		return false;

	const IOnlineSessionPtr sessionRef = Online::GetSubsystem(GetWorld())->GetSessionInterface();

	if (!sessionRef)
		return false;

	const EOnlineSessionState::Type state = sessionRef->GetSessionState(MGSESSION_NAME);

	return state != EOnlineSessionState::NoSession;
}

void UMG_MyGameInstance::HostGame(bool lan)
{
	if (!IsLoggedIn())
		return;

	const IOnlineSessionPtr sessionRef = Online::GetSubsystem(GetWorld())->GetSessionInterface();

	if (!sessionRef)
		return;

	FOnlineSessionSettings settings;
	settings.NumPublicConnections = 2;
	settings.bIsLANMatch = lan;
	settings.bIsDedicated = false;
	settings.bAllowInvites = true;
	settings.bShouldAdvertise = true;
	settings.bUsesPresence = true;
	settings.bUseLobbiesIfAvailable = true;
	settings.Set(SEARCH_KEYWORDS, MGSESSION_NAME.ToString(), EOnlineDataAdvertisementType::ViaOnlineService);
	settings.Set(SEARCH_LOBBIES, true, EOnlineDataAdvertisementType::ViaOnlineService);

	sessionRef->CreateSession(0, MGSESSION_NAME, settings);
}

void UMG_MyGameInstance::FindAndJoinSession()
{
	if (!IsLoggedIn())
		return;

	const IOnlineSessionPtr sessionRef = Online::GetSubsystem(GetWorld())->GetSessionInterface();

	if (!sessionRef)
		return;
	
	sessionRef->FindSessions(0, FoundSessions.ToSharedRef());
}

void UMG_MyGameInstance::StartLobbyGame()
{
	GetWorld()->GetAuthGameMode()->bUseSeamlessTravel = true;
	GetWorld()->ServerTravel("/Game/MyContent/Maps/Lvl_Test", false);
}


void UMG_MyGameInstance::EOSLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
{
	OnLoginComplete(bWasSuccessful, Error);
}

void UMG_MyGameInstance::SessionCreateComplete(FName SessionName, bool bWasSuccessful)
{
	EnableListenServer(true);
	OnSessionCreateComplete(bWasSuccessful);
}

void UMG_MyGameInstance::SessionFindComplete(bool bWasSuccessful)
{
	if (!bWasSuccessful)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find sessions"))
		OnSessionJoinCompleted(false);
		return;
	}

	const IOnlineSubsystem* ossRef = Online::GetSubsystem(GetWorld());

	if (!ossRef)
		return;

	const IOnlineSessionPtr sessionRef = ossRef->GetSessionInterface();

	if (!sessionRef)
		return;

	if (FoundSessions->SearchResults.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("No sessions found"))
		OnSessionJoinCompleted(false);
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Found session attempting to join"))
	sessionRef->JoinSession(0, MGSESSION_NAME, FoundSessions->SearchResults[0]);
	
}

void UMG_MyGameInstance::SessionJoinComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	OnSessionJoinCompleted(Result == EOnJoinSessionCompleteResult::Success);
	
	if (Result != EOnJoinSessionCompleteResult::Success)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to join session"))
		return;
	}

	ClientTravelToSession(0, SessionName);
}
