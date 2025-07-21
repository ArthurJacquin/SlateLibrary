#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "SlateTableEditorUtility.generated.h"

/**
 * 
 */
UCLASS()
class SLATELIBRARYEDITOR_API USlateTableEditorUtility : public UEditorUtilityWidget
{
	GENERATED_BODY()
	
protected:
	TSharedRef<SWidget> RebuildWidget() override;

};
