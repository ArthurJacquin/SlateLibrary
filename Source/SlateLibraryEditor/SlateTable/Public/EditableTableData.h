#pragma once

#include "CoreMinimal.h"

#include "EditableTableData.generated.h"

/**
 * 
 */
UCLASS()
class SLATELIBRARYEDITOR_API UEditableTableData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString Animal;

	UPROPERTY()
	FString Color;

	UPROPERTY()
	FString Age;
};
