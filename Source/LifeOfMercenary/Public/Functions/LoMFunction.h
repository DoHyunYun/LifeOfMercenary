#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/DataTable.h"
#include "LoMFunction.generated.h"

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API ULoMFunction : public UObject
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
	static UDataTable* GetDataTableFromString(const FString& _dataTablePath);
	
};
