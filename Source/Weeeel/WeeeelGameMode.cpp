// Copyright Epic Games, Inc. All Rights Reserved.

#include "WeeeelGameMode.h"
#include "WeeeelCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWeeeelGameMode::AWeeeelGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Character/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}










