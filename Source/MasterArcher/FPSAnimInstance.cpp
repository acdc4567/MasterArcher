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
        if(ShooterCharacter->GetCurrentWeapon()){
            CurrentWeaponType=ShooterCharacter->GetCurrentWeapon()->WeaponType;
        }
        bRecoil=ShooterCharacter->GetRecoil();
        bReloading=ShooterCharacter->GetReloading();
        
    }
}

void UFPSAnimInstance::NativeInitializeAnimation()
{
	ShooterCharacter = Cast<AFPSCharacter>(TryGetPawnOwner());
    
    
}


void UFPSAnimInstance::OnFireWeapon(E_WeaponType WeaponType){
    bRecoil=1;
}


void UFPSAnimInstance::OnStopFireWeapon(bool bAutomatic){
    bRecoil=0;
}