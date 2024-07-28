// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MG_MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MGD_TEMPLATE_API UMG_MyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
virtual void Init() override;
	
	UFUNCTION(BlueprintCallable, Category="Login")
	void LoginEOS();

	UFUNCTION(BlueprintPure, Category="Login")
	bool IsLoggedIn() const;

	UFUNCTION(BlueprintPure, Category="User")
	FString GetDisplayName() const;
	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category="Login")
	void OnLoginComplete(bool success, const FString& error);

	
private:
	// runs when EOS login completes
	void EOSLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);
};
