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
		virtual void OnRep_Health(const FGameplayAttributeData& OldHealth); //set replication func

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

	//Power
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_Power)
		FGameplayAttributeData Power;
	ATTRIBUTE_ACCESSORS(UWeeelAttributeSet, Power);//visible access

	UFUNCTION()
		virtual void OnRep_Power(const FGameplayAttributeData& OldPower); //set replication func
};



