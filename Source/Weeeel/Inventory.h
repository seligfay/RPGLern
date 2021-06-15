// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs.h"


#include "Inventory.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WEEEEL_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	bool fullInit;
	UInventory();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UDataTable* ItemsInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FItemSlot> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int GenerateCellOnStart;


	/* simple add in massive if slot is free, return false if slot is not free*/
	UFUNCTION(BlueprintCallable, Category = "inventory")
		bool addItemInSlot(FItemSlot Item,  int slotIndex, FItemSlot& notFitItem);
	/* if slot have stack of same item, just add count of items and return new stack items that 
		didn't fit in the stack (count 0 if all items fit). 
		return false if item in slot dont have same item or free or item cant be stacked*/
	UFUNCTION(BlueprintCallable, Category = "inventory")
		bool addToStack(FItemSlot Item, int slotIndex, FItemSlot& notFitItem);
	/* just remove item make slot free,
		return false if slot already free
		return deleted item or free slot*/
	UFUNCTION(BlueprintCallable, Category = "inventory")
		bool removeItemFromSlotAndReturnItem(int slotIndex, FItemSlot& item);
	UFUNCTION(BlueprintCallable, Category = "inventory")
		bool removeItemFromSlot(int slotIndex);
	/* just remove number of item in stack
		return number of items who not be removed in stack (just items cant be stacked or removed number > than stack)
		if this action make stack count 0, slot be free!!!*/
	UFUNCTION(BlueprintCallable, Category = "inventory")
		int removeFromStack(int removedItems, int slotIndex);
	/* try item or item stack change slot
		if slot is not emprty, try add item to stack,
		if cant stack, swap items between slots
		return false if somting wrong ;)*/
	UFUNCTION(BlueprintCallable, Category = "inventory")
		bool changeItemSlot(int newSlotIndex, int oldSlotIndex);
	/* search stack of item in inventory
	 return false and -1 index if stack not finded,
	 return sum of free slots in stacks*/
	UFUNCTION(BlueprintCallable, Category = "inventory")
		bool findStack(FItemSlot Item, TArray<int> &index, int& stackSum);
	/* find free slots, same as findStack */
	UFUNCTION(BlueprintCallable, Category = "inventory")
		bool findFreeSlots(FItemData itemData, TArray<int>& index, int& freeSlotsCount);
	/* add items in inventory with dont care in position
		if item can be stack, add to other stacks
		return false if no item or stack added (for example, if inventory full)
		return item, who not fit in inventory*/
	UFUNCTION(BlueprintCallable, Category = "inventory")
		bool addItem(FItemSlot Item, FItemSlot& notFitItem);
	/*add Inventory slots to InventoryArray
		use for simple creation
	*/
	UFUNCTION(BlueprintCallable, Category = "inventory")
		void CreateInventorySlots(int cellCount);
	/*
		Try drag some item in stack in new slot.
		if cant, dont change inventory and return false
	*/
	UFUNCTION(BlueprintCallable, Category = "inventory")
		bool dragSomeStackItemInNewSlot(int oldSlotIndex, int newSlotIndex, int draggedItem);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};


