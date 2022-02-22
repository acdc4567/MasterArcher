// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayerController.h"
#include "FPSCharacter.h"


AFPSPlayerController::AFPSPlayerController(){

}

void AFPSPlayerController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);


}






void AFPSPlayerController::SetupInputComponent(){
Super::SetupInputComponent();
	check(InputComponent);

	InputComponent->BindAxis("Turn", this, &AFPSPlayerController::MouseTurnx);
	InputComponent->BindAxis("LookUp", this, &AFPSPlayerController::MouseLookUpX);

    //InputComponent->BindAxis("MoveForward", this, &AFPSPlayerController::MoveForwardKeyPressed);
	//InputComponent->BindAxis("MoveRight", this, &AFPSPlayerController::MoveRightKeyPressed);
}




void AFPSPlayerController::OnPossessx(AFPSCharacter* inCharacter){
    MyCharacterRef=inCharacter;
}

void AFPSPlayerController::MouseTurnx(float AxisValue){
    AddYawInput(AxisValue);

}

void AFPSPlayerController::MouseLookUpX(float AxisValue){
    AddPitchInput(AxisValue);

}

void AFPSPlayerController::MoveForwardKeyPressed(float AxisValue){

}



void AFPSPlayerController::MoveRightKeyPressed(float AxisValue){

}



//AFPSPlayerController
