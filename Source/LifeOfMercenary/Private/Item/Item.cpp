// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "Item/Armor.h"
#include "Item/Weapon.h"
#include "Item/Equipment.h"
#include "Engine/Texture2D.h"
#include "UObject/ConstructorHelpers.h"

UItem::UItem() : m_name("NONE"), m_imageCode("NONE"), m_weight(0.f), m_meshCode("NONE")
{

}

UTexture2D* UItem::GetItemTexture2D()
{
	if (m_imageCode == "NONE")
		return nullptr;

	FString FileName = "/Game/Resource/Textures/";
	FString FullName = FileName + m_imageCode + "." + m_imageCode;

	return LoadObject<UTexture2D>(nullptr, *FullName);
}

UArmor* UItem::ToArmor()
{
	return Cast<UArmor>(this);
}

UWeapon* UItem::ToWeapon()
{
	return Cast<UWeapon>(this);
}

UEquipment* UItem::ToEquipment()
{
	return Cast<UEquipment>(this);
}