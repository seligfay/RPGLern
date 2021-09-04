// Fill out your copyright notice in the Description page of Project Settings.


#include "WeeelAttributeSet.h"
#include "Net/UnrealNetwork.h"

UWeeelAttributeSet::UWeeelAttributeSet() {

}

void UWeeelAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeeelAttributeSet, Health, COND_None, REPNOTIFY_Always);//always onRep
	DOREPLIFETIME_CONDITION_NOTIFY(UWeeelAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeeelAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeeelAttributeSet, Power, COND_None, REPNOTIFY_Always);
}


void UWeeelAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeeelAttributeSet, Health, OldHealth)
}

void UWeeelAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeeelAttributeSet, Stamina, OldStamina)
}

void UWeeelAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeeelAttributeSet, Mana, OldMana)
}

void UWeeelAttributeSet::OnRep_Power(const FGameplayAttributeData& OldPower) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeeelAttributeSet, Power, OldPower)
}