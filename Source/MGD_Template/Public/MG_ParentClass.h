// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MG_ParentClass.generated.h"

UCLASS()
class MGD_TEMPLATE_API AMG_ParentClass : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMG_ParentClass();

	//Moves character based on Axis
	UFUNCTION(BlueprintCallable, Category="Movement")
	void Pure_MoveCharacter(const FVector2D Axis);

	//Move axis of Character
	UPROPERTY(BlueprintReadOnly, Category="Movement")
	FVector2D pMoveAxis;


public:
	//Replicated pitch incase i need it
	//UPROPERTY(BlueprintReadOnly, Category="Pitch")
	//float pRepPtch;
	
FRotator defaultMeshRotation;
	virtual void BeginPlay() override;



	
};
