// Fill out your copyright notice in the Description page of Project Settings.

#include "EquipmentComponent.h"
//#include "Functions/LoMFunctions.h"

UEquipmentComponent::UEquipmentComponent() : m_totalAttackPower(0.f), m_totalDefensivePower(0.f)
{
	for (int32 i = 0; i < (int32)EEquipmentPartsType::MAX_PARTS; i++) {
		m_parts[i] = nullptr;
	}
}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UEquipmentComponent::UpdateEquipmentDefensivePower()
{
	m_totalDefensivePower = 0;
	for (int32 i = 0; i < (int32)EEquipmentPartsType::MAX_PARTS; i++) {
		m_totalDefensivePower += Cast<UArmor>(m_parts[i])->GetDefensivePower();
	}
}

void UEquipmentComponent::SetEquipItem(UItem* _item, EEquipmentPartsType _partsType)
{
	//전 아이템 정보 계산
	switch (_item->GetItemType()) {
	case EItemType::ARMOR:
		if (m_parts[(int32)_partsType] != nullptr)
			m_totalDefensivePower -= Cast<UArmor>(m_parts[(int32)_partsType])->GetDefensivePower();
		break;
	case EItemType::WEAPON:
		break;
	}

	m_parts[(int32)_partsType] = _item;

	//현 아이템 정보 계산
	switch (_item->GetItemType()) {
	case EItemType::ARMOR:
		m_totalDefensivePower += Cast<UArmor>(m_parts[(int32)_partsType])->GetDefensivePower();
		break;
	case EItemType::WEAPON:
		m_totalAttackPower = Cast<UWeapon>(m_parts[(int32)_partsType])->GetAttackPower();
		break;
	}

	OnEquipItem.Broadcast(_partsType);
}

void UEquipmentComponent::Disarm(EEquipmentPartsType _partsType)
{
	if (m_parts[(int32)_partsType] != nullptr) {
		switch (m_parts[(int32)_partsType]->GetItemType()) {
		case EItemType::ARMOR:
			m_totalDefensivePower -= Cast<UArmor>(m_parts[(int32)_partsType])->GetDefensivePower();
			break;
		case EItemType::WEAPON:
			m_totalAttackPower = 0;
			break;
		}
	}

	m_parts[(int32)_partsType] = nullptr;

	OnDisarmItem.Broadcast(_partsType);
}