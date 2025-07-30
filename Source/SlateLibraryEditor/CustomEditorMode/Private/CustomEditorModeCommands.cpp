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
	
	// Another tool
	FUICommandInfo::MakeCommandInfo(
		AsShared(),
		AnotherTool,
		TEXT("Another Tool"),
		LOCTEXT("AnotherToolCommandName", "Another Tool"),
		LOCTEXT("AnotherToolToolTooltip", "This is the tooltip of Another Tool"),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "Level.VisibleIcon16x"),
		EUserInterfaceActionType::RadioButton,
		FInputChord()
	);
	ToolCommands.Add(AnotherTool);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> FCustomEditorModeCommands::GetCommands()
{
	return Get().Commands;
}


#undef LOCTEXT_NAMESPACE

