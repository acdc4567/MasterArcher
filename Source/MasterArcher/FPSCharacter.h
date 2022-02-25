// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeaponBase.h"
#include "FPSCharacter.generated.h"


class AFPSPlayerController;
class UCameraComponent;

class USkeletalMeshComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFireWeaponSignature,E_WeaponType, WeaponType );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStopFireWeaponSignature,bool, bAutomatic );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractSignature,bool, bAutomatic );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractEndSignature,bool, bAutomatic );


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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FPSArms;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	AWeaponBase* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	AWeaponBase* WeaponSlot_01;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	AWeaponBase* WeaponSlot_02;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeaponBase>  WeaponSlot_01class;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AWeaponBase> WeaponSlot_02class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	bool bCanFire=1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	bool bIsReloading=0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	bool bIsRecoil=0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	bool bIsChangingWeapon=0;

	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* ReloadMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	E_WeaponSlot WeaponSlotEnum=E_WeaponSlot::EWS_FirstSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	bool bSlot1Full;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	bool bSlot2Full;

	





public:
	// Sets default values for this character's properties
	AFPSCharacter();

	FTransform ClipTransform;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	FTransform LHandTransform;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	bool bHasWeapon=0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(AWeaponBase* Weapon);

	void ShowWeapon(AWeaponBase* Weapon);

	UFUNCTION(BlueprintCallable)
	void GrabClip();

	UFUNCTION(BlueprintCallable)
	void ReleaseClip();

	UFUNCTION(BlueprintCallable)
	void ReloadEnd();

	void Fire();

	void StopFire();


	void Reload();

	void InteractKeyPressed();

	void Key1Pressed();

	void Key2Pressed();
	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void PossessedBy(AController* inController);

	FORCEINLINE AWeaponBase* GetCurrentWeapon() const {return CurrentWeapon;}

	FORCEINLINE bool GetRecoil() const {return bIsRecoil;}
	FORCEINLINE bool GetReloading() const {return bIsReloading;}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Animation)
	USceneComponent* HandSceneComponent;

	



	UPROPERTY(BlueprintAssignable,Category="Events")
	FOnFireWeaponSignature OnFireWeapon;

	UPROPERTY(BlueprintAssignable,Category="Events")
	FOnStopFireWeaponSignature OnStopFireWeapon;

	UPROPERTY(BlueprintAssignable,Category="Events")
	FOnInteractSignature OnInteract;

	UPROPERTY(BlueprintAssignable,Category="Events")
	FOnInteractEndSignature OnInteractEnd;

	UFUNCTION(BlueprintCallable)
	bool SpawnWeapon(TSubclassOf<AWeaponBase> Weapon);

	void OutOfSphere();

};
