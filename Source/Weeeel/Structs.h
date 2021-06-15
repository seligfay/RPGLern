#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Engine/StaticMesh.h"
#include "Engine/Texture.h"

#include "Structs.generated.h"


/*Base structs for items in inventory */
USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()
		/*   Item Name   */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName; 
	/*  Item description  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Desc;     
	/*  Mesh for spawn actor in world  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* Mesh; 
	/*  Icon for display in inventory slots  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture* Icon;
	/*  Item can be stored in inventory slot  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool CanBeStored; 
	/*  Item can be stacked in inventory     */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool CanStack; 
	/*  Maximum namber of this item in 1 slot  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxStack; 
};

/*info for  */
USTRUCT(BlueprintType)
struct FItemSlot : public FTableRowBase
{
	GENERATED_BODY()
		/*   full static item info   */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDataTableRowHandle ItemInfo;
	/*  current count of items in stuck  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Count;
	
};

/**
 * 
 */
class WEEEEL_API Structs
{
public:
	Structs();
	~Structs();
};
