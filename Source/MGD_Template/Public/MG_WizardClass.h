// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MG_WizardClass.generated.h"

UCLASS()
class MGD_TEMPLATE_API AMG_WizardClass : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMG_WizardClass();

	//Moves character based on Axis
	UFUNCTION(BlueprintCallable, Category="Movement")
	void Pure_MoveCharacter(const FVector2D Axis);

	//Move axis of Character
	UPROPERTY(BlueprintReadOnly, Category="Movement")
	FVector2D pMoveAxis;






	
};
