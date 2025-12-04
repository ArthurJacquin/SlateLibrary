#pragma once

#include "CoreMinimal.h"
#include "BaseTools/SingleClickTool.h"
#include "InteractiveTool.h"
#include "Engine/HitResult.h"
#include "Engine/World.h"
#include "ToolContextInterfaces.h"
#include "Engine/StaticMeshActor.h"
#include "Utilities/Public/ActorUtilities.h"

#include "PlaceCubeTool.generated.h"

/**
 * Settings UObject for UPlaceCubeTool. This UClass inherits from UInteractiveToolPropertySet,
 * which provides an OnModified delegate that the Tool will listen to for changes in property values.
 */
UCLASS(Transient)
class SLATELIBRARYEDITOR_API UPlaceCubeToolProperties : public UInteractiveToolPropertySet
{
	GENERATED_BODY()
public:
	UPlaceCubeToolProperties()
	{
		bPlaceOnObjects = true;
		GroundHeight = 0.0f;
	}

	/** Place actors on existing objects */
	UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayName = "Place On Objects"))
	bool bPlaceOnObjects;

	/** Height of ground plane */
	UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayName = "Ground Height", UIMin = "-1000.0", UIMax = "1000.0", ClampMin = "-1000000", ClampMax = "1000000.0"))
	float GroundHeight;
};

/**
 * Tool to allow selection in the level
 */
UCLASS()
class SLATELIBRARYEDITOR_API UPlaceCubeTool : public USingleClickTool
{
	GENERATED_BODY()

public:
	UPlaceCubeTool()
	{}

	/* USingleClickTool overrides */
	virtual void Setup() override
	{
		USingleClickTool::Setup();
		Properties = NewObject<UPlaceCubeToolProperties>(this);
		AddToolPropertySource(Properties);
	}

	void OnClicked(const FInputDeviceRay& ClickPos) override
	{
		FVector NewActorLocation;

		// Cast ray into world to find hit position
		const FVector RayStart = ClickPos.WorldRay.Origin;
		const FVector RayEnd = ClickPos.WorldRay.PointAt(999999);
		const FCollisionObjectQueryParams QueryParams(FCollisionObjectQueryParams::AllObjects);
		FHitResult Result;
		const bool bHitWorld = TargetWorld->LineTraceSingleByObjectType(Result, RayStart, RayEnd, QueryParams);
		if (Properties->bPlaceOnObjects && bHitWorld)
		{
			NewActorLocation = Result.ImpactPoint;
		}
		else
		{
			// Hit the ground plane
			const FPlane GroundPlane(FVector(0, 0, Properties->GroundHeight), FVector(0, 0, 1));
			NewActorLocation = FMath::RayPlaneIntersection(ClickPos.WorldRay.Origin, ClickPos.WorldRay.Direction, GroundPlane);
		}

		UStaticMesh* Mesh = LoadObject<UStaticMesh>(TargetWorld, TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
		UActorUtilities::SpawnMeshActorAtLocation(TargetWorld, Mesh, NewActorLocation);
	}

	/* End USingleClickTool overrides */

	virtual void SetWorld(UWorld* World) { TargetWorld = World; }

protected:
	UPROPERTY(Transient)
	TObjectPtr<UPlaceCubeToolProperties> Properties;

	UPROPERTY(Transient)
	TObjectPtr<UWorld> TargetWorld;
};

/**
 * Builder for UPlaceCubeTool
 * Enabled only if there's actors in the level
 */
UCLASS()
class SLATELIBRARYEDITOR_API UPlaceCubeToolBuilder : public UInteractiveToolBuilder
{
	GENERATED_BODY()

public:

	/** Conditions to enable the tool, here no condition */
	virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override
	{
		return true;
	}

	/** Create the tool */
	virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const
	{
		UPlaceCubeTool* NewTool = NewObject<UPlaceCubeTool>();
		NewTool->SetWorld(SceneState.World);
		return NewTool;
	}
};
