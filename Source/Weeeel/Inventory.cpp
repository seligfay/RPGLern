// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	this->fullInit = false;
	this->GenerateCellOnStart = 0;
	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	
	Super::BeginPlay();
	bool init = true;
	if (!ItemsInfo) {
		init = false;
		
	}
	else {
		CreateInventorySlots(GenerateCellOnStart);
	}
	fullInit = init;
	
	// ...
	
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventory::addItemInSlot(FItemSlot Item, int slotIndex, FItemSlot& notFitItem) {
	bool success = false;
	notFitItem = Item;
	if (!Item.ItemInfo.IsNull() && fullInit) {
		FItemData* ItemData = Item.ItemInfo.DataTable->FindRow<FItemData>(Item.ItemInfo.RowName, "");
		if (ItemData->CanBeStored) {
			success = addToStack(Item, slotIndex, notFitItem);
			if (!success && (Inventory[slotIndex].ItemInfo.RowName == (FName)"Empty" || Inventory[slotIndex].ItemInfo.RowName == (FName)"None")) {
				if (ItemData->CanStack && Item.Count > ItemData->MaxStack) {
					FItemSlot subitem = Item;
					subitem.Count = ItemData->MaxStack;
					Inventory[slotIndex] = subitem;
					notFitItem.Count = Item.Count - ItemData->MaxStack;
					success = true;
				}
				else {
					Inventory[slotIndex] = Item;
					success = true;
					notFitItem.Count = 0;
				}
				
			}
		}
		
	}

	return success;
}

bool UInventory::addToStack(FItemSlot Item, int slotIndex, FItemSlot &notFitItem) {
	bool success = false;
	notFitItem = Item;
	if (!Item.ItemInfo.IsNull() && fullInit) {
		if (Item.ItemInfo.RowName == Inventory[slotIndex].ItemInfo.RowName) {
			FItemData* ItemData = Item.ItemInfo.DataTable->FindRow<FItemData>(Item.ItemInfo.RowName, "");
			if (ItemData->CanStack) {
				int fit = 0;
				
				fit = Inventory[slotIndex].Count;
				fit += Item.Count;
				if (fit <= ItemData->MaxStack) {
					Inventory[slotIndex].Count = fit;
					notFitItem = Item;
					notFitItem.Count = 0;
				} else {
					int notFit = fit - ItemData->MaxStack;
					Inventory[slotIndex].Count = ItemData->MaxStack;
					notFitItem = Item;
					notFitItem.Count = notFit;
					
				}
				success = true;
				
			} 
			
		}
	}

	return success;
}



bool UInventory::removeItemFromSlotAndReturnItem(int slotIndex, FItemSlot& item) {
	bool success = false;
	
	if (fullInit) {
		item = Inventory[slotIndex];
		if (Inventory[slotIndex].ItemInfo.RowName != (FName)"Empty" || Inventory[slotIndex].ItemInfo.RowName != (FName)"None") {

			FItemSlot EmptySlot;
			EmptySlot.Count = 0;
			EmptySlot.ItemInfo.DataTable = Inventory[slotIndex].ItemInfo.DataTable;
			EmptySlot.ItemInfo.RowName = (FName)"Empty";
			Inventory[slotIndex] = EmptySlot;
			success = true;
		}
	}
	return success;
}

bool UInventory::removeItemFromSlot(int slotIndex) {
	bool success = false;

	if (fullInit) {
		if (Inventory[slotIndex].ItemInfo.RowName != (FName)"Empty" || Inventory[slotIndex].ItemInfo.RowName != (FName)"None") {
			FItemSlot EmptySlot;
			EmptySlot.Count = 0;
			EmptySlot.ItemInfo.DataTable = Inventory[slotIndex].ItemInfo.DataTable;
			EmptySlot.ItemInfo.RowName = (FName)"Empty";
			Inventory[slotIndex] = EmptySlot;
			success = true;
		}
	}
	return success;
}

int UInventory::removeFromStack(int removedItems, int slotIndex) {
	int result = removedItems;
	if (fullInit) {
		if (removedItems >= Inventory[slotIndex].Count) {
			result = result - Inventory[slotIndex].Count;
			removeItemFromSlot(slotIndex);
		}
		else {
			result = 0;
			Inventory[slotIndex].Count -= removedItems;
		}
	}
	return result;
}

bool UInventory::changeItemSlot(int newSlotIndex, int oldSlotIndex) {
	bool result = false;
	if (fullInit && newSlotIndex!= oldSlotIndex) {
		FItemSlot copiedItem = Inventory[oldSlotIndex];
		result = addItemInSlot(copiedItem, newSlotIndex, copiedItem);
		if (result) {
			removeFromStack(Inventory[oldSlotIndex].Count - copiedItem.Count, oldSlotIndex);
		}
		else {
			Inventory[oldSlotIndex] = Inventory[newSlotIndex];
			Inventory[newSlotIndex] = copiedItem;
		}

	}

	return result;
}

bool UInventory::findStack(FItemSlot Item, TArray<int>& index, int &stackSum) {
	bool result = false;
	if (fullInit ) {
		stackSum = 0;
		FItemData* ItemData = Item.ItemInfo.DataTable->FindRow<FItemData>(Item.ItemInfo.RowName, "");
		if (ItemData->CanStack) {
			for (size_t i = 0; i < Inventory.Num(); i++) {
				if (Inventory[i].ItemInfo.RowName == Item.ItemInfo.RowName) {
					stackSum += (ItemData->MaxStack - Inventory[i].Count);
						index.Add(i);
					result = true;
				}

			}
		}
	}
	return result;
}

bool UInventory::findFreeSlots(FItemData itemData,TArray<int>& index, int &freeSlotsCount) {
	bool result = false;
	freeSlotsCount = 0;
	if (fullInit) {
		for (size_t i = 0; i < Inventory.Num(); i++) {
			if (Inventory[i].ItemInfo.RowName == (FName)"Empty" || Inventory[i].ItemInfo.RowName == (FName)"None") {
				if (itemData.CanStack) {
					freeSlotsCount += itemData.MaxStack;
				}
				else {
					freeSlotsCount++;
				}
				index.Add(i);
				result = true;
			}
		}
	}
	return result;
}

bool UInventory::addItem(FItemSlot Item, FItemSlot& notFitItem) {
	bool result = false;
	notFitItem = Item;
	FItemData* ItemData = Item.ItemInfo.DataTable->FindRow<FItemData>(Item.ItemInfo.RowName, "");
	if (fullInit && ItemData->CanBeStored) {
		for (int i = 0; i < Inventory.Num() && notFitItem.Count>0; i++) {
			result = addItemInSlot(notFitItem, i, notFitItem);
		}
		
	}
	return result;
}

void UInventory::CreateInventorySlots(int cellCount) {
		for (int i = 0; i < cellCount; i++) {
			FItemSlot EmptySlot;
			EmptySlot.Count = 0;
			EmptySlot.ItemInfo.DataTable = ItemsInfo;
			EmptySlot.ItemInfo.RowName = (FName)"Empty";
			Inventory.Add(EmptySlot);
		}
		
}

bool UInventory::dragSomeStackItemInNewSlot(int oldSlotIndex, int newSlotIndex, int draggedItem) {
	bool result = false;
	if (fullInit) {
		FItemData* ItemData = Inventory[oldSlotIndex].ItemInfo.DataTable->FindRow<FItemData>(Inventory[oldSlotIndex].ItemInfo.RowName, "");
		if (ItemData->CanStack) {
			if (Inventory[newSlotIndex].ItemInfo.RowName == (FName)"Empty" || Inventory[newSlotIndex].ItemInfo.RowName == (FName)"None") {
				FItemSlot subItem = Inventory[oldSlotIndex];
				
				int NoItemInStack = removeFromStack(draggedItem, oldSlotIndex);
				subItem.Count = draggedItem - NoItemInStack;
				result = addItemInSlot(subItem, newSlotIndex, subItem);
		
			}
			else {
				if (Inventory[oldSlotIndex].ItemInfo == Inventory[newSlotIndex].ItemInfo) {
				
				
					int ItemInStack = draggedItem;
					if (ItemInStack > ItemData->MaxStack - Inventory[newSlotIndex].Count) {
						ItemInStack = ItemData->MaxStack - Inventory[newSlotIndex].Count;
					}
					int NoItemInStack = removeFromStack(ItemInStack, oldSlotIndex);
					ItemInStack -= NoItemInStack;
					FItemSlot subItem = Inventory[oldSlotIndex];
					subItem.Count = ItemInStack;
					result = addToStack(subItem, newSlotIndex, subItem);
				}


			}
		}
	}

	return result;
}
	
