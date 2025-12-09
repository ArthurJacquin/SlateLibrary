#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomDetailsActor.generated.h"

/**
 * An actor that has a customized details panel. See CustomDetailsActorDetailsCustomization.h
 */
UCLASS(BlueprintType)
class SLATELIBRARY_API ACustomDetailsActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomDetailsActor(const FObjectInitializer& ObjectInitializer)
		: AActor(ObjectInitializer)
	{}

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UStaticMesh> CustomMesh;
 
	UPROPERTY(EditAnywhere)
	float CustomFloat;
		
	UPROPERTY(EditAnywhere)
	bool CustomBool;
};
