#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class IPropertyHandle;

/**
 * Details panel customization for ACustomDetailsActor
 */
class SLATELIBRARYEDITOR_API FCustomDetailsActorDetailsCustomization : public IDetailCustomization
{
public:
	void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

	static TSharedRef<IDetailCustomization> MakeInstance();
};
