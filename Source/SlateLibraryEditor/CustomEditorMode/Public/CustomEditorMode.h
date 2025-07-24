#pragma once

#include "CoreMinimal.h"
#include "Tools/UEdMode.h"

#include "CustomEditorMode.generated.h"

/**
 * A custom editor mode
 */
 UCLASS()
class SLATELIBRARYEDITOR_API UCustomEditorMode : public UEdMode
{
	GENERATED_BODY()

public:
	UCustomEditorMode();
	virtual ~UCustomEditorMode() override;

	// UEdMode interface
	virtual void Enter() override;
	virtual void CreateToolkit() override;
	virtual TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> GetModeCommands() const override;

	// Define ids for the mode and tools
	const static FEditorModeID ModeId;
	const static FString CustomWidgetToolId;
	const static FString AnotherToolId;

private:
	/** Register the tools part of this mode, this binds the commands to the tool events (OnStart, OnEnd...) **/
	void RegisterTools();
};
