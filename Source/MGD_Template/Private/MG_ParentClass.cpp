// Fill out your copyright notice in the Description page of Project Settings.


#include "MG_ParentClass.h"

// Sets default values
AMG_ParentClass::AMG_ParentClass()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

void AMG_ParentClass::Pure_MoveCharacter(const FVector2D Axis)
{
	// update axis 
	pMoveAxis = Axis;
	
	FRotator direction = defaultMeshRotation;
	
	
	if(-Axis.Y > 0.0f)
	{
		direction.Yaw = 90.0f;
	}
	else if(-Axis.Y < 0.0f)
	{
		direction.Yaw = -90.0f;
	}

	GetMesh()->SetRelativeRotation(direction);
	



	
	// Move character based on X axis
	//AddMovementInput(FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y), -Axis.X);

	// Move character based on Y Axis (Might be needed Later)
	AddMovementInput(GetControlRotation().Vector(), Axis.Y);

	
}

void AMG_ParentClass::BeginPlay()
{
	Super::BeginPlay();
	defaultMeshRotation = GetMesh()->GetRelativeRotation();
}





