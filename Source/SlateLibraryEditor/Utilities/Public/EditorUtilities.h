#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EditorUtilities.generated.h"

/**
 * Editor Utilities
 */
UCLASS()
class SLATELIBRARYEDITOR_API UEditorUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/** Refresh all the opened editor viewports */
	static void RefreshEditorViewports();
	
	
};
