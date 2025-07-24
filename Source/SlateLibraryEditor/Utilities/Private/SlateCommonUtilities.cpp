#include "../Public/SlateCommonUtilities.h"

TSharedPtr<SWindow> FSlateCommonUtilities::OpenPopupWindow(const FText& WindowTitle,
    TSharedPtr<SWidget> WindowContent,
    ESizingRule SizingRule,
    FVector2D Size)
{
    //Create window
    TSharedPtr<SWindow> Window = SNew(SWindow)
        .Title(FText::FromString(TEXT("Slate Table")))
        .SizingRule(ESizingRule::Autosized)
        .ClientSize(Size)
        .AutoCenter(EAutoCenter::PreferredWorkArea)
        .SupportsMinimize(false)
        .SupportsMaximize(false);

    //Set window content
    Window->SetContent(WindowContent.ToSharedRef());

    //Show window
    GEditor->EditorAddModalWindow(Window.ToSharedRef());

    return Window;
}
