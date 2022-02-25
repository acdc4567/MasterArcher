// Fill out your copyright notice in the Description page of Project Settings.


#include "ARAnimInstance.h"
#include "AssaultRifle_WeaponBase.h"

UARAnimInstance::UARAnimInstance(){

}

void UARAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (ARRef == nullptr)
	{
		ARRef = Cast<AAssaultRifle_WeaponBase>(GetOwningActor());
	}
    else{
        bMovingClip=ARRef->GetMovingClip();
		bFiring=ARRef->GetFiring();
    }

}

void UARAnimInstance::NativeInitializeAnimation()
{
	ARRef = Cast<AAssaultRifle_WeaponBase>(GetOwningActor());
    
    
}
