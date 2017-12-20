#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	ARMOR		UMETA(DisplayName = "ARMOR"),
	WEAPON		UMETA(DisplayName = "WEAPON"),	
};

class UArmor;
class UWeapon;
class UEquipment;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class LIFEOFMERCENARY_API UItem : public UObject
{
	GENERATED_BODY()
public:
	UItem();

	UFUNCTION(BlueprintCallable, Category = "Item")
		UTexture2D* GetItemTexture2D(FString _path);
	UFUNCTION(BlueprintCallable, Category = "Item")
		FString GetName() { return m_name; }
	UFUNCTION(BlueprintCallable, Category = "Item")
		EItemType GetItemType() { return m_itemType; }
	UFUNCTION(BlueprintCallable, Category = "Item")
		FString GetMeshCode() { return m_meshCode; }
	UFUNCTION(BlueprintCallable, Category = "Item")
		float GetWeigth() { return m_weight; }
	UFUNCTION(BlueprintCallable, Category = "Item")
		int32 GetPrice() { return m_price; }
	UFUNCTION(BlueprintCallable, Category = "Item")
		UArmor* ToArmor();
	UFUNCTION(BlueprintCallable, Category = "Item")
		UWeapon* ToWeapon();
	UFUNCTION(BlueprintCallable, Category = "Item")
		UEquipment* ToEquipment();

protected:
	FString m_name; //������ �̸�
	EItemType m_itemType; //������ Ÿ��(��, ����, �Ҹ�ǰ ��...)
	FString m_imageCode; //������ �̹��� �����̸�
	FString m_meshCode; //������ �̹��� �����̸�
	float m_weight; //����
	int32 m_price;  //����
};
