#include "SlateLibraryEditor.h"
#include "Modules/ModuleManager.h"
#include "LevelEditor.h"
#include "SlateTable/Public/SEditableTable.h"

// Custom Editor Mode
#include "CustomEditorMode/Public/CustomEditorMode.h"
#include "EditorModeRegistry.h"
#include "CustomEditorMode/Public/CustomEditorModeCommands.h"
#include "Utilities/Public/SlateCommonUtilities.h"

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
}

void SlateLibraryEditor::ShutdownModule()
{
    // Unregister Custom Editor Mode commands
    FCustomEditorModeCommands::Unregister();
}

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
    MenuBuilder.AddMenuEntry(
        LOCTEXT("SlateTableTest", "Slate Table"),
        LOCTEXT("SlateTableTooltip", "A table made with slate"),
        FSlateIcon(),
        FUIAction(FExecuteAction::CreateRaw(this, &SlateLibraryEditor::OpenSlateTableWidget))
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

#undef LOCTEXT_NAMESPACE
