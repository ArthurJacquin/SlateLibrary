#pragma once

#include "CoreMinimal.h"
#include "InteractiveToolBuilder.h"
#include "BaseTools/SingleClickTool.h"

#include "CustomWidgetTool.generated.h"

/**
 * Builder for the tool
 */
UCLASS()
class SLATELIBRARYEDITOR_API UCustomWidgetToolBuilder : public UInteractiveToolBuilder
{
	GENERATED_BODY()

public:
	virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override { return true; }
	virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;
};

/**
 * The tool itself
 */
UCLASS()
class SLATELIBRARYEDITOR_API UCustomWidgetTool : public UInteractiveTool
{
	GENERATED_BODY()
public:
	UCustomWidgetTool();

protected:
	virtual void Setup() override;
};
