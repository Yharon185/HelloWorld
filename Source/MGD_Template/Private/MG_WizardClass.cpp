// Fill out your copyright notice in the Description page of Project Settings.


#include "MG_WizardClass.h"

// Sets default values
AMG_WizardClass::AMG_WizardClass()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMG_WizardClass::Pure_MoveCharacter(const FVector2D Axis)
{
	// update axis 
	pMoveAxis = Axis;

	// Move character based on Y Axis
	AddMovementInput(GetControlRotation().Vector(), Axis.Y);
	
	// Move character based on X axis
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y), Axis.X); 
}



