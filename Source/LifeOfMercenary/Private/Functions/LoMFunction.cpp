#include "LoMFunction.h"

UDataTable* ULoMFunction::GetDataTableFromString(const FString& _dataTablePath)
{
	ConstructorHelpers::FObjectFinder<UDataTable> ExcelTable_BP(*_dataTablePath);
	return ExcelTable_BP.Object;
}