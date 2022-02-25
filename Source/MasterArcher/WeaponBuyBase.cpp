// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBuyBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"

// Sets default values
AWeaponBuyBase::AWeaponBuyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunMesh=CreateDefaultSubobject<UStaticMeshComponent>("GunMesh");
	SetRootComponent( GunMesh);

	OverlapSphere=CreateDefaultSubobject<USphereComponent>("OverlapSphere");
	OverlapSphere->SetSphereRadius(175.f);
	OverlapSphere->SetupAttachment(GunMesh);
	//OverlapSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	//OverlapSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility,ECollisionResponse::ECR_Block);
		

	RotatingMovement=CreateDefaultSubobject<URotatingMovementComponent>("RotatingMovement");


}

// Called when the game starts or when spawned
void AWeaponBuyBase::BeginPlay()
{
	Super::BeginPlay();

	MyCharacterRef=Cast<AFPSCharacter>(UGameplayStatics::GetPlayerPawn(this,0));
	
	OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBuyBase::OnSphereOverlap);
	OverlapSphere->OnComponentEndOverlap.AddDynamic(this, &AWeaponBuyBase::OnSphereEndOverlap);
	

}

// Called every frame
void AWeaponBuyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AWeaponBuyBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult){


	if(Cast<AFPSCharacter>(OtherActor)==MyCharacterRef){
		MyCharacterRef->OnInteract.AddDynamic(this,&AWeaponBuyBase::Pickup);
	}


}

void AWeaponBuyBase::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex){

	if(Cast<AFPSCharacter>(OtherActor)==MyCharacterRef){
		MyCharacterRef->OutOfSphere();
		MyCharacterRef->OnInteractEnd.AddDynamic(this,&AWeaponBuyBase::PickupEnd);
	}

}





void AWeaponBuyBase::Pickup(bool bAutomatic){
	
	bool bWeaponSpawned=MyCharacterRef->SpawnWeapon(Weapon);
	if(bWeaponSpawned){
		SetLifeSpan(.2f);
	}

}

void AWeaponBuyBase::PickupEnd(bool bAutomatic){
	
	



}









//AWeaponBuyBase
