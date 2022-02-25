// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "FPSCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/SkeletalMeshSocket.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "ImpactEffex.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
	
	PrimaryActorTick.bCanEverTick = true;

	GunMesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	RootComponent=GunMesh;


}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}


void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}


void AWeaponBase::WeaponFire(){

	CurrentAmmo-=1;

	SendBullet();

}


void AWeaponBase::SetMovingClip(bool Value){
	bMovingClip=Value;


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


bool AWeaponBase::TraceUnderCrosshairs(FHitResult& OutHitResult,FVector& OutHitLocation){

	FVector2D ViewportSize;
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}

	
	FVector2D CrosshairLocation(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);
	FVector CrosshairWorldPosition;
	FVector CrosshairWorldDirection;

	
	bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(UGameplayStatics::GetPlayerController(this, 0),CrosshairLocation,CrosshairWorldPosition,CrosshairWorldDirection);
	if (bScreenToWorld)
	{
		const FVector Start{ CrosshairWorldPosition };
		const FVector End{ Start + CrosshairWorldDirection * 50000.f };
		OutHitLocation = End;
		GetWorld()->LineTraceSingleByChannel(
			OutHitResult,
			Start,
			End,
			ECollisionChannel::ECC_Visibility);
		if (OutHitResult.bBlockingHit)
		{
			OutHitLocation = OutHitResult.Location;
			return true;
		}
	}
	return false;






}

void AWeaponBase::SendBullet()
{
	
	const USkeletalMeshSocket* BarrelSocket=GunMesh->GetSocketByName("BarrelSocket");
	if (BarrelSocket)
	{
		const FTransform SocketTransform = BarrelSocket->GetSocketTransform(GunMesh);

		

		FHitResult BeamHitResult;
		bool bBeamEnd = GetBeamEndLocation(SocketTransform.GetLocation(), BeamHitResult);
		if (bBeamEnd)
		{
	
			if (BeamHitResult.Actor.IsValid())
			{
				//UE_LOG(MyLog, Log, TEXT("You hit: %s"), (*BeamHitResult)->GetActor()->GetName());

				//IBulletHitInterface* BulletHitInterface = Cast<IBulletHitInterface>(BeamHitResult.Actor.Get());
				/*
				if (BulletHitInterface)
				{
					BulletHitInterface->BulletHit_Implementation(BeamHitResult, this, GetController());
				}
				*/
				//AEnemy* HitEnemy = Cast<AEnemy>(BeamHitResult.Actor.Get());
				/*
				if (HitEnemy)
				{
					int32 Damage{};
					if (BeamHitResult.BoneName.ToString() == HitEnemy->GetHeadBone())
					{
						// Head shot
						Damage = EquippedWeapon->GetHeadShotDamage();
						UGameplayStatics::ApplyDamage(
							BeamHitResult.Actor.Get(),
							Damage,
							GetController(),
							this,
							UDamageType::StaticClass());
						HitEnemy->ShowHitNumber(Damage, BeamHitResult.Location, true);
					}
					else
					{
						// Body shot
						Damage = EquippedWeapon->GetDamage();
						UGameplayStatics::ApplyDamage(
							BeamHitResult.Actor.Get(),
							Damage,
							GetController(),
							this,
							UDamageType::StaticClass());
						HitEnemy->ShowHitNumber(Damage, BeamHitResult.Location, false);
					}
					
					
				}*/
			}
			else
			{
				
				if (ImpactParticles)
				{
					
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactParticles,BeamHitResult.Location);
						
						
				}
			}
			

			
			UParticleSystemComponent* Beam = UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				BeamParticles,
				SocketTransform);

			if (Beam)
			{
				Beam->SetVectorParameter(FName("Target"), BeamHitResult.Location);
			}

			
			FTransform TempTransform ;
			TempTransform.SetLocation(BeamHitResult.ImpactPoint);
			TempTransform.SetRotation(FQuat(0,0,0,0));
			TempTransform.SetScale3D(FVector(1.f,1.f,1.f));

			AImpactEffex* IE_Hit=GetWorld()->SpawnActorDeferred<AImpactEffex>(IE_HitClass,TempTransform);
			if(IE_Hit){
			
				IE_Hit->HitResult=BeamHitResult;
				
				UGameplayStatics::FinishSpawningActor(IE_Hit,TempTransform);
			}

			
		}
	}
}



bool AWeaponBase::GetBeamEndLocation(const FVector& MuzzleSocketLocation,FHitResult& OutHitResult)
{
	FVector OutBeamLocation;
	
	FHitResult CrosshairHitResult;
	bool bCrosshairHit = TraceUnderCrosshairs(CrosshairHitResult, OutBeamLocation);

	if (bCrosshairHit)
	{
		
		OutBeamLocation = CrosshairHitResult.Location;
	}
	else 
	{
		
	}

	
	const FVector WeaponTraceStart{ MuzzleSocketLocation };
	const FVector WeaponTraceEnd{ OutBeamLocation };
	GetWorld()->LineTraceSingleByChannel(OutHitResult,WeaponTraceStart,WeaponTraceEnd,ECollisionChannel::ECC_Visibility);
	if (!OutHitResult.bBlockingHit) 
	{
		OutHitResult.Location = OutBeamLocation;
		return false;
	}

	return true;
}
















//AWeaponBase
