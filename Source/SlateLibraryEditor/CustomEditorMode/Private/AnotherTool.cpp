#include "../Public/AnotherTool.h"

UInteractiveTool* UAnotherToolBuilder::BuildTool(const FToolBuilderState& SceneState) const
{
	UAnotherTool* Tool = NewObject<UAnotherTool>();
	return Tool;
}

UAnotherTool::UAnotherTool()
{
}

void UAnotherTool::Setup()
{
	Super::Setup();
}
