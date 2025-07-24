#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

/**
 * Commands for a custom editor mode
 */
class FCustomEditorModeCommands : public TCommands<FCustomEditorModeCommands>
{
public:
	FCustomEditorModeCommands();

	virtual void RegisterCommands() override;
	static TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> GetCommands();

	// Commands for actions
	TSharedPtr<FUICommandInfo> CustomWidget;
	TSharedPtr<FUICommandInfo> AnotherTool;

	/** List of all the commands */
	TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> Commands;
};
