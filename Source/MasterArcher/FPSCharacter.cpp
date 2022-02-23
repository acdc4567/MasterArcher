// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "FPSPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponBase.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(RootComponent); // Attach camera to end of boom
	FollowCamera->bUsePawnControlRotation = true;

	bUseControllerRotationYaw = 0;

	FPSArms=CreateDefaultSubobject<USkeletalMeshComponent>("FPSArms");
	FPSArms->SetupAttachment(FollowCamera);


}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForwardKeyPressed);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRightKeyPressed);
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);

	PlayerInputComponent->BindAction("Fire",IE_Pressed,this,&AFPSCharacter::Fire);
	PlayerInputComponent->BindAction("Fire",IE_Released,this,&AFPSCharacter::StopFire);

	PlayerInputComponent->BindAction("Reload",IE_Pressed,this,&AFPSCharacter::Reload);

}


void AFPSCharacter::PossessedBy(AController* inController){
	AFPSPlayerController* SPC=Cast<AFPSPlayerController>(inController);
	if(SPC){
		MyPlayerControllerRef=SPC;
		SPC->OnPossessx(this);

	}

}	

void AFPSCharacter::MoveForwardKeyPressed(float Value){

	if(MyPlayerControllerRef&& (Value != 0.0f)){

        const FRotator Rotation{MyPlayerControllerRef->GetControlRotation()};
        const FRotator YawRotation{0, Rotation.Yaw, 0};

        const FVector Direction{FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X)};
        AddMovementInput(Direction, Value);
    }


}



void AFPSCharacter::MoveRightKeyPressed(float Value){

	if(MyPlayerControllerRef&& (Value != 0.0f)){

		const FRotator Rotation{MyPlayerControllerRef->GetControlRotation()};
		const FRotator YawRotation{0, Rotation.Yaw, 0};

		const FVector Direction{FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y)};
		AddMovementInput(Direction, Value);
	}
}

void AFPSCharacter::EquipWeapon(AWeaponBase* Weapon){
    if (!bIsChangingWeapon) {
		if(!bIsReloading){

			
		}
		else{
			bCanFire=0;
			bIsReloading=0;

		}
		//bIsChangingWeapon = 1;

		CurrentWeapon = Weapon;
		ShowWeapon(Weapon);
		bCanFire=1;
		bHasWeapon=1;
    }
}

void AFPSCharacter::ShowWeapon(AWeaponBase* Weapon){
	WeaponSlot_01=Weapon;
	WeaponSlot_01->SetActorHiddenInGame(0);

}

AWeaponBase* AFPSCharacter::SpawnWeapon(AWeaponBase* Weapon){
	AWeaponBase* TempPickupWeapon;
	
	TempPickupWeapon=GetWorld()->SpawnActor<AWeaponBase>(WeaponSlot_01class);
	

	TempPickupWeapon->AttachToComponent(FPSArms,FAttachmentTransformRules::SnapToTargetNotIncludingScale,TempPickupWeapon->SocketName);
	WeaponSlot_01=TempPickupWeapon;

	CurrentWeapon= WeaponSlot_01;

	bHasWeapon=1;



	return TempPickupWeapon;


}













void AFPSCharacter::Fire(){
	if(bCanFire&&bHasWeapon){
		bool bHasAmmo;
		bool bMagFull;
		CurrentWeapon->HasAmmoInMag(bHasAmmo,bMagFull);
		if(bHasAmmo){
			CurrentWeapon->WeaponFire();
			bIsRecoil=1;
		}
		else{
			if(CurrentWeapon->HaveExtraAmmo()){
				Reload();
			}
			else{
				UE_LOG(LogTemp,Warning,TEXT("NoAmmo"));

			}
		}
	}




}
void AFPSCharacter::Reload(){
	if(bHasWeapon){

	
		if(!bIsReloading||!bIsChangingWeapon){
			bool bHasAmmo;
			bool bMagFull;
			CurrentWeapon->HasAmmoInMag(bHasAmmo,bMagFull);
			if(!bMagFull){
				bIsReloading=1;
				bCanFire=0;
				CurrentWeapon->WeaponReload();
				bIsReloading=0;
				bCanFire=1;
			}
		}
	}
	



}


void AFPSCharacter::StopFire(){
	
	bIsRecoil=0;

}








//AFPSCharacter
