// Fill out your copyright notice in the Description page of Project Settings.


#include "MG_ParentClass.h"

#include "Kismet/KismetMathLibrary.h"

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

void AMG_ParentClass::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	float direction = UKismetMathLibrary::Quat_UnrotateVector(GetActorRotation().Quaternion(), GetVelocity()).X;
	
	currentMeshRotation = defaultMeshRotation;
	
	
	if(direction > 0.0f)
	{
		currentMeshRotation.Yaw = -90.0f;
	}
	else if(direction < 0.0f)
	{
		currentMeshRotation.Yaw = 90.0f;
	}

	
	if(GetMesh()->IsSimulatingPhysics() == false)
	{
		GetMesh()->SetRelativeRotation(currentMeshRotation);
	}
}





