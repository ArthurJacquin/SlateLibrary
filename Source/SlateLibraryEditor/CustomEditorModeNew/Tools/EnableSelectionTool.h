#pragma once

#include "CoreMinimal.h"
#include "InteractiveTool.h"
#include "EngineUtils.h"

#include "EnableSelectionTool.generated.h"

/**
 * Tool to allow selection in the level
 */
UCLASS()
class SLATELIBRARYEDITOR_API UEnableSelectionTool : public UInteractiveTool
{
	GENERATED_BODY()

public:
	UEnableSelectionTool()
	{}
};

/**
 * Builder for UEnableSelectionTool
 * Enabled only if there's actors in the level
 */
UCLASS()
class SLATELIBRARYEDITOR_API UEnableSelectionToolBuilder : public UInteractiveToolBuilder
{
	GENERATED_BODY()

public:

	/** Conditions to enable the tool, here we want at least 1 actor in the level */
	virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override
	{
		UWorld* EditorWorld = GEditor->GetEditorWorldContext().World();
		if (EditorWorld)
		{
			for (const AActor* Actor : TActorRange<AActor>(EditorWorld))
			{
				// Here we can check more things related to actors, like if they have a specific tag for example
				// In this case we just return because we have an actor in the level
				return true;
			}
		}

		return false;
	}

	/** Create the tool */
	virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const
	{
		UEnableSelectionTool* NewTool = NewObject<UEnableSelectionTool>();

		// Here we can setup the tool, like set variables, etc... 

		return NewTool;
	}
};
