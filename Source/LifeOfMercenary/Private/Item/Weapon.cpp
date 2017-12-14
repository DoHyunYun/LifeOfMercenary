// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "Functions/LoMFunction.h"

UWeapon::UWeapon() :m_attackPower(0.f)
{

}

void UWeapon::SetWeaponData(const FWeaponEquipmentData& _weaponData)
{
	m_name = _weaponData.Name;
	m_attackPower = _weaponData.AttackPower;
	m_solidity = _weaponData.Solidity;
	m_durabilty = _weaponData.Durability;
	m_weight = _weaponData.Weight;
	m_partsType = ULoMFunction::GetEnumValueFromString<EEquipmentPartsType>("EEquipmentPartsType", _weaponData.PartsType);
	m_imageCode = _weaponData.ImageCode;
	m_price = _weaponData.Price;
	m_meshCode = _weaponData.MeshCode;
	m_weaponType = ULoMFunction::GetEnumValueFromString<EWeaponType>("EWeaponType", _weaponData.WeaponType);
	m_itemType = EItemType::WEAPON;
}