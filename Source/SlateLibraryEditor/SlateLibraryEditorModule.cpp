#include "SlateLibraryEditorModule.h"
#include "Modules/ModuleManager.h"
#include "LevelEditor.h"
#include "SlateTable/Public/SEditableTable.h"

IMPLEMENT_MODULE(SlateLibraryEditorModule, SlateLibraryEditorModule);

#define LOCTEXT_NAMESPACE "SlateLibraryEditorModule"

void SlateLibraryEditorModule::StartupModule()
{
    TSharedPtr<FExtender> TrainingMenuExtender = MakeShareable(new FExtender());

    // Add a menu extension to the "Window" menu
    TrainingMenuExtender->AddMenuBarExtension(
        "Help",
        EExtensionHook::After,
        nullptr,
        FMenuBarExtensionDelegate::CreateRaw(this, &SlateLibraryEditorModule::ExtendTopBarMenu)
    );

    // Add the extender to the level editor's menu extenders
    FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
    LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(TrainingMenuExtender);
}

void SlateLibraryEditorModule::ShutdownModule()
{
}

void SlateLibraryEditorModule::ExtendTopBarMenu(FMenuBarBuilder& MenuBarBuilder)
{
    MenuBarBuilder.AddPullDownMenu(
        LOCTEXT("TrainingTopBar", "Training"),
        LOCTEXT("TrainingTopBarTooltip", "Tab with training fonctionalities"),
        FNewMenuDelegate::CreateRaw(this, &SlateLibraryEditorModule::MakeTrainingMenu)
    );
}

void SlateLibraryEditorModule::MakeTrainingMenu(FMenuBuilder& MenuBuilder)
{
    MenuBuilder.AddMenuEntry(
        LOCTEXT("SlateTableTest", "Slate Table"),
        LOCTEXT("SlateTableTooltip", "A table made with slate"),
        FSlateIcon(),
        FUIAction(FExecuteAction::CreateRaw(this, &SlateLibraryEditorModule::OpenSlateTableWidget))
    );
}

void SlateLibraryEditorModule::OpenSlateTableWidget()
{
    //Create window
    TSharedPtr<SWindow> Window = SNew(SWindow)
        .Title(FText::FromString(TEXT("Slate Table")))
        .SizingRule(ESizingRule::Autosized)
        .AutoCenter(EAutoCenter::PreferredWorkArea)
        .SupportsMinimize(false)
        .SupportsMaximize(false);

    TSharedPtr<SEditableTable> WindowContent = SNew(SEditableTable);

    //Set window content
    Window->SetContent(WindowContent.ToSharedRef());

    //Show window
    GEditor->EditorAddModalWindow(Window.ToSharedRef());
}

#undef LOCTEXT_NAMESPACE
