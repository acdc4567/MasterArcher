// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "FPSCharacter.h"
#include "Kismet/KismetMathLibrary.h"


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





void AWeaponBase::WeaponFire(){

	CurrentAmmo-=1;

}




void AWeaponBase::WeaponReload(){
	CurrentAmmo=FMath::Min(MaxMagAmmo,CurrentTotalAmmo);
	CurrentTotalAmmo-=CurrentAmmo;


}


void AWeaponBase::HasAmmoInMag(bool &HasAmmo,bool &MagFull){
	
	HasAmmo=CurrentAmmo>0;
	MagFull=CurrentAmmo==MaxMagAmmo;




}





bool AWeaponBase::HaveExtraAmmo(){
	
	return CurrentTotalAmmo>0;

}







//AWeaponBase
