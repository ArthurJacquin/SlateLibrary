#include "../Public/CustomWidgetTool.h"

UInteractiveTool* UCustomWidgetToolBuilder::BuildTool(const FToolBuilderState& SceneState) const
{
	UCustomWidgetTool* Tool = NewObject<UCustomWidgetTool>();
	return Tool;
}

UCustomWidgetTool::UCustomWidgetTool()
{

}

void UCustomWidgetTool::Setup()
{
	Super::Setup();
}
