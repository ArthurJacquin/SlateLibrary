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

private:
	TSharedRef<SWidget> MakeCellWidget(const int32 InRowIndex, const FName& InColumnId);

	SEditableTable* OwningTable;

	FEditableTableRowListViewDataPtr RowDataPtr;

	TSharedPtr<FName> CurrentName;
};
