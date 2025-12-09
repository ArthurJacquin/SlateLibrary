using UnrealBuildTool;

public class SlateLibraryEditor: ModuleRules
{
    public SlateLibraryEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicIncludePaths.AddRange(
            new string[] {
                ModuleDirectory
            }
        );

        PrivateDependencyModuleNames.AddRange(new string[] {
            "Blutility",
            "Core",
            "CoreUObject",
            "EditorFramework",
            "Engine",
            "InputCore",
            "InteractiveToolsFramework",
            "LevelEditor",
            "SlateCore",
            "Slate",
            "SlateLibrary",
            "UMG",
            "UnrealEd",
            "WidgetRegistration"
        });
    }
}
