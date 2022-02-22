// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

class AFPSPlayerController;
class UCameraComponent;
class AWeaponBase;



UCLASS()
class MASTERARCHER_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()
private:


	AFPSPlayerController* MyPlayerControllerRef;
	void MoveForwardKeyPressed(float Value);

	void MoveRightKeyPressed(float Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	AWeaponBase* CurrentWeapon;



public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void PossessedBy(AController* inController);

	FORCEINLINE AWeaponBase* GetCurrentWeapon() const {return CurrentWeapon;}


};
