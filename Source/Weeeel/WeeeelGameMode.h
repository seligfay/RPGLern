// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WeeeelGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPLayerDiedSIgnature, ACharacter*, Character);



UCLASS(minimalapi)
class AWeeeelGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AWeeeelGameMode();

};



