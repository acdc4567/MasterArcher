// Copyright Epic Games, Inc. All Rights Reserved.

#include "MasterArcherGameMode.h"
#include "MasterArcherCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMasterArcherGameMode::AMasterArcherGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
