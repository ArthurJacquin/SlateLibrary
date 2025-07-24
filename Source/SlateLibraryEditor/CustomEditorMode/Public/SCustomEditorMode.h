#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class FCustomEditorModeToolkit;

/**
 * Slate widget for the custom editor mode
 */
class SCustomEditorMode : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCustomEditorMode)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, TSharedRef<FCustomEditorModeToolkit> InParentToolkit);

private:
	/** Creates the toolbar. */
	//TSharedRef<SWidget> BuildToolBar();

	TWeakPtr<FCustomEditorModeToolkit> ParentToolkit;
};
