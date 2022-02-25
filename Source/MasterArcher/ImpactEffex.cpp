// Fill out your copyright notice in the Description page of Project Settings.


#include "ImpactEffex.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AImpactEffex::AImpactEffex()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AImpactEffex::BeginPlay()
{
	Super::BeginPlay();

	float RandonFInRange=FMath::RandRange(-180.f,180.f);
	const FVector RandomXInRange=FVector(RandonFInRange,HitResult.Normal.Y,HitResult.Normal.Z);

	DecalRotation= UKismetMathLibrary::MakeRotFromX(RandomXInRange);
	EPhysicalSurface TempPhySurf= UPhysicalMaterial::DetermineSurfaceType(HitResult.PhysMaterial.Get());

	switch(TempPhySurf){
		case EPhysicalSurface::SurfaceType1:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ConcreteFX, HitResult.ImpactPoint);
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ConcreteSound,FVector::ZeroVector);
			UGameplayStatics::SpawnDecalAttached(ConcreteDecalMat,FVector(10.f),HitResult.GetComponent(),HitResult.BoneName,HitResult.ImpactPoint,DecalRotation,EAttachLocation::KeepWorldPosition,10.f);
		break;

		case EPhysicalSurface::SurfaceType2:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FleshFX, HitResult.ImpactPoint);
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FleshSound,FVector::ZeroVector);

		break;

		case EPhysicalSurface::SurfaceType_Default:

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DefaultFX, HitResult.ImpactPoint);
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), DefaultSound,FVector::ZeroVector);
			UGameplayStatics::SpawnDecalAttached(DefaultDecalMat,FVector(10.f),HitResult.GetComponent(),HitResult.BoneName,HitResult.ImpactPoint,DecalRotation,EAttachLocation::KeepWorldPosition,10.f);

		break;
	}
}

// Called every frame
void AImpactEffex::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

