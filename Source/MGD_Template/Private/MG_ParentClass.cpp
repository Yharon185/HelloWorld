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

	// Move character based on Y Axis (Might be needed Later)
	AddMovementInput(GetControlRotation().Vector(), Axis.Y);
	
	// Move character based on X axis
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y), Axis.X); 
}



