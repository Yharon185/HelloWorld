// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSessionSettings.h"
#include "interfaces/OnlineSessionInterface.h"
#include "MG_MyGameInstance.generated.h"



#define MGSESSION_NAME FName(TEXT("MGSESSION"))
/**
 * 
 */
UCLASS()
class MGD_TEMPLATE_API UMG_MyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMG_MyGameInstance();
	
	virtual void Init() override;
	
	UFUNCTION(BlueprintCallable, Category="Login")
	void LoginEOS();

	UFUNCTION(BlueprintPure, Category="Login")
	bool IsLoggedIn() const;

	UFUNCTION(BlueprintPure, Category="User")
	FString GetDisplayName() const;

	UFUNCTION(BlueprintPure, Category="Session")
	bool IsInSession() const;
	
	UFUNCTION(BlueprintCallable, Category="Session")
	void HostGame(bool lan = true);

	UFUNCTION(BlueprintCallable, Category="Session")
	void FindAndJoinSession();

	UFUNCTION(BlueprintCallable, Category="Session")
	void StartLobbyGame();
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category="Login")
	void OnLoginComplete(bool success, const FString& error);

	UFUNCTION(BlueprintImplementableEvent, category="Session")
	void OnSessionCreateComplete(bool success);

	UFUNCTION(BlueprintImplementableEvent, Category="Session")
	void OnSessionJoinCompleted(bool success);
	
private:
	// runs when EOS login completes
	void EOSLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);

	void SessionCreateComplete(FName SessionName, bool bWasSuccessful);

	void SessionFindComplete(bool bWasSuccessful);

	void SessionJoinComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	TSharedPtr<FOnlineSessionSearch> FoundSessions;
};
