#include "CustomEditorMode_New.h"
#include "CustomEditorModeToolkit_New.h"
#include "CustomEditorModeCommands_New.h"
#include "Tools/UEdMode.h"
#include "Tools/EdModeInteractiveToolsContext.h"

// Our tools
#include "Tools/EnableSelectionTool.h"
#include "Tools/DisableSelectionTool.h"
#include "Tools/PlaceCubeTool.h"
#include "Tools/PlaceSphereTool.h"

#define LOCTEXT_NAMESPACE "FCustomEditorModeNew"

const FEditorModeID UCustomEditorMode_New::ModeId = TEXT("EM_CustomMode_New_Id");

//Make sure to add a space before each caps letter in tool ids as Unreal is going to space it automatically to display it
const FString UCustomEditorMode_New::EnableSelectionToolId = TEXT("Enable Selection");
const FString UCustomEditorMode_New::DisableSelectionToolId = TEXT("Disable Selection");

const FString UCustomEditorMode_New::PlaceCubeToolId = TEXT("Place Cube");
const FString UCustomEditorMode_New::PlaceSphereToolId = TEXT("Place Sphere");

UCustomEditorMode_New::UCustomEditorMode_New()
{
	Info = FEditorModeInfo(ModeId,
		LOCTEXT("CustomEditorModeNewName", "New Custom Editor"),
		FSlateIcon(),
		true);
}

UCustomEditorMode_New::~UCustomEditorMode_New()
{
}

void UCustomEditorMode_New::Enter()
{
	Super::Enter();

	RegisterTools();

	// Enable the default tool
	GetToolManager()->SelectActiveToolType(EToolSide::Left, UCustomEditorMode_New::EnableSelectionToolId);
}

void UCustomEditorMode_New::Exit()
{
	Super::Exit();
}

void UCustomEditorMode_New::CreateToolkit()
{
	Toolkit = MakeShareable(new FCustomEditorModeToolkit_New());
}

bool UCustomEditorMode_New::IsSelectionAllowed(AActor* InActor, bool bInSelection) const
{
	// Allow selection only if the selection tool is active
	return IsActiveToolFromClass(UEnableSelectionTool::StaticClass());
}

bool UCustomEditorMode_New::IsActiveToolFromClass(UClass* ToolClass) const
{
	UInteractiveTool* ActiveTool = GetActiveTool();
	return ActiveTool != nullptr && ActiveTool->IsA(ToolClass);
}

void UCustomEditorMode_New::RegisterTools()
{
	const FCustomEditorModeCommands_New& Commands = FCustomEditorModeCommands_New::Get();

	//Register the tools, this binds the command the open the tool
	
	// Selection Tools
	UEnableSelectionToolBuilder* EnableSelectionToolBuilder = NewObject<UEnableSelectionToolBuilder>(this);
	RegisterTool(Commands.Selection_EnableSelection, EnableSelectionToolId, EnableSelectionToolBuilder);
	
	UDisableSelectionToolBuilder* DisableSelectionToolBuilder = NewObject<UDisableSelectionToolBuilder>(this);
	RegisterTool(Commands.Selection_DisableSelection, DisableSelectionToolId, DisableSelectionToolBuilder);

	// Place Tools
	UPlaceCubeToolBuilder* PlaceCubeToolBuilder = NewObject<UPlaceCubeToolBuilder>(this);
	RegisterTool(Commands.Place_Cube, PlaceCubeToolId, PlaceCubeToolBuilder);

	UPlaceSphereToolBuilder* PlaceSphereToolBuilder = NewObject<UPlaceSphereToolBuilder>(this);
	RegisterTool(Commands.Place_Sphere, PlaceSphereToolId, PlaceSphereToolBuilder);

	// Build the widget with the new palettes
	GetToolkit()->RebuildModeToolPalette();
}

FCustomEditorModeToolkit_New* UCustomEditorMode_New::GetToolkit() const
{
	return (FCustomEditorModeToolkit_New*)Toolkit.Get();
}

UInteractiveTool* UCustomEditorMode_New::GetActiveTool() const
{
	if (FCustomEditorModeToolkit_New* ModeToolkit = GetToolkit())
	{
		return ModeToolkit->ActiveTool;
	}

	return nullptr;
}

FName UCustomEditorMode_New::GetActivePaletteName() const
{
	if (FCustomEditorModeToolkit_New* ModeToolkit = GetToolkit())
	{
		return ModeToolkit->GetActivePaletteName();
	}

	return FName();
}
