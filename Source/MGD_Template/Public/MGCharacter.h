// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MGCharacter.generated.h"

UCLASS()
class MGD_TEMPLATE_API AMGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMGCharacter();

	// Move the character based on an axis
	UFUNCTION(BlueprintCallable, Category="Movement")
	void Pure_MoveCharacter(const FVector2D Axis);

	// Rotate the character controller based on axis
	UFUNCTION(BlueprintCallable, Category="Controller")
	void Pure_RotateController(const FVector2D Axis);

public:
	// Move axis of the character
	UPROPERTY(BlueprintReadOnly, Category="Movement")
	FVector2D pMoveAxis;
	
};


