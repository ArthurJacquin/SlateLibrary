#include "CustomEditorMode/Public/CustomEditorMode.h"
#include "CustomEditorMode/Public/CustomEditorModeToolkit.h"
#include "CustomEditorMode/Public/CustomEditorModeCommands.h"
#include "CustomEditorMode/Public/CustomWidgetTool.h"
#include "CustomEditorMode/Public/AnotherTool.h"
#include "Tools/UEdMode.h"
#include "Tools/EdModeInteractiveToolsContext.h"

#define LOCTEXT_NAMESPACE "CustomEditorMode"

const FEditorModeID UCustomEditorMode::ModeId = TEXT("EM_CustomModeId");

//Make sure to add a space after each caps letter in tool ids as Unreal is going to space it automatically to display it
const FString UCustomEditorMode::CustomWidgetToolId = TEXT("Custom Widget Tool");
const FString UCustomEditorMode::AnotherToolId = TEXT("Another Tool");

UCustomEditorMode::UCustomEditorMode()
{
	Info = FEditorModeInfo(ModeId,
		LOCTEXT("CustomEditorModeName", "Custom Editor"),
		FSlateIcon(),
		true);
}

UCustomEditorMode::~UCustomEditorMode()
{
}

void UCustomEditorMode::Enter()
{
	Super::Enter();

	RegisterTools();
}

void UCustomEditorMode::CreateToolkit()
{
	Toolkit = MakeShareable(new FCustomEditorModeToolkit());
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> UCustomEditorMode::GetModeCommands() const
{
	return FCustomEditorModeCommands::Get().GetCommands();
}

void UCustomEditorMode::RegisterTools()
{
	const FCustomEditorModeCommands& Commands = FCustomEditorModeCommands::Get();

	//Register the tool, this binds the command the open the tool
	auto CustomWidgetToolBuilder = NewObject<UCustomWidgetToolBuilder>(this);
	RegisterTool(Commands.CustomWidget, CustomWidgetToolId, CustomWidgetToolBuilder);
	
	auto AnotherToolBuilder = NewObject<UAnotherToolBuilder>(this);
	RegisterTool(Commands.AnotherTool, AnotherToolId, AnotherToolBuilder);

}

#undef LOCTEXT_NAMESPACE
