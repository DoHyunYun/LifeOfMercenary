// Fill out your copyright notice in the Description page of Project Settings.

#include "UIInventory.h"
#include "Blueprint/WidgetLayoutLibrary.h"

UUIInventory::UUIInventory(const FObjectInitializer& _objectInitializer) : Super(_objectInitializer), choiceSlot(nullptr),
beforeSlot(nullptr), inventoryWidthSize(4), inventoryComponent(nullptr)
{

}

void UUIInventory::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UUIInventory::AddEmptyInventorySlot(UUniformGridPanel* _panel, int32 _index/* = 1*/)
{
	//����ũ�Ⱑ ������ ���� �ʴٸ� ����.
	if (inventoryWidthSize == 0) {
		UE_LOG(LogClass, Warning, TEXT("UUMGInventory::AddEmptyInventorySlot - None 'InventoryWidthSize'"));
		return false;
	}

	for (int i = 0; i < _index; ++i) {
		//������ ����(Sizebox) ���� �� �߰�.
		USizeBox* pTempSizeBox = NewObject<USizeBox>(USizeBox::StaticClass());
		_panel->AddChild(pTempSizeBox);

		//�߰��� ������ ������ ��ġ ���ϱ�.
		int32 row = (_panel->GetChildrenCount() - 1) / inventoryWidthSize;
		int32 column = (_panel->GetChildrenCount() - 1) % inventoryWidthSize;

		//������ ������ ��ġ ����.
		UUniformGridSlot* pSizeboxGridSlot = UWidgetLayoutLibrary::SlotAsUniformGridSlot(pTempSizeBox);
		pSizeboxGridSlot->SetRow(row);
		pSizeboxGridSlot->SetColumn(column);
	}

	return true;
}