#include "SlateLibraryEditor.h"
#include "Modules/ModuleManager.h"
#include "LevelEditor.h"
#include "SlateTable/Public/SEditableTable.h"

// Custom Editor Mode
#include "CustomEditorMode/Public/CustomEditorMode.h"
#include "EditorModeRegistry.h"
#include "CustomEditorMode/Public/CustomEditorModeCommands.h"
#include "Utilities/Public/SlateCommonUtilities.h"
#include "Framework/Docking/TabManager.h"

IMPLEMENT_MODULE(SlateLibraryEditor, SlateLibraryEditor);

#define LOCTEXT_NAMESPACE "SlateLibraryEditor"

void SlateLibraryEditor::StartupModule()
{
    TSharedPtr<FExtender> TrainingMenuExtender = MakeShareable(new FExtender());

    // Add a menu extension after the "Help" menu
    TrainingMenuExtender->AddMenuBarExtension(
        "Help",
        EExtensionHook::After,
        nullptr,
        FMenuBarExtensionDelegate::CreateRaw(this, &SlateLibraryEditor::ExtendTopBarMenu)
    );

    // Add the extender to the level editor's menu extenders
    FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
    LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(TrainingMenuExtender);

    // Register Custom Editor Mode commands
    FCustomEditorModeCommands::Register();

    //Dockable Tab Spawner: Register tab to spawn
    FGlobalTabmanager::Get()->RegisterTabSpawner(DockableTabId,
        FOnSpawnTab::CreateRaw(this, &SlateLibraryEditor::SpawnDockableTab),
        FCanSpawnTab()
        );
}

void SlateLibraryEditor::ShutdownModule()
{
    // Unregister Custom Editor Mode commands
    FCustomEditorModeCommands::Unregister();
}

const FName SlateLibraryEditor::DockableTabId = TEXT("DockableTab");

void SlateLibraryEditor::ExtendTopBarMenu(FMenuBarBuilder& MenuBarBuilder)
{
    MenuBarBuilder.AddPullDownMenu(
        LOCTEXT("TrainingTopBar", "Training"),
        LOCTEXT("TrainingTopBarTooltip", "Tab with training fonctionalities"),
        FNewMenuDelegate::CreateRaw(this, &SlateLibraryEditor::MakeTrainingMenu)
    );
}

void SlateLibraryEditor::MakeTrainingMenu(FMenuBuilder& MenuBuilder)
{
    // Slate Table
    MenuBuilder.AddMenuEntry(
        LOCTEXT("SlateTableTest", "Slate Table"),
        LOCTEXT("SlateTableTooltip", "A table made with slate"),
        FSlateIcon(),
        FUIAction(FExecuteAction::CreateRaw(this, &SlateLibraryEditor::OpenSlateTableWidget))
    );

    // Dockable tab spawner
    MenuBuilder.AddMenuEntry(
        LOCTEXT("DockableTabSpawner", "Dockable Tab Spawner"),
        LOCTEXT("DockableTabSpawnerTooltip", "Spawn a dockable tab"),
        FSlateIcon(),
        FUIAction(FExecuteAction::CreateLambda([this](){ FGlobalTabmanager::Get()->TryInvokeTab(DockableTabId); }))
    );
}

void SlateLibraryEditor::OpenSlateTableWidget()
{
    FSlateCommonUtilities::OpenPopupWindow(
        FText::FromString(TEXT("Slate Table")),
        SNew(SEditableTable),
        ESizingRule::Autosized
        );
}

TSharedRef<SDockTab> SlateLibraryEditor::SpawnDockableTab(const FSpawnTabArgs& Args)
{
    TSharedPtr<SDockTab> DockableTab = SNew(SDockTab);
    DockableTab->SetContent(
        SNew(STextBlock)
        .Text(LOCTEXT("DockableTabContentText", "A Dockable Tab"))
    );

    return DockableTab.ToSharedRef();
}

#undef LOCTEXT_NAMESPACE
