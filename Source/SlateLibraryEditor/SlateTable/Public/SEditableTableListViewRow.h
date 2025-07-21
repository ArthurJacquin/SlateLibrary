#pragma once

#include "CoreMinimal.h"
#include "SEditableTable.h"

/**
 * 
 */
class SLATELIBRARYEDITOR_API SEditableTableListViewRow : public SMultiColumnTableRow<FEditableTableRowListViewDataPtr>
{
public:
	SLATE_BEGIN_ARGS(SEditableTableListViewRow)
		{}

		SLATE_ARGUMENT(SEditableTable*, OwningTable)

		SLATE_ARGUMENT(FEditableTableRowListViewDataPtr, RowDataPtr)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView);

	virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;

	FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;

private:
	TSharedRef<SWidget> MakeCellWidget(const int32 InRowIndex, const FName& InColumnId);

	void OnCellEnterEdit(const FText& Text);

	void OnCellModified(const FText& Text, ETextCommit::Type CommitType);

	SEditableTable* OwningTable;

	FEditableTableRowListViewDataPtr RowDataPtr;

	/** List the editable cells widgets link to the text object they are editing **/
	TMap<TSharedPtr<SInlineEditableTextBlock>, FText*> EditableCells;

	/** The cell currently being edited **/
	TSharedPtr<SInlineEditableTextBlock> EditedCell;
};
