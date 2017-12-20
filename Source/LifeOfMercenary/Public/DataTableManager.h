#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Functions/LoMFunctions.h"
#include "DataTableManager.generated.h"

/**
 * 
 */
UCLASS()
class LIFEOFMERCENARY_API UDataTableManager : public UObject
{
	GENERATED_BODY()
public:
	UDataTableManager();

	UDataTable* GetArmorDataTable() { return m_armorDataTable; }
	UDataTable* GetWeaponDataTable() { return m_weaponDataTable; }

private:
	UDataTable* m_armorDataTable;
	UDataTable* m_weaponDataTable;
};
