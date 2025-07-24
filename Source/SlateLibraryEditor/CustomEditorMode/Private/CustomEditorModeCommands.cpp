#include "../Public/CustomEditorModeCommands.h"

#define LOCTEXT_NAMESPACE "CustomEditorMode"

FCustomEditorModeCommands::FCustomEditorModeCommands()
	: TCommands("CustomEditorMode",
		NSLOCTEXT("CustomEditorMode", "CustomEditorModeCommands", "Custom Editor Mode"),
		NAME_None,
		FAppStyle::GetAppStyleSetName())
{
}

void FCustomEditorModeCommands::RegisterCommands()
{
	TArray <TSharedPtr<FUICommandInfo>>& ToolCommands = Commands.FindOrAdd(NAME_Default);

	//Commands for actions
	UI_COMMAND(CustomWidget, "Custom Widget", "Custom Widget", EUserInterfaceActionType::RadioButton, FInputChord());
	ToolCommands.Add(CustomWidget);
	
	UI_COMMAND(AnotherTool, "Another Tool", "Another Tool", EUserInterfaceActionType::RadioButton, FInputChord());
	ToolCommands.Add(AnotherTool);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> FCustomEditorModeCommands::GetCommands()
{
	return Get().Commands;
}


#undef LOCTEXT_NAMESPACE

