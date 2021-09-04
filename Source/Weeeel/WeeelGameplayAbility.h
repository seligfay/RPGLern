// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Weeeel.h"
#include "WeeelGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class WEEEEL_API UWeeelGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UWeeelGameplayAbility();

	//AutoActivate if input pressed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
		EWeeeelAbilityInputID AbilityInputId = EWeeeelAbilityInputID::None;
	
};
