#pragma once

#include "CoreMinimal.h"
#include "InteractiveToolBuilder.h"
#include "BaseTools/SingleClickTool.h"

#include "AnotherTool.generated.h"

/**
 * Builder for the tool
 */
UCLASS()
class SLATELIBRARYEDITOR_API UAnotherToolBuilder : public UInteractiveToolBuilder
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
class SLATELIBRARYEDITOR_API UAnotherTool : public UInteractiveTool
{
	GENERATED_BODY()
public:
	UAnotherTool();

protected:
	virtual void Setup() override;
};
