// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/Equipment.h"
#include "Item/Armor.h"
#include "Item/Weapon.h"
#include "EquipmentComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipItem, EEquipmentPartsType, _type);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDisarmItem, EEquipmentPartsType, _type);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LIFEOFMERCENARY_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEquipmentComponent();

	void UpdateEquipmentDefensivePower();

	UItem** GetEquipmentArray() { return m_parts; }

	UFUNCTION(BlueprintCallable, Category = EquipmentComponent)
		void SetEquipItem(UItem* _item, EEquipmentPartsType _partsType);

	UFUNCTION(BlueprintCallable, Category = EquipmentComponent)
		void Disarm(EEquipmentPartsType _partsType);

	UFUNCTION(BlueprintCallable, Category = EquipmentComponent)
		float GetTotalDefensivePower() { return m_totalDefensivePower; }

	UFUNCTION(BlueprintCallable, Category = EquipmentComponent)
		float GetTotalWeaponPower() { return m_totalAttackPower; }

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable, Category = EquipmentComponent)
		FOnEquipItem OnEquipItem;

	UPROPERTY(BlueprintAssignable, Category = EquipmentComponent)
		FOnDisarmItem OnDisarmItem;

private:
	UItem* m_parts[(int32)EEquipmentPartsType::MAX_PARTS];
	float m_totalDefensivePower;
	float m_totalAttackPower;
};
