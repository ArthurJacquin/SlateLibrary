#pragma once

#include "CoreMinimal.h"

#include "EditableTableData.generated.h"

/**
 * Data to be displayed in the table
 */
UCLASS()
class SLATELIBRARYEDITOR_API UEditableTableData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FText Animal;

	UPROPERTY()
	FText Color;

	UPROPERTY()
	FText Age;
};
