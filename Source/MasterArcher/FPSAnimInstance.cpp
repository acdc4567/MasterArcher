// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAnimInstance.h"

#include "FPSCharacter.h"


UFPSAnimInstance::UFPSAnimInstance(){
    
}

void UFPSAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (ShooterCharacter == nullptr)
	{
		ShooterCharacter = Cast<AFPSCharacter>(TryGetPawnOwner());
	}
    else if (ShooterCharacter){
        CurrentWeaponType=ShooterCharacter->GetCurrentWeapon()->WeaponType;

    }
}

void UFPSAnimInstance::NativeInitializeAnimation()
{
	ShooterCharacter = Cast<AFPSCharacter>(TryGetPawnOwner());
}