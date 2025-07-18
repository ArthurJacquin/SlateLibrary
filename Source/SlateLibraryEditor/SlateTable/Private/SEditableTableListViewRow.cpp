#include "../Public/SEditableTableListViewRow.h"

void SEditableTableListViewRow::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)
{
	OwningTable = InArgs._OwningTable;
	RowDataPtr = InArgs._RowDataPtr;
	CurrentName = MakeShareable(new FName(RowDataPtr->RowId));
	SMultiColumnTableRow<FEditableTableRowListViewDataPtr>::Construct(
		FSuperRowType::FArguments()
		.Style(FAppStyle::Get(), "DataTableEditor.CellListViewRow"),
		InOwnerTableView
	);

	SetBorderImage(TAttribute<const FSlateBrush*>(this, &SEditableTableListViewRow::GetBorder));
}

TSharedRef<SWidget> SEditableTableListViewRow::GenerateWidgetForColumn(const FName& ColumnName)
{
	return MakeCellWidget(IndexInList, ColumnName);
}

TSharedRef<SWidget> SEditableTableListViewRow::MakeCellWidget(const int32 InRowIndex, const FName& InColumnId)
{
	int32 ColumnIndex = 0;

	//Find the column id
	TArray<FEditableTableColumnHeaderDataPtr>& AvailableColumns = OwningTable->AvailableColumns;
	for (ColumnIndex; ColumnIndex < AvailableColumns.Num(); ++ColumnIndex)
	{
		const FEditableTableColumnHeaderDataPtr& ColumnData = AvailableColumns[ColumnIndex];
		if (ColumnData->ColumnId == InColumnId)
		{
			break;
		}
	}

	// Valid column ID?
	if (AvailableColumns.IsValidIndex(ColumnIndex))
	{
		return SNew(SBox)
			.Padding(FMargin(4, 2, 4, 2))
			[
				SNew(STextBlock)
					.TextStyle(FAppStyle::Get(), "DataTableEditor.CellText")
					.ColorAndOpacity(FSlateColor::UseForeground())
					.Text(OwningTable, &SEditableTable::GetCellText, RowDataPtr, ColumnIndex)
			];
	}

	return SNullWidget::NullWidget;
}
