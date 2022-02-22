// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSPlayerController.generated.h"

class AFPSCharacter;


/**
 * 
 */
UCLASS()
class MASTERARCHER_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()
  public:
    AFPSPlayerController();
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	void OnPossessx(AFPSCharacter* inCharacter);




protected:





private:
	void MouseTurnx(float AxisValue);
	void MouseLookUpX(float AxisValue);

	void MoveForwardKeyPressed(float AxisValue);
	void MoveRightKeyPressed(float AxisValue);

	AFPSCharacter* MyCharacterRef;


};
