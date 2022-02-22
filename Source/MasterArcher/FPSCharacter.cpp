// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "FPSPlayerController.h"
#include "Camera/CameraComponent.h"
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

	GetMesh()->SetupAttachment(FollowCamera);


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
















//AFPSCharacter
