#include "NewCustomEditorModeToolkit.h"
#include "NewCustomEditorModeCommands.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "InteractiveTool.h"
#include "Tools/EdModeInteractiveToolsContext.h"

FNewCustomEditorModeToolkit::FNewCustomEditorModeToolkit()
{
	bUsesToolkitBuilder = true;
}

void FNewCustomEditorModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode)
{
	FModeToolkit::Init(InitToolkitHost, InOwningMode);

	InitToolkitBuilder();

	// Create mode warning area text
	ModeWarningArea = SNew(STextBlock)
		.AutoWrapText(true)
		.Font(FCoreStyle::GetDefaultFontStyle("Bold", 9))
		.ColorAndOpacity(FSlateColor(FLinearColor(0.9f, 0.15f, 0.15f)));
	ModeWarningArea->SetText(FText::FromString("Mode Warning Area"));
	ModeWarningArea->SetVisibility(EVisibility::Visible); // Set to always visible for this example

	// Create tool warning area text
	ToolWarningArea = SNew(STextBlock)
		.AutoWrapText(true)
		.Font(FCoreStyle::GetDefaultFontStyle("Bold", 9))
		.ColorAndOpacity(FSlateColor(FLinearColor(0.9f, 0.15f, 0.15f)));
	ToolWarningArea->SetText(FText::FromString("Tool Warning Area"));
	ToolWarningArea->SetVisibility(EVisibility::Visible); // Set to always visible for this example

	// Create details view
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.bAllowSearch = false;
	DetailsViewArgs.bShowPropertyMatrixButton = false;
	DetailsViewArgs.bShowOptions = false;
	DetailsViewArgs.bHideSelectionTip = true;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;

	ModeDetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);

	// Link this toolkit to the editor mode builder and build the tab
	if (HasToolkitBuilder())
	{
		ToolkitSections->ModeWarningArea = ModeWarningArea;
		ToolkitSections->DetailsView = ModeDetailsView;
		ToolkitSections->ToolWarningArea = ToolWarningArea;

		SAssignNew(ToolkitWidget, SBorder)
			.HAlign(HAlign_Fill)
			.Padding(0)
			.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
			[
				ToolkitBuilder->GenerateWidget()->AsShared()
			];
	}

	GetScriptableEditorMode()->GetInteractiveToolsContext(EToolsContextScope::EdMode)->OnToolWarningMessage.AddSP(this, &FNewCustomEditorModeToolkit::PostToolWarning);
}

void FNewCustomEditorModeToolkit::GetToolPaletteNames(TArray<FName>& PaletteNames) const
{
	PaletteNames.Reset();

	for (const FNewCustomEditorModeCommands::FPaletteCommand& Palette : FNewCustomEditorModeCommands::Get().GetPalettes())
	{
		PaletteNames.Add(FName(Palette.Name));
	}
}

void FNewCustomEditorModeToolkit::RebuildModeToolPalette()
{
	ToolkitBuilder->InitializeCategoryToolbar(true);

	const FNewCustomEditorModeCommands& Commands = FNewCustomEditorModeCommands::Get();

	TSharedPtr<FUICommandInfo> ActivePaletteOnLoad;
	TArray<FName> PaletteNames;
	GetToolPaletteNames(PaletteNames);
	
	// Go through palettes and initialize the tools
	for (int32 i = 0; i < PaletteNames.Num(); ++i)
	{
		const FName& PaletteName = PaletteNames[i];

		// Find tools for this palette
		TArray<TSharedPtr<FUICommandInfo>> PaletteCommandList;
		for (const FNewCustomEditorModeCommands::FStartToolCommand& Tool : Commands.GetTools())
		{
			if (Tool.PaletteName == PaletteName)
			{
				PaletteCommandList.Add(Tool.ToolCommand);
			}
		}

		// Get the command to load the palette
		bool bFoundLoadPaletteCommand = false;
		TSharedPtr<FUICommandInfo> LoadPaletteCommand = Commands.FindPaletteByName(PaletteName.ToString(), bFoundLoadPaletteCommand);
		check(bFoundLoadPaletteCommand);
		
		// Mark the first palette as the one to activate by default
		if (i == 0)
		{
			ActivePaletteOnLoad = LoadPaletteCommand;
		}

		// Add palette to the palette list
		ToolkitBuilder->AddPalette(
			MakeShareable(new FToolPalette(LoadPaletteCommand.ToSharedRef(), PaletteCommandList)));
	}

	// Set the default active palette
	if (ActivePaletteOnLoad)
	{
		ToolkitBuilder->SetActivePaletteOnLoad(ActivePaletteOnLoad.Get());
	}

	// Refresh the widget
	ToolkitBuilder->UpdateWidget();
	ToolkitBuilder->RefreshCategoryToolbarWidget(true);
}

FText FNewCustomEditorModeToolkit::GetToolPaletteDisplayName(FName Palette) const
{
	return FText::FromName(Palette);
}

TSharedPtr<SWidget> FNewCustomEditorModeToolkit::GetInlineContent() const
{
	return ToolkitWidget;
}

FName FNewCustomEditorModeToolkit::GetToolkitFName() const
{
	return FName("CustomEditorMode_New");
}

FText FNewCustomEditorModeToolkit::GetBaseToolkitName() const
{
	return NSLOCTEXT("CustomEditorModeToolkit", "DisplayName", "CustomEditor Tool");
}

void FNewCustomEditorModeToolkit::OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool)
{
	FModeToolkit::OnToolStarted(Manager, Tool);

	// Set detail panel object
	if (UInteractiveTool* ActiveTool = OwningEditorMode->GetToolManager(EToolsContextScope::EdMode)->GetActiveTool(EToolSide::Left))
	{
		const TArray<UObject*>&  Properties = ActiveTool->GetToolProperties();
		ModeDetailsView->SetObject(Properties.IsEmpty() ? nullptr : Properties[0]);
	}
}

void FNewCustomEditorModeToolkit::OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool)
{
	FModeToolkit::OnToolEnded(Manager, Tool);

	ModeDetailsView->SetObject(nullptr);

	ClearToolWarning();
}

void FNewCustomEditorModeToolkit::InitToolkitBuilder()
{
	UEdMode* ScriptableMode = GetScriptableEditorMode().Get();

	ToolkitSections = MakeShared<FToolkitSections>();

	// Settings for the toolkit
	FToolkitBuilderArgs ToolkitBuilderArgs(ScriptableMode->GetModeInfo().ToolbarCustomizationName);
	ToolkitBuilderArgs.ToolkitCommandList = GetToolkitCommands();
	ToolkitBuilderArgs.ToolkitSections = ToolkitSections;
	ToolkitBuilderArgs.SelectedCategoryTitleVisibility = EVisibility::Collapsed;
	ToolkitBuilderArgs.CategoryReclickBehavior = FToolkitBuilder::ECategoryReclickBehavior::TreatAsChanged;

	// Build the toolkit
	ToolkitBuilder = MakeShared<FToolkitBuilder>(ToolkitBuilderArgs);
	ToolkitBuilder->SetCategoryButtonLabelVisibility(true);

	// Bind OnPaletteChanged event and store the event for future call
	ActivePaletteChangedHandle = ToolkitBuilder->OnActivePaletteChanged.AddRaw(this, &FNewCustomEditorModeToolkit::OnPaletteChanged);
}

void FNewCustomEditorModeToolkit::OnPaletteChanged()
{
	// Deactivate the active tool
	if (UInteractiveToolManager* ToolManager = OwningEditorMode->GetToolManager(EToolsContextScope::EdMode))
	{
		ToolManager->DeactivateTool(EToolSide::Left, EToolShutdownType::Completed);
	}

	// Make the new active palette visible
	ToolkitBuilder->SetActivePaletteCommandsVisibility(EVisibility::Visible);
}

void FNewCustomEditorModeToolkit::PostToolWarning(const FText& Message)
{
	// Set the text and show it
	ToolWarningArea->SetText(Message);
	ToolWarningArea->SetVisibility(EVisibility::Visible);
}

void FNewCustomEditorModeToolkit::ClearToolWarning()
{
	// Clear the text and hide it
	ToolWarningArea->SetText(FText());
	ToolWarningArea->SetVisibility(EVisibility::Collapsed);
}
