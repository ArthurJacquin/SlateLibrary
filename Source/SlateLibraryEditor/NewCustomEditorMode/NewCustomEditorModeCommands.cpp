#include "NewCustomEditorModeCommands.h"
#include "NewCustomEditorModeStyle.h"

#define LOCTEXT_NAMESPACE "NewCustomEditorMode"

FNewCustomEditorModeCommands::FNewCustomEditorModeCommands()
	: TCommands("NewCustomEditorModeCommands",
		NSLOCTEXT("NewCustomEditorMode", "NewCustomEditorModeCommands", "New Custom Editor Mode"),
		NAME_None,
		FNewCustomEditorModeStyle::Get()->GetStyleSetName())
{
}

void FNewCustomEditorModeCommands::RegisterCommands()
{
	// Macro to register palettes and store them
#define REGISTER_PALETTE_COMMAND(ToolCommandInfo, PaletteName, ToolTip) \
		UI_COMMAND(ToolCommandInfo, PaletteName, ToolTip, EUserInterfaceActionType::RadioButton, FInputChord()); \
		RegisteredPalettes.Add(FPaletteCommand{ PaletteName, ToolCommandInfo });

	// Macro to register tool commands and add store them
#define REGISTER_TOOL_COMMAND(PaletteName, ToolCommandInfo, ToolName, ToolTip) \
		UI_COMMAND(ToolCommandInfo, ToolName, ToolTip, EUserInterfaceActionType::RadioButton, FInputChord()); \
		RegisteredTools.Add(FStartToolCommand{ ToolName, ToolCommandInfo, PaletteName });

	// Register Tabs commands (Left bar), 
	REGISTER_PALETTE_COMMAND(LoadSelectionTab, "Select", "Select Actors Tooltip");
	REGISTER_PALETTE_COMMAND(LoadPlaceTab, "Place", "Place Actors Tooltip");

	// Register selection commands, palette name as to be hard coded as macro doesn't take parameters
	// Selection tab tools
	REGISTER_TOOL_COMMAND("Select", Selection_EnableSelection, "Enable", "Enable Selection Tooltip");
	REGISTER_TOOL_COMMAND("Select", Selection_DisableSelection, "Disable", "Disable selection Tooltip");

	// Place tab tools
	REGISTER_TOOL_COMMAND("Place", Place_Cube, "Cube", "Enable Dressing Selection");
	REGISTER_TOOL_COMMAND("Place", Place_Sphere, "Sphere", "Enable Terrain Selection");

#undef REGISTER_PALETTE_COMMAND
#undef REGISTER_TOOL_COMMAND
}

TSharedPtr<FUICommandInfo> FNewCustomEditorModeCommands::FindToolByName(const FString& Name, bool& bFound) const
{
	bFound = false;
	for (const FStartToolCommand& Command : RegisteredTools)
	{
		if (Command.ToolUIName.Equals(Name, ESearchCase::IgnoreCase)
			|| (Command.ToolCommand.IsValid() && Command.ToolCommand->GetLabel().ToString().Equals(Name, ESearchCase::IgnoreCase)))
		{
			bFound = true;
			return Command.ToolCommand;
		}
	}
	return TSharedPtr<FUICommandInfo>();
}

TSharedPtr<FUICommandInfo> FNewCustomEditorModeCommands::FindPaletteByName(const FString& Name, bool& bFound) const
{
	bFound = false;
	for (const FPaletteCommand& Command : RegisteredPalettes)
	{
		if (Command.Name.Equals(Name, ESearchCase::IgnoreCase))
		{
			bFound = true;
			return Command.Command;
		}
	}
	return TSharedPtr<FUICommandInfo>();
}

#undef LOCTEXT_NAMESPACE

