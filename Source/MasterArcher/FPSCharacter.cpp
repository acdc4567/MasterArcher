// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "FPSPlayerController.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"



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

	HandSceneComponent=CreateDefaultSubobject<USceneComponent>("HandSceneComponent");
	HandSceneComponent->SetupAttachment(RootComponent);

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
	
	PlayerInputComponent->BindAction("Interact",IE_Pressed,this,&AFPSCharacter::InteractKeyPressed);

	PlayerInputComponent->BindAction("Keyboard1",IE_Pressed,this,&AFPSCharacter::Key1Pressed);

	PlayerInputComponent->BindAction("Keyboard2",IE_Pressed,this,&AFPSCharacter::Key2Pressed);


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
	if(WeaponSlot_01){
		WeaponSlot_01->SetActorHiddenInGame(1);
	}
	else{
		if(WeaponSlot_02){
			WeaponSlot_02->SetActorHiddenInGame(1);
		}
	}
	if(Weapon==WeaponSlot_01){
		WeaponSlot_01->SetActorHiddenInGame(0);

	}
	else if(Weapon==WeaponSlot_02){
		WeaponSlot_02->SetActorHiddenInGame(0);
	}

	

}

bool AFPSCharacter::SpawnWeapon(TSubclassOf<AWeaponBase> Weapon){
	
	switch (WeaponSlotEnum)
	{
		case E_WeaponSlot::EWS_FirstSlot:
			if(!bSlot1Full){
				AWeaponBase* TempPickupWeapon;
	
				TempPickupWeapon=GetWorld()->SpawnActor<AWeaponBase>(Weapon);
				
				const USkeletalMeshSocket* HandSocket = FPSArms->GetSocketByName(TempPickupWeapon->SocketName);
				HandSocket->AttachActor(TempPickupWeapon, FPSArms);
				WeaponSlot_01=TempPickupWeapon;
				bSlot1Full=1;
				CurrentWeapon= WeaponSlot_01;
				ShowWeapon(CurrentWeapon);

				bHasWeapon=1;
				return true;

			}
			else if(!bSlot2Full){
				WeaponSlotEnum=E_WeaponSlot::EWS_SecondSlot;
				SpawnWeapon(Weapon);
				return 1;
			}
			else{
				return false;
			}
		break;

		case E_WeaponSlot::EWS_SecondSlot:
			if(!bSlot2Full){
				AWeaponBase* TempPickupWeaponx1;
	
				TempPickupWeaponx1=GetWorld()->SpawnActor<AWeaponBase>(Weapon);
				
				const USkeletalMeshSocket* HandSocketx1 = FPSArms->GetSocketByName(TempPickupWeaponx1->SocketName);
				HandSocketx1->AttachActor(TempPickupWeaponx1, FPSArms);
				WeaponSlot_02=TempPickupWeaponx1;
				bSlot2Full=1;
				CurrentWeapon= WeaponSlot_02;
				ShowWeapon(CurrentWeapon);

				bHasWeapon=1;
				return 1;
			}
			else{
				return 0;
			}
		
		break;
		
		default:

		break;
	}
	
	



	return 0;


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
				UAnimInstance* AnimInstance = FPSArms->GetAnimInstance();
				CurrentWeapon->WeaponReload();
				
				if(AnimInstance&&ReloadMontage){
					AnimInstance->Montage_Play(ReloadMontage,1.f);
					AnimInstance->Montage_JumpToSection(TEXT("Default"));

				}
				
			}
		}
	}
	



}


void AFPSCharacter::StopFire(){
	
	bIsRecoil=0;

}

void AFPSCharacter::GrabClip(){
	
	
	int32 ClipBoneIndex{ CurrentWeapon->GetGunMesh()->GetBoneIndex(TEXT("Clip_Bone")) };
	
	ClipTransform = CurrentWeapon->GetGunMesh()->GetBoneTransform(ClipBoneIndex);
	//int32 LHandBoneIndex{ FPSArms->GetBoneIndex(TEXT("b_LeftHand")) };
	//LHandTransform=FPSArms->GetBoneTransform(LHandBoneIndex);
	
	
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, true);
	HandSceneComponent->AttachToComponent(FPSArms, AttachmentRules, FName(TEXT("LeftHandSocket")));
	HandSceneComponent->SetWorldTransform(ClipTransform);
	


	CurrentWeapon->SetMovingClip(1);



}
void AFPSCharacter::ReleaseClip(){
	
	CurrentWeapon->SetMovingClip(0);

}
void AFPSCharacter::ReloadEnd(){
	bIsReloading=0;
	bCanFire=1;


}



void AFPSCharacter::InteractKeyPressed(){
	
	OnInteract.Broadcast(1);


}

void AFPSCharacter::OutOfSphere(){
	OnInteractEnd.Broadcast(1);
}











void AFPSCharacter::Key1Pressed(){
	
	if(bSlot1Full){
		EquipWeapon(WeaponSlot_01);
		WeaponSlotEnum=E_WeaponSlot::EWS_FirstSlot;

	}

}
void AFPSCharacter::Key2Pressed(){
	
	if(bSlot2Full){
		EquipWeapon(WeaponSlot_02);
		WeaponSlotEnum=E_WeaponSlot::EWS_SecondSlot;
		
	}

}









//AFPSCharacter
