#include "NewCustomEditorMode.h"
#include "NewCustomEditorModeToolkit.h"
#include "NewCustomEditorModeCommands.h"
#include "Tools/UEdMode.h"
#include "Tools/EdModeInteractiveToolsContext.h"

// Our tools
#include "Tools/EnableSelectionTool.h"
#include "Tools/DisableSelectionTool.h"
#include "Tools/PlaceCubeTool.h"
#include "Tools/PlaceSphereTool.h"

#define LOCTEXT_NAMESPACE "NewCustomEditorMode"

const FEditorModeID UNewCustomEditorMode::ModeId = TEXT("EM_CustomMode_New_Id");

//Make sure to add a space before each caps letter in tool ids as Unreal is going to space it automatically to display it
const FString UNewCustomEditorMode::EnableSelectionToolId = TEXT("Enable Selection");
const FString UNewCustomEditorMode::DisableSelectionToolId = TEXT("Disable Selection");

const FString UNewCustomEditorMode::PlaceCubeToolId = TEXT("Place Cube");
const FString UNewCustomEditorMode::PlaceSphereToolId = TEXT("Place Sphere");

UNewCustomEditorMode::UNewCustomEditorMode()
{
	Info = FEditorModeInfo(ModeId,
		LOCTEXT("CustomEditorModeNewName", "New Custom Editor"),
		FSlateIcon(),
		true);
}

UNewCustomEditorMode::~UNewCustomEditorMode()
{
}

void UNewCustomEditorMode::Enter()
{
	Super::Enter();

	RegisterTools();

	// Enable the default tool
	GetToolManager()->SelectActiveToolType(EToolSide::Left, UNewCustomEditorMode::EnableSelectionToolId);
}

void UNewCustomEditorMode::Exit()
{
	Super::Exit();
}

void UNewCustomEditorMode::CreateToolkit()
{
	Toolkit = MakeShareable(new FNewCustomEditorModeToolkit());
}

bool UNewCustomEditorMode::IsSelectionAllowed(AActor* InActor, bool bInSelection) const
{
	// Allow selection only if the selection tool is active
	return IsActiveToolFromClass(UEnableSelectionTool::StaticClass());
}

bool UNewCustomEditorMode::IsActiveToolFromClass(UClass* ToolClass) const
{
	UInteractiveTool* ActiveTool = GetToolManager(EToolsContextScope::EdMode)->GetActiveTool(EToolSide::Left);
	return ActiveTool != nullptr && ActiveTool->IsA(ToolClass);
}

void UNewCustomEditorMode::RegisterTools()
{
	const FNewCustomEditorModeCommands& Commands = FNewCustomEditorModeCommands::Get();

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

FNewCustomEditorModeToolkit* UNewCustomEditorMode::GetToolkit() const
{
	return (FNewCustomEditorModeToolkit*)Toolkit.Get();
}
