#include "../Public/SEditableTableListViewRow.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"

void SEditableTableListViewRow::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView)
{
	OwningTable = InArgs._OwningTable;
	RowDataPtr = InArgs._RowDataPtr;
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

FReply SEditableTableListViewRow::OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent)
{
	for (auto EditableTextCell : EditableCells)
	{
		if (EditableTextCell.Key->IsHovered())
		{
			EditableTextCell.Key->EnterEditingMode();
			break;
		}
	}
	return FReply::Handled();
}

TSharedRef<SWidget> SEditableTableListViewRow::MakeCellWidget(const int32 InRowIndex, const FName& InColumnId)
{
	int32 ColumnIndex = 0;

	// RowId
	const FName RowIdColumnId("RowId");
	if (InColumnId.IsEqual(RowIdColumnId))
	{
		return SNew(SBox)
			.Padding(FMargin(4, 2, 4, 2))
			[
				SNew(STextBlock)
					.TextStyle(FAppStyle::Get(), "DataTableEditor.CellText")
					.Text(FText::FromName(RowDataPtr->RowId))
					.ColorAndOpacity(FSlateColor::UseForeground())
			];
	} 

	// Other cells, find the column id
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
		FText* CellText = OwningTable->GetCellText(RowDataPtr, ColumnIndex);

		TSharedPtr<SInlineEditableTextBlock> EditableText = SNew(SInlineEditableTextBlock)
			.Text(*CellText)
			.OnTextCommitted(this, &SEditableTableListViewRow::OnCellModified)
			//.HighlightText(DataTableEdit, &FDataTableEditor::GetFilterText)
			.ColorAndOpacity(FSlateColor::UseForeground())
			.OnBeginTextEdit(this, &SEditableTableListViewRow::OnCellEnterEdit);
		
		EditableCells.Add(EditableText, CellText);

		return SNew(SBox)
			.Padding(FMargin(4, 2, 4, 2))
			[
				EditableText.ToSharedRef()
			];
	}

	return SNullWidget::NullWidget;
}

void SEditableTableListViewRow::OnCellEnterEdit(const FText& Text)
{
	// Store the currently edited cell
	for (auto EditableTextCell : EditableCells)
	{
		if (EditableTextCell.Key->IsInEditMode())
		{
			EditedCell = EditableTextCell.Key;
			break;
		}
	}
}

void SEditableTableListViewRow::OnCellModified(const FText& Text, ETextCommit::Type CommitType)
{
	EditedCell->SetText(Text);

	if (EditedCell && EditableCells.Contains(EditedCell))
	{
		*EditableCells[EditedCell] = Text;
	}
}
