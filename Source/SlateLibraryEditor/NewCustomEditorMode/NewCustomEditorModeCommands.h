#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

/**
 * Commands for a custom editor mode
 */
class FNewCustomEditorModeCommands : public TCommands<FNewCustomEditorModeCommands>
{
public:
	FNewCustomEditorModeCommands();

	virtual void RegisterCommands() override;

	TSharedPtr<FUICommandInfo> FindToolByName(const FString& Name, bool& bFound) const;
	TSharedPtr<FUICommandInfo> FindPaletteByName(const FString& Name, bool& bFound) const;

	/** Command info for palettes */
	struct FPaletteCommand
	{
		FString Name;
		TSharedPtr<FUICommandInfo> Command;
	};

	/** Command info for tools */
	struct FStartToolCommand
	{
		FString ToolUIName;
		TSharedPtr<FUICommandInfo> ToolCommand;
		FName PaletteName;
	};

	TArray<FStartToolCommand> GetTools() const { return RegisteredTools; }
	TArray<FPaletteCommand> GetPalettes() const { return RegisteredPalettes; }

	// Commands to open tabs
	TSharedPtr<FUICommandInfo> LoadSelectionTab;
	TSharedPtr<FUICommandInfo> LoadPlaceTab;

	// Selection Tab commands
	TSharedPtr<FUICommandInfo> Selection_EnableSelection;
	TSharedPtr<FUICommandInfo> Selection_DisableSelection;

	// Place Tab commands
	TSharedPtr<FUICommandInfo> Place_Cube;
	TSharedPtr<FUICommandInfo> Place_Sphere;

protected:
	/** The registered palettes */
	TArray<FPaletteCommand> RegisteredPalettes;
	
	/** The registered tools */
	TArray<FStartToolCommand> RegisteredTools;
};
