// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "WeeelAttributeSet.generated.h"



//macro from attributeSet
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)\
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName)\
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName)\
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName)\
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)




/**
 * 
 */
UCLASS()
class WEEEEL_API UWeeelAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UWeeelAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	//health
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Health)
		FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UWeeelAttributeSet, Health);//visible access

	UFUNCTION()
		virtual void OnRep_Health(const FGameplayAttributeData& OldHealth); 

	//Stamina
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Stamina)
		FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UWeeelAttributeSet, Stamina);//visible access

	UFUNCTION()
		virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina); //set replication func

	//Mana
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Mana)
		FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UWeeelAttributeSet, Mana);//visible access

	UFUNCTION()
		virtual void OnRep_Mana(const FGameplayAttributeData& OldMana); //set replication func


	//MaxHealth
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxHealth)
		FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UWeeelAttributeSet, MaxHealth);//visible access


	UFUNCTION()
		virtual void OnRep_MAxHealth(const FGameplayAttributeData& OldMaxHealth); //set replication func

	//MaxStamina
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxStamina)
		FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UWeeelAttributeSet, MaxStamina);//visible access

	UFUNCTION()
		virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldSMaxStamina); //set replication func

	//MaxMana
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxMana)
		FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UWeeelAttributeSet, MaxMana);//visible access

	UFUNCTION()
		virtual void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana); //set replication func

	//Power
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Power)
		FGameplayAttributeData Power;
	ATTRIBUTE_ACCESSORS(UWeeelAttributeSet, Power);//visible access

	UFUNCTION()
		virtual void OnRep_Power(const FGameplayAttributeData& OldPower); //set replication func

	//HealthRegen
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_HealthRegen)
		FGameplayAttributeData HealthRegen;
	ATTRIBUTE_ACCESSORS(UWeeelAttributeSet, HealthRegen);//visible access

	UFUNCTION()
		virtual void OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen); //set replication func

	//ManaRegen
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_ManaRegen)
		FGameplayAttributeData ManaRegen;
	ATTRIBUTE_ACCESSORS(UWeeelAttributeSet, ManaRegen);//visible access

	UFUNCTION()
		virtual void OnRep_ManaRegen(const FGameplayAttributeData& OldManaRegen); //set replication func

	//StaminaRegen
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_StaminaRegen)
		FGameplayAttributeData StaminaRegen;
	ATTRIBUTE_ACCESSORS(UWeeelAttributeSet, StaminaRegen);//visible access

	UFUNCTION()
		virtual void OnRep_StaminaRegen(const FGameplayAttributeData& OldStaminaRegen); //set replication func
	
};



