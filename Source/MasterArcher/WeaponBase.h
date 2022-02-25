// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class USkeletalMesh;
class USkeletalMeshComponent;
class AFPSCharacter;
class AImpactEffex;

UENUM(BlueprintType)
enum class E_WeaponType : uint8
{
	EWT_Pistol UMETA(DisplayName = "Pistol"),
	EWT_AssaultRifle UMETA(DisplayName = "AssaultRifle"),
	EWT_Shotgun UMETA(DisplayName = "Shotgun"),
	EWT_GreandeLauncher UMETA(DisplayName = "GreandeLauncher"),
	EWT_RocketLauncher UMETA(DisplayName = "RocketLauncher"),
	EWT_SniperRifle UMETA(DisplayName = "SniperRifle"),


	EWT_MAX UMETA(DisplayName = "DefaultMAX")
	
};



UENUM(BlueprintType)
enum class E_WeaponSlot : uint8
{
	EWS_FirstSlot UMETA(DisplayName = "FirstSlot"),
	EWS_SecondSlot UMETA(DisplayName = "SecondSlot"),
	
	EWS_MAX UMETA(DisplayName = "DefaultMAX")
	
};




USTRUCT(BlueprintType)
struct FSTR_WeaponData 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMesh* WeaponToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* IconImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsEquipped;


	
};

USTRUCT(BlueprintType)
struct FSTR_AmmoData 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CriticalHitChance;


};



UCLASS()
class MASTERARCHER_API AWeaponBase : public AActor
{
	GENERATED_BODY()
private:
	



public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item, meta = (AllowPrivateAccess = "true"))
	bool bMovingClip;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item,meta=(AllowPrivateAccess="true"))
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item,meta=(AllowPrivateAccess="true"))
	FName ClipBoneName=TEXT("Clip_Bone");
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item,meta=(AllowPrivateAccess="true"))
	float BulletSpread;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item,meta=(AllowPrivateAccess="true"))
	FSTR_AmmoData AmmoData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* TrailFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* ImpactParticles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* BeamParticles;

	bool TraceUnderCrosshairs(FHitResult& OutHitResult,FVector& OutHitLocation); 
	
	void SendBullet();

	bool GetBeamEndLocation(const FVector& MuzzleSocketLocation,FHitResult& OutHitResult);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Impact)
	TSubclassOf<AImpactEffex> IE_HitClass;

public:	
// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	E_WeaponType WeaponType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	FName SocketName=TEXT("WeaponPoint");

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	int CurrentAmmo=30;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	int MaxMagAmmo=30;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	int CurrentTotalAmmo=0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	int MaxTotalAmmo=180;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	float ReloadTime=2.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	bool bFiring=0;


	UFUNCTION(BlueprintCallable)
	virtual void WeaponFire();

	virtual void WeaponReload();

	void HasAmmoInMag(bool &HasAmmo,bool &MagFull);

	bool HaveExtraAmmo();



	virtual void SetMovingClip(bool Value);

	FORCEINLINE USkeletalMeshComponent* GetGunMesh() const { return GunMesh; } 

	FORCEINLINE FName GetClipBoneName() const { return ClipBoneName; } 

	FORCEINLINE bool GetMovingClip() const { return bMovingClip; } 

	FORCEINLINE bool GetFiring() const { return bFiring; } 


};
