using UnrealBuildTool;

public class SlateLibraryEditor: ModuleRules
{
    public SlateLibraryEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PrivateDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "SlateCore",
            "Slate",
            "LevelEditor",
            "Blutility",
            "UMG",
            "UnrealEd",
            "InputCore",
            "EditorFramework",
            "WidgetRegistration",
            "InteractiveToolsFramework"
        });
    }
}
