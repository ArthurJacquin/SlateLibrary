#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ActorUtilities.generated.h"

/**
 * Actor Utilities
 */
UCLASS(Abstract)
class SLATELIBRARYEDITOR_API UActorUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/** Spawn a AStaticMeshActor at the given location with the given mesh */
	UFUNCTION(BlueprintCallable, Category = "Actor Utilities")
	static bool SpawnMeshActorAtLocation(UWorld* World, UStaticMesh* Mesh, const FVector& Location);	
};
