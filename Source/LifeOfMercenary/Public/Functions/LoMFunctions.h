// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/DataTable.h"
#include "Camera/MainSceneCamera.h"
#include "MainScene/GameMode/HUDManager.h"
#include "LoMFunctions.generated.h"

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API ULoMFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//Enum�̸��� ���� ��ġ�ϴ� ���� ��ȯ���ش�.
	template <typename EnumType>
	static FORCEINLINE EnumType GetEnumValueFromString(const FString& _enumName, const FString& _string)
	{
		UEnum* Enum = FindObject<UEnum>(ANY_PACKAGE, *_enumName, true);
		if (!Enum)
		{
			return EnumType(-1);
		}
		return (EnumType)Enum->GetIndexByName(FName(*_string));
	}

	//���ڿ��� �ش��ϴ� ���������̺��� �ҷ����ش�.
	UFUNCTION(BlueprintCallable, Category = "LoMFunctions")
		static UDataTable* GetDataTableFromString(const FString& _dataTablePath);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "_world"), Category = "LoMFunctions")
		static AMainSceneCamera* GetMainSceneCamera(const UObject* _world);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "_world"), Category = "LoMFunctions")
		static AHUDManager* GetHUDManager(const UObject* _world);
};
