// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ARAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MASTERARCHER_API UARAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
	UARAnimInstance();

	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);

	virtual void NativeInitializeAnimation() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bMovingClip;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bFiring;


private:
	class AAssaultRifle_WeaponBase* ARRef;


};
