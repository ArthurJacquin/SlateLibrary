#pragma once

#include "CoreMinimal.h"
#include "Widgets/SWindow.h"

/**
 * Template functions for basic slate functionality
 */
class FSlateCommonUtilities
{
public:
/** Creates a popup window with the given content inside
* @SizingRule: Either Autosized or FixedSize 
* @Size: The size of the window, not needed if Autosized
**/
	static TSharedPtr<SWindow> OpenPopupWindow(const FText& WindowTitle, TSharedPtr<SWidget> WindowContent, ESizingRule SizingRule, FVector2D Size = FVector2D::Zero());
};
