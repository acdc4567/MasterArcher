// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "FPSCharacter.h"


// Sets default values
AWeaponBase::AWeaponBase()
{
 	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent=SceneComponent;

	GunMesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	GunMesh->AttachToComponent(SceneComponent,FAttachmentTransformRules::KeepRelativeTransform);



}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}






//AWeaponBase
