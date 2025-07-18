#include "../Public/SEditableTable.h"

#include "SlateOptMacros.h"
#include "../Public/SEditableTableListViewRow.h"
#include "Fonts/FontMeasure.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SEditableTable::Construct(const FArguments& InArgs)
{
	//Setup data
	FillTestData();
	CacheColumns();

	SetDefaultSort();

	//Create columns widgets
	ColumnNamesHeaderRow = SNew(SHeaderRow);
	for (int32 ColumnIndex = 0; ColumnIndex < AvailableColumns.Num(); ++ColumnIndex)
	{
		const FEditableTableColumnHeaderDataPtr& ColumnData = AvailableColumns[ColumnIndex];

		ColumnNamesHeaderRow->AddColumn(
			SHeaderRow::Column(ColumnData->ColumnId)
			.DefaultLabel(ColumnData->DisplayName)
			.ManualWidth(TAttribute<float>::Create(TAttribute<float>::FGetter::CreateSP(this, &SEditableTable::GetColumnWidth, ColumnIndex)))
			.OnWidthChanged(this, &SEditableTable::OnColumnResized, ColumnIndex)
			.SortMode(this, &SEditableTable::GetColumnSortMode, ColumnData->ColumnId)
			.OnSort(this, &SEditableTable::OnColumnSortModeChanged)
			[
				SNew(SBox)
					.Padding(FMargin(0, 4, 0, 4))
					.VAlign(VAlign_Fill)
					[
						SNew(STextBlock)
							.Justification(ETextJustify::Left)
							.Text(ColumnData->DisplayName)
					]
			]
		);
	}

	//Scroll bars
	TSharedRef<SScrollBar> HorizontalScrollBar = SNew(SScrollBar)
		.Orientation(Orient_Horizontal)
		.Thickness(FVector2D(12.0f, 12.0f));

	TSharedRef<SScrollBar> VerticalScrollBar = SNew(SScrollBar)
		.Orientation(Orient_Vertical)
		.Thickness(FVector2D(12.0f, 12.0f));

	//Rows List View
	CellsListView = SNew(SListView<FEditableTableRowListViewDataPtr>)
		.ListItemsSource(&AvailableRows)
		.HeaderRow(ColumnNamesHeaderRow)
		.OnGenerateRow(this, &SEditableTable::MakeRowWidget)
		.ExternalScrollbar(VerticalScrollBar)
		.ConsumeMouseWheel(EConsumeMouseWheel::Always)
		.SelectionMode(ESelectionMode::Single)
		.AllowOverscroll(EAllowOverscroll::No);

	//Combine everything
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			[
				SNew(SScrollBox)
				.Orientation(Orient_Horizontal)
				.ExternalScrollbar(HorizontalScrollBar)
				+ SScrollBox::Slot()
				[
					CellsListView.ToSharedRef()
				]
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				VerticalScrollBar
			]
		]

		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			[
				HorizontalScrollBar
			]
		]
	];
}

TSharedRef<ITableRow> SEditableTable::MakeRowWidget(FEditableTableRowListViewDataPtr InRowDataPtr, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(SEditableTableListViewRow, OwnerTable)
		.OwningTable(this)
		.RowDataPtr(InRowDataPtr);
}

void SEditableTable::CacheColumns()
{
	// First build array of properties
	UClass* RowClass = UEditableTableData::StaticClass();
	TArray<const FProperty*> StructProps;
	for (TFieldIterator<const FProperty> It(RowClass); It; ++It)
	{
		const FProperty* Prop = *It;
		check(Prop);
		if (!Prop->HasAnyPropertyFlags(CPF_Deprecated))
		{
			StructProps.Add(Prop);
		}
	}

	// Populate the column data
	AvailableColumns.Reset(StructProps.Num());
	for (int32 Index = 0; Index < StructProps.Num(); ++Index)
	{
		const FProperty* Prop = StructProps[Index];
		const FText PropertyDisplayName = FText::FromString(Prop->GetName());

		TSharedRef<FSlateFontMeasure> FontMeasure = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
		const FTextBlockStyle& CellTextStyle = FAppStyle::GetWidgetStyle<FTextBlockStyle>("DataTableEditor.CellText");
		static const float CellPadding = 10.0f;

		FEditableTableColumnHeaderDataPtr CachedColumnData = MakeShareable(new FEditableTableColumnHeaderData());
		CachedColumnData->ColumnId = Prop->GetFName();
		CachedColumnData->DisplayName = PropertyDisplayName;
		CachedColumnData->Property = Prop;

		CachedColumnData->DesiredColumnWidth = static_cast<float>(FontMeasure->Measure(CachedColumnData->DisplayName, CellTextStyle.Font).X + CellPadding);

		AvailableColumns.Add(CachedColumnData);
	}

	// Setup the default auto-sized columns
	ColumnWidths.SetNum(AvailableColumns.Num());
	for (int32 ColumnIndex = 0; ColumnIndex < AvailableColumns.Num(); ++ColumnIndex)
	{
		const FEditableTableColumnHeaderDataPtr& ColumnData = AvailableColumns[ColumnIndex];
		FColumnWidth& ColumnWidth = ColumnWidths[ColumnIndex];
		ColumnWidth.CurrentWidth = FMath::Clamp(ColumnData->DesiredColumnWidth, 10.0f, 400.0f); // Clamp auto-sized columns to a reasonable limit
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SEditableTable::FillTestData()
{
	UEditableTableData* Dog = NewObject<UEditableTableData>();
	Dog->Animal = "Dog";
	Dog->Color = "White";
	Dog->Age = "10";

	UEditableTableData* Cat = NewObject<UEditableTableData>();
	Cat->Animal = "Cat";
	Cat->Color = "Black";
	Cat->Age = "5";

	UEditableTableData* Bunny = NewObject<UEditableTableData>();
	Bunny->Animal = "Bunny";
	Bunny->Color = "Grey";
	Bunny->Age = "8";

	FEditableTableRowListViewDataPtr DataDog = MakeShareable(new FEditableTableRowListViewData());
	DataDog->RowId = FName(FString::FromInt(0));
	DataDog->DisplayName = FText::FromString("Row 0");
	DataDog->RowNum = 0;
	DataDog->DesiredRowHeight = 30;
	DataDog->RowData = Dog;

	FEditableTableRowListViewDataPtr DataCat = MakeShareable(new FEditableTableRowListViewData());
	DataCat->RowId = FName(FString::FromInt(1));
	DataCat->DisplayName = FText::FromString("Row 1");
	DataCat->RowNum = 1;
	DataCat->DesiredRowHeight = 30;
	DataCat->RowData = Cat;

	FEditableTableRowListViewDataPtr DataBunny = MakeShareable(new FEditableTableRowListViewData());
	DataBunny->RowId = FName(FString::FromInt(2));
	DataBunny->DisplayName = FText::FromString("Row 2");
	DataBunny->RowNum = 2;
	DataBunny->DesiredRowHeight = 30;
	DataBunny->RowData = Bunny;

	AvailableRows.Add(DataDog);
	AvailableRows.Add(DataCat);
	AvailableRows.Add(DataBunny);
}

float SEditableTable::GetColumnWidth(const int32 ColumnIndex) const
{
	if (ColumnWidths.IsValidIndex(ColumnIndex))
	{
		return ColumnWidths[ColumnIndex].CurrentWidth;
	}

	return 0.0f;
}

void SEditableTable::OnColumnResized(const float NewWidth, const int32 ColumnIndex)
{
	if (ColumnWidths.IsValidIndex(ColumnIndex))
	{
		ColumnWidths[ColumnIndex].CurrentWidth = NewWidth;
	}
}

EColumnSortMode::Type SEditableTable::GetColumnSortMode(const FName ColumnId) const
{
	if (SortByColumn != ColumnId)
	{
		return EColumnSortMode::None;
	}

	return SortMode;
}

void SEditableTable::SetDefaultSort()
{
	SortMode = EColumnSortMode::Ascending;
	SortByColumn = AvailableColumns.IsEmpty() ? "" : AvailableColumns[0]->ColumnId;
}

void SEditableTable::OnColumnSortModeChanged(const EColumnSortPriority::Type SortPriority, const FName& ColumnId, const EColumnSortMode::Type InSortMode)
{
	int32 ColumnIndex;

	SortMode = InSortMode;
	SortByColumn = ColumnId;

	for (ColumnIndex = 0; ColumnIndex < AvailableColumns.Num(); ++ColumnIndex)
	{
		if (AvailableColumns[ColumnIndex]->ColumnId == ColumnId)
		{
			break;
		}
	}

	if (AvailableColumns.IsValidIndex(ColumnIndex))
	{
		if (InSortMode == EColumnSortMode::Ascending)
		{
			AvailableRows.Sort([this, ColumnIndex](const FEditableTableRowListViewDataPtr& first, const FEditableTableRowListViewDataPtr& second)
				{
					FText FirstText = GetCellText(first, ColumnIndex);
					FText SecondText = GetCellText(second, ColumnIndex);

					int32 Result = FirstText.ToString().Compare(FirstText.ToString());

					if (!Result)
					{
						return first->RowNum < second->RowNum;

					}

					return Result < 0;
				});

		}
		else if (InSortMode == EColumnSortMode::Descending)
		{
			AvailableRows.Sort([this, ColumnIndex](const FEditableTableRowListViewDataPtr& first, const FEditableTableRowListViewDataPtr& second)
				{
					FText FirstText = GetCellText(first, ColumnIndex);
					FText SecondText = GetCellText(second, ColumnIndex);

					int32 Result = FirstText.ToString().Compare(FirstText.ToString());

					if (!Result)
					{
						return first->RowNum > second->RowNum;
					}

					return Result > 0;
				});
		}
	}

	CellsListView->RequestListRefresh();
}

FText SEditableTable::GetCellText(FEditableTableRowListViewDataPtr InRowDataPointer, int32 ColumnIndex) const
{
	if (!AvailableColumns.IsValidIndex(ColumnIndex))
	{
		return FText::GetEmpty();
	}

	const FProperty* Property = AvailableColumns[ColumnIndex]->Property;

	//String property
	if (FString* StringValue = Property->ContainerPtrToValuePtr<FString>(InRowDataPointer->RowData))
	{
		return FText::FromString(*StringValue);
	}

	return FText::GetEmpty();
}
