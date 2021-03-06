// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Pistol_WeaponBase.generated.h"


/**
 * 
 */
UCLASS()
class MASTERARCHER_API APistol_WeaponBase : public AWeaponBase
{
	GENERATED_BODY()
public:
	APistol_WeaponBase();
	
	virtual void WeaponFire() override;

	virtual void WeaponReload() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	class UAnimSequence* FireAnimation;


};
