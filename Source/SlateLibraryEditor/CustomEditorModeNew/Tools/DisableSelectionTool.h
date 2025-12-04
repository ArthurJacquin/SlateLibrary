#pragma once

#include "CoreMinimal.h"
#include "InteractiveTool.h"

#include "DisableSelectionTool.generated.h"

/**
 * Tool to allow selection in the level
 */
UCLASS()
class SLATELIBRARYEDITOR_API UDisableSelectionTool : public UInteractiveTool
{
	GENERATED_BODY()

public:
	UDisableSelectionTool()
	{}
};

/**
 * Builder for UDisableSelectionTool
 */
UCLASS()
class SLATELIBRARYEDITOR_API UDisableSelectionToolBuilder : public UInteractiveToolBuilder
{
	GENERATED_BODY()

public:

	/** Conditions to Disable the tool, here no condition */
	virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override
	{
		return true;
	}

	/** Create the tool */
	virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const
	{
		UDisableSelectionTool* NewTool = NewObject<UDisableSelectionTool>();

		// Here we can setup the tool, like set variables, etc... 

		return NewTool;
	}
};
