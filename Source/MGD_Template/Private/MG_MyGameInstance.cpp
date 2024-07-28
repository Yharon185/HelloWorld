// Fill out your copyright notice in the Description page of Project Settings.


#include "MG_MyGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"

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

void UMG_MyGameInstance::EOSLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId,
                                          const FString& Error)
{
	OnLoginComplete(bWasSuccessful, Error);
}
