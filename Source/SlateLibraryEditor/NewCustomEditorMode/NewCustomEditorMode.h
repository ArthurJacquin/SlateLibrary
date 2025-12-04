#pragma once

#include "CoreMinimal.h"
#include "Tools/UEdMode.h"

#include "NewCustomEditorMode.generated.h"

class FNewCustomEditorModeToolkit;

/**
 * A custom editor mode
 */
 UCLASS()
class SLATELIBRARYEDITOR_API UNewCustomEditorMode : public UEdMode
{
	GENERATED_BODY()

public:
	UNewCustomEditorMode();
	virtual ~UNewCustomEditorMode() override;

	const static FEditorModeID ModeId;
	const static FString EnableSelectionToolId;
	const static FString DisableSelectionToolId;
	const static FString PlaceCubeToolId;
	const static FString PlaceSphereToolId;

	// UEdMode interface
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void CreateToolkit() override;

	virtual bool IsSelectionAllowed(AActor* InActor, bool bInSelection) const override;

	/** Checks if the tool of the from the given class is active */
	bool IsActiveToolFromClass(UClass* ToolClass) const;

private:
	/** Register the tools part of this mode, this binds the commands to the tool events (OnStart, OnEnd...) **/
	void RegisterTools();

	/** Returns the toolkit as a FCustomEditorModeToolkit_New */
	FNewCustomEditorModeToolkit* GetToolkit() const;

	/** Return the name of the active palette */
	FName GetActivePaletteName() const;
};
