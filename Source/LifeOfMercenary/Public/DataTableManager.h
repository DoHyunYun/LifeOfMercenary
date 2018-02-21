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
	UDataTable* GetQuestDataTable() { return m_questDataTable; }
	UDataTable* GetMonsterDataTable() { return m_monsterDataTable; }

private:
	UDataTable* m_armorDataTable;
	UDataTable* m_weaponDataTable;
	UDataTable* m_questDataTable;
	UDataTable* m_monsterDataTable;
};
