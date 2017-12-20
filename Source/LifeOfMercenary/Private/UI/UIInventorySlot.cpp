// Fill out your copyright notice in the Description page of Project Settings.

#include "UIInventorySlot.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

UUIInventorySlot::UUIInventorySlot(const FObjectInitializer& _objectInitializer)
	: Super(_objectInitializer), textureBackground(nullptr), textureItem(nullptr), bChoice(false), item(nullptr)
{

}

void UUIInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
	textureBackground = LoadObject<UTexture2D>
		(nullptr, TEXT("Texture2D'/Game/Resources/UI/Textures/T_NotSlotChoice.T_NotSlotChoice'"));

	SetItem(item);
}

FReply UUIInventorySlot::NativeOnMouseButtonUp(const FGeometry& _inGeometry, const FPointerEvent& _inMouseEvent)
{
	bChoice = true;

	textureBackground = LoadObject<UTexture2D>
		(nullptr, TEXT("Texture2D'/Game/Resources/UI/Textures/T_SlotChoice.T_SlotChoice'"));

	OnTouchSlot.Broadcast(this);
	return FReply::Handled();
}

void UUIInventorySlot::SetItem(UItem* _item)
{
	if (nullptr != _item) {
		item = _item;
		textureItem = item->GetItemTexture2D("/Game/Resources/Item/Textures/");
	}
	else {
		UE_LOG(LogClass, Warning, TEXT("UUIInventorySlot::SetItem - None Item!!"));
	}
}

void UUIInventorySlot::UnableSlot()
{
	bChoice = false;
	textureBackground = LoadObject<UTexture2D>
		(nullptr, TEXT("Texture2D'/Game/Resources/UI/Textures/T_NotSlotChoice.T_NotSlotChoice'"));
}