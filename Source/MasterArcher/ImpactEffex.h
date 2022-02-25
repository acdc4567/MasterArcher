// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ImpactEffex.generated.h"

class USoundBase;
class UMaterial;


UCLASS()
class MASTERARCHER_API AImpactEffex : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AImpactEffex();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta=(ExposeOnSpawn="true"))
	FHitResult HitResult;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta=(ExposeOnSpawn="true"))
	bool bIsUsingHitResult;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* DefaultFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	USoundBase* DefaultSound;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	UMaterial* DefaultDecalMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* ConcreteFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	USoundBase* ConcreteSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	UMaterial* ConcreteDecalMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* FleshFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat, meta = (AllowPrivateAccess = "true"))
	USoundBase* FleshSound;

	

	FRotator DecalRotation;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
