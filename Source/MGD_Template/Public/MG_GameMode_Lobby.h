// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MG_GameMode.h"
#include "MG_GameMode_Lobby.generated.h"

/**
 * 
 */
UCLASS()
class MGD_TEMPLATE_API AMG_GameMode_Lobby : public AMG_GameMode
{
	GENERATED_BODY()


public:

	
protected:
	virtual void OnPostLogin(AController* NewPlayer) override;

	
private:
	
};
