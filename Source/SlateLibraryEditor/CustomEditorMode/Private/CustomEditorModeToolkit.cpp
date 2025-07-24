#include "../Public/CustomEditorModeToolkit.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "../Public/CustomEditorModeCommands.h"
#include "../Public/SCustomEditorMode.h"
#include "InteractiveTool.h"

FCustomEditorModeToolkit::FCustomEditorModeToolkit()
{

}

void FCustomEditorModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode)
{
	FModeToolkit::Init(InitToolkitHost, InOwningMode);
}

void FCustomEditorModeToolkit::GetToolPaletteNames(TArray<FName>& PaletteNames) const
{
	PaletteNames.Add(NAME_Default);
}

FText FCustomEditorModeToolkit::GetActiveToolDisplayName() const
{
	return ActiveToolDisplayName;
}

void FCustomEditorModeToolkit::OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool)
{
	FModeToolkit::OnToolStarted(Manager, Tool);

	ActiveToolDisplayName = Tool->GetToolInfo().ToolDisplayName;
	UpdatePrimaryModePanel();
}

void FCustomEditorModeToolkit::OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool)
{
	FModeToolkit::OnToolEnded(Manager, Tool);

	ActiveToolDisplayName = FText();
	UpdatePrimaryModePanel();
}

FName FCustomEditorModeToolkit::GetToolkitFName() const
{
	return FName("CustomEditorMode");
}

FText FCustomEditorModeToolkit::GetBaseToolkitName() const
{
	return NSLOCTEXT("CustomEditorModeToolkit", "DisplayName", "CustomEditor Tool");
}

TSharedPtr<SWidget> FCustomEditorModeToolkit::GetInlineContent() const
{
	FString ActiveToolName = GetActiveToolDisplayName().ToString();

	if(ActiveToolName == UCustomEditorMode::CustomWidgetToolId)
	{
		return MakeCustomWidgetToolWidget();
	}
	else if (ActiveToolName == UCustomEditorMode::AnotherToolId)
	{
		return MakeAnotherToolWidget();
	}

	return SNew(SSpacer);
}

TSharedPtr<SWidget> FCustomEditorModeToolkit::MakeCustomWidgetToolWidget() const
{
	return SNew(STextBlock)
		.Text(FText::FromString("Custom Widget"));
}

TSharedPtr<SWidget> FCustomEditorModeToolkit::MakeAnotherToolWidget() const
{
	return SNew(STextBlock)
		.Text(FText::FromString("Another tool"));
}
