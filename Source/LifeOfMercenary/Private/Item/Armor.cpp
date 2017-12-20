// Fill out your copyright notice in the Description page of Project Settings.

#include "Armor.h"
#include "Functions/LoMFunctions.h"

UArmor::UArmor() : m_defensivePower(0.f)
{

}

void UArmor::SetArmorData(const FArmorEquipmentData& _amorData)
{
	m_name = _amorData.Name;
	m_defensivePower = _amorData.DefensivePower;
	m_solidity = _amorData.Solidity;
	m_durabilty = _amorData.Durability;
	m_weight = _amorData.Weight;
	m_partsType = ULoMFunctions::GetEnumValueFromString<EEquipmentPartsType>("EEquipmentPartsType", _amorData.PartsType);
	m_imageCode = _amorData.ImageCode;
	m_price = _amorData.Price;
	m_meshCode = _amorData.MeshCode;
	m_itemType = EItemType::ARMOR;
}
