#include "DataTableManager.h"

UDataTableManager::UDataTableManager() : m_armorDataTable(nullptr), m_weaponDataTable(nullptr)
{
	m_armorDataTable = ULoMFunction::GetDataTableFromString(TEXT("DataTable'/Game/DataTables/DB_ArmorEquipment.DB_ArmorEquipment'"));
	m_weaponDataTable = ULoMFunction::GetDataTableFromString(TEXT("DataTable'/Game/DataTables/DB_WeaponEquipment.DB_WeaponEquipment'"));
}