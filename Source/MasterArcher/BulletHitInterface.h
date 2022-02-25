// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponBase.h"
#include "BulletHitInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBulletHitInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MASTERARCHER_API IBulletHitInterface
{
	GENERATED_BODY()

	public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void BulletHit(FSTR_AmmoData AmmoData,float Damage,float CriticalDamage,FHitResult HitResult);

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
