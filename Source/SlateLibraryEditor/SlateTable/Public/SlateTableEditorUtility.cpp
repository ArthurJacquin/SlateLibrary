#include "../Public/SlateTableEditorUtility.h"
#include "SEditableTable.h"

TSharedRef<SWidget> USlateTableEditorUtility::RebuildWidget()
{
	return SNew(SEditableTable);
}
