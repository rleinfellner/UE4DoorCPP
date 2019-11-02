// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "UE4DoorGameMode.h"
#include "UE4DoorCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE4DoorGameMode::AUE4DoorGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
