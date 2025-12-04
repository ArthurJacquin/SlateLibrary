#include "../Public/ActorUtilities.h"
#include "Engine/StaticMeshActor.h"
#include "Utilities/Public/EditorUtilities.h"

bool UActorUtilities::SpawnMeshActorAtLocation(UWorld* World, UStaticMesh* Mesh, const FVector& Location)
{
	if (World == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn mesh: World is NULL"));
		return false;
	}

	if (Mesh == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn mesh: Mesh is NULL"));
		return false;
	}

	// Create a new static mesh actor
	const FActorSpawnParameters SpawnInfo;
	AStaticMeshActor* NewActor = World->SpawnActor<AStaticMeshActor>(FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
	if (NewActor == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn mesh: Failed to create actor."));
		return false;
	}

	// Set the mesh
	UStaticMeshComponent* MeshComp = NewActor->GetStaticMeshComponent();
	if (MeshComp == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn mesh: Failed to find Static Mesh Component."));
		NewActor->Destroy();
		return false;
	}

	MeshComp->SetStaticMesh(Mesh);
	MeshComp->SetMobility(EComponentMobility::Movable);
	MeshComp->SetWorldTransform(FTransform(Location));

	UEditorUtilities::RefreshEditorViewports();

	return true;
}
