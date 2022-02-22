// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "WeaponBase.generated.h"

class USkeletalMesh;
class USkeletalMeshComponent;
class AFPSCharacter;


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

USTRUCT(BlueprintType)
struct FSTR_WeaponData : public FTableRowBase
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	FName SocketName=TEXT("WeaponPoint");

	


public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	E_WeaponType WeaponType;

};
