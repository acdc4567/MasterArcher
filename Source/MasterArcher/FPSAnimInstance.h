// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WeaponBase.h"
#include "FPSAnimInstance.generated.h"

class AFPSCharacter;

/**
 * 
 */
UCLASS()
class MASTERARCHER_API UFPSAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UFPSAnimInstance();

	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);

	virtual void NativeInitializeAnimation() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bRecoil;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bReloading;

protected:


	void OnFireWeapon(E_WeaponType WeaponType);

	void OnStopFireWeapon(bool bAutomatic);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	AFPSCharacter* ShooterCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	E_WeaponType CurrentWeaponType;




};
