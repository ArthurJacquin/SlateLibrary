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

// New Custom Editor Mode
#include "NewCustomEditorMode/NewCustomEditorModeCommands.h"
#include "NewCustomEditorMode/NewCustomEditorModeStyle.h"

// Details customization
#include "DetailsCustomization/CustomDetailsActorDetailsCustomization.h"
#include "Actors/CustomDetailsActor.h"

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

    //New Custom Editor Mode setup
    FNewCustomEditorModeStyle::Initialize();
    FNewCustomEditorModeCommands::Register();

    //Dockable Tab Spawner: Register tab to spawn
    FGlobalTabmanager::Get()->RegisterTabSpawner(DockableTabId,
        FOnSpawnTab::CreateRaw(this, &SlateLibraryEditor::SpawnDockableTab),
        FCanSpawnTab()
        );

    // Details customization
    FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    PropertyModule.RegisterCustomClassLayout(ACustomDetailsActor::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FCustomDetailsActorDetailsCustomization::MakeInstance));
}

void SlateLibraryEditor::ShutdownModule()
{
    // Unregister Custom Editor Mode commands
    FCustomEditorModeCommands::Unregister();

    // New Custom Editor Mode
    FNewCustomEditorModeCommands::Unregister();
    FNewCustomEditorModeStyle::Shutdown();

    // Details customization
    FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
    PropertyModule.UnregisterCustomClassLayout(ACustomDetailsActor::StaticClass()->GetFName());
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
