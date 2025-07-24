#pragma once

#include "CoreMinimal.h"
#include "EditorModes.h"
#include "Toolkits/BaseToolkit.h"
#include "CustomEditorMode.h"
#include "../Public/SCustomEditorMode.h"

/**
 * Toolkit for a custom editor mode
 */
class FCustomEditorModeToolkit : public FModeToolkit
{
public:
	FCustomEditorModeToolkit();

	// FModeToolkit interface 
	virtual void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode) override;
	virtual void GetToolPaletteNames(TArray<FName>& PaletteNames) const override;
	FText GetActiveToolDisplayName() const override;

	// IToolkit interface 
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;

	/** Return the content to display in the main content area (under the toolbar) **/
	virtual TSharedPtr<SWidget> GetInlineContent() const override;

protected:
	/** Called when a tool start being active **/
	virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;

	/** Called when a tool stop being active **/
	virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;

private:
	/** Create the main widget for the tool "Custom Widget" **/
	TSharedPtr<SWidget> MakeCustomWidgetToolWidget() const;

	/** Create the main widget for the tool "Another Tool" **/
	TSharedPtr<SWidget> MakeAnotherToolWidget() const;

	/** The display name of the active tool **/
	FText ActiveToolDisplayName;

	/** The content shown into the main area of the mode tab, usually the currently selected tool **/
	TSharedPtr<SWidget> ToolkitWidget;
};
