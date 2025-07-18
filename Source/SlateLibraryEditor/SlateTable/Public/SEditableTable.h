#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "EditableTableData.h"

struct FEditableTableRowListViewData
{
	/** Unique ID used to identify this row */
	FName RowId;

	/** Display name of this row */
	FText DisplayName;

	/** The calculated height of this row taking into account the cell data for each column */
	float DesiredRowHeight;

	/** Insertion number of the row */
	uint32 RowNum;

	/** Array corresponding to each cell in this row */
	UEditableTableData* RowData;
};

struct FEditableTableColumnHeaderData
{
	/** Unique ID used to identify this column */
	FName ColumnId;

	/** Display name of this column */
	FText DisplayName;

	/** The calculated width of this column taking into account the cell data for each row */
	float DesiredColumnWidth;

	/** The FProperty for the variable in this column */
	const FProperty* Property;
};

typedef TSharedPtr<FEditableTableRowListViewData>  FEditableTableRowListViewDataPtr;
typedef TSharedPtr<FEditableTableColumnHeaderData>  FEditableTableColumnHeaderDataPtr;

/**
 * 
 */
class SLATELIBRARYEDITOR_API SEditableTable : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SEditableTable)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	FText GetCellText(FEditableTableRowListViewDataPtr InRowDataPointer, int32 ColumnIndex) const;

	/** Array of the columns that are available for editing */
	TArray<FEditableTableColumnHeaderDataPtr> AvailableColumns;

	/** Array of the rows that are available for editing */
	TArray<FEditableTableRowListViewDataPtr> AvailableRows;

private:
	/** Struct holding information about the current column widths */
	struct FColumnWidth
	{
		FColumnWidth()
			: bIsAutoSized(true)
			, CurrentWidth(0.0f)
		{
		}

		/** True if this column is being auto-sized rather than sized by the user */
		bool bIsAutoSized;
		/** The width of the column, either sized by the user, or auto-sized */
		float CurrentWidth;
	};

	/** Make the widget for a row entry in the data table row list view */
	TSharedRef<ITableRow> MakeRowWidget(FEditableTableRowListViewDataPtr InRowDataPtr, const TSharedRef<STableViewBase>& OwnerTable);

	void CacheColumns();

	void FillTestData();

	float GetColumnWidth(const int32 ColumnIndex) const;

	void OnColumnResized(const float NewWidth, const int32 ColumnIndex);

	EColumnSortMode::Type GetColumnSortMode(const FName ColumnId) const;
	
	void SetDefaultSort();

	void OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode);

	TSharedPtr<SHeaderRow> ColumnNamesHeaderRow;

	/** Widths of data table cell columns */
	TArray<FColumnWidth> ColumnWidths;

	TSharedPtr<SListView<FEditableTableRowListViewDataPtr>> CellsListView;

	/** Currently selected sorting mode */
	EColumnSortMode::Type SortMode;

	/** Specify which column to sort with */
	FName SortByColumn;
};
