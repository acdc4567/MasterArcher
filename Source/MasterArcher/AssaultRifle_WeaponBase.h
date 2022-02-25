// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "AssaultRifle_WeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class MASTERARCHER_API AAssaultRifle_WeaponBase : public AWeaponBase
{
	GENERATED_BODY()
public:
	AAssaultRifle_WeaponBase();

	virtual void WeaponFire() override;

	virtual void WeaponReload() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UAnimSequence* FireAnimation;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UAnimSequence* ReloadAnimation;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UAnimMontage* FireAnimMontage;


	FTimerHandle TH_FireAnim;

	void EndFireAnim();

};
