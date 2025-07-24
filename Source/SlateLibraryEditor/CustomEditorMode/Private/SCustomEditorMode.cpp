#include "../Public/SCustomEditorMode.h"
#include "../Public/CustomEditorModeToolkit.h"

void SCustomEditorMode::Construct(const FArguments& InArgs, TSharedRef<FCustomEditorModeToolkit> InParentToolkit)
{
	ParentToolkit = InParentToolkit;

	ChildSlot
	[
		SNew(STextBlock)
		.Text(FText::FromString(TEXT("Hello")))
	];
}
