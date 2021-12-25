// Fill out your copyright notice in the Description page of Project Settings.


#include "WeeelAttributeSet.h"
#include "Net/UnrealNetwork.h"

UWeeelAttributeSet::UWeeelAttributeSet() {

}

void UWeeelAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeeelAttributeSet, Health, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeeelAttributeSet, Stamina, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeeelAttributeSet, Mana, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeeelAttributeSet, MaxHealth, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeeelAttributeSet, MaxStamina, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeeelAttributeSet, MaxMana, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeeelAttributeSet, Power, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeeelAttributeSet, HealthRegen, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeeelAttributeSet, ManaRegen, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UWeeelAttributeSet, StaminaRegen, COND_None, REPNOTIFY_OnChanged);
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



void UWeeelAttributeSet::OnRep_MAxHealth(const FGameplayAttributeData& OldMaxHealth) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeeelAttributeSet, MaxHealth, OldMaxHealth)
}

void UWeeelAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeeelAttributeSet, MaxStamina, OldMaxStamina)
}

void UWeeelAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeeelAttributeSet, MaxMana, OldMaxMana)
}

void UWeeelAttributeSet::OnRep_Power(const FGameplayAttributeData& OldPower) {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeeelAttributeSet, Power, OldPower)
}

void UWeeelAttributeSet::OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeeelAttributeSet, HealthRegen, OldHealthRegen)
}

void UWeeelAttributeSet::OnRep_ManaRegen(const FGameplayAttributeData& OldManaRegen)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeeelAttributeSet, ManaRegen, OldManaRegen)
}

void UWeeelAttributeSet::OnRep_StaminaRegen(const FGameplayAttributeData& OldStaminaRegen)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWeeelAttributeSet, StaminaRegen, OldStaminaRegen)
}
