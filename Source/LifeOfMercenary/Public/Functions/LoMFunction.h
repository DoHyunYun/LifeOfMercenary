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
	//Enum이름을 얻어와 일치하는 값를 반환해준다.
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

	//문자열에 해당하는 데이터테이블을 불러와준다.
	static UDataTable* GetDataTableFromString(const FString& _dataTablePath);
	
};
