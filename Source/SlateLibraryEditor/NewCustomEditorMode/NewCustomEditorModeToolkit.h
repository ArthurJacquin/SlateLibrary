#pragma once

#include "CoreMinimal.h"
#include "EditorModes.h"
#include "Toolkits/BaseToolkit.h"
#include "NewCustomEditorMode.h"

/**
 * Toolkit for a custom editor mode
 */
class FNewCustomEditorModeToolkit : public FModeToolkit
{
public:
	FNewCustomEditorModeToolkit();

	// FModeToolkit interface 
	virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode) override;
	virtual void GetToolPaletteNames(TArray<FName>& PaletteNames) const override;
	virtual void RebuildModeToolPalette() override;
	virtual FText GetToolPaletteDisplayName(FName Palette) const override;
	virtual TSharedPtr<SWidget> GetInlineContent() const override;

	// IToolkit interface 
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;

	/** Return the name of the active palette */
	FName GetActivePaletteName() const;

protected:
	/** Called when starting to use a tool */
	void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;

	/** Called when stopping to use a tool */
	void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;

	/** Setup the toolkit builder to be able to build the palettes later */
	void InitToolkitBuilder();

	/** Called when the active palette changed */
	FDelegateHandle ActivePaletteChangedHandle;

private:
	/** Do what is needed when the active palette changed */
	void OnPaletteChanged();

	/** Display a warning with the given message in the warning area */
	void PostToolWarning(const FText& Message);

	/** Remove the warning message */
	void ClearToolWarning();

	/** The text shown is the header area of the mode */
	TSharedPtr<STextBlock> ModeHeaderArea;

	/** Text shown in the warning area of the mode */
	TSharedPtr<STextBlock> ModeWarningArea;

	/** Text shown in the warning area of the tool */
	TSharedPtr<STextBlock> ToolWarningArea;
};
