#include "NewCustomEditorModeStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateStyleMacros.h"
#include "Styling/CoreStyle.h"

#define RootToContentDir StyleSet->RootToContentDir

TSharedPtr<FSlateStyleSet> FNewCustomEditorModeStyle::StyleSet = nullptr;

void FNewCustomEditorModeStyle::Initialize()
{
	// Only register once
	if (StyleSet.IsValid())
	{
		return;
	}

	const FVector2D Icon20x20(20.0f, 20.0f);

	StyleSet = MakeShareable(new FSlateStyleSet(GetStyleSetName()));

	// If we get asked for something that we don't set, we should default to editor style
	StyleSet->SetParentStyleName("EditorStyle");

	FString Path = FPaths::ProjectContentDir() / TEXT("Slate/NewCustomEditorModeStyle");
	StyleSet->SetContentRoot(FPaths::ProjectContentDir() / TEXT("Slate/NewCustomEditorModeStyle"));
	StyleSet->SetCoreContentRoot(FPaths::EngineContentDir() / TEXT("Slate"));

	// NOTE: The style names follow the following: "CommandSetName.CommandName"
	// NewCustomEditorMode is the name of the commands set defined with TCommands(Name, Desc, Parent, StyleSet)
	// CommandName is the name of the command created in your command class

	// NOTE: Use IMAGE_BRUSH_SVG for SVG and IMAGE_BRUSH for PNG/JPG
	
	// Selection Tab styles
	{
		StyleSet->Set("NewCustomEditorModeCommands.LoadSelectionTab", new IMAGE_BRUSH_SVG("SelectionTab_16x", Icon20x20));
		StyleSet->Set("NewCustomEditorModeCommands.Selection_EnableSelection", new IMAGE_BRUSH_SVG("SelectionTab_16x", Icon20x20));
		StyleSet->Set("NewCustomEditorModeCommands.Selection_DisableSelection", new IMAGE_BRUSH_SVG("SelectionTab_16x", Icon20x20));
	}

	// Place Tab styles
	{
		StyleSet->Set("NewCustomEditorModeCommands.LoadPlaceTab", new IMAGE_BRUSH_SVG("PlaceActors_16x", Icon20x20));
		StyleSet->Set("NewCustomEditorModeCommands.Place_Cube", new IMAGE_BRUSH("PlaceCube_20x", Icon20x20));
		StyleSet->Set("NewCustomEditorModeCommands.Place_Sphere", new IMAGE_BRUSH("PlaceSphere_16x", Icon20x20));
	}

	// Register style set
	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

void FNewCustomEditorModeStyle::Shutdown()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
		ensure(StyleSet.IsUnique());
		StyleSet.Reset();
	}
}

TSharedPtr<class ISlateStyle> FNewCustomEditorModeStyle::Get()
{
	return StyleSet;
}

FName FNewCustomEditorModeStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("NewCustomEditorModeStyle"));
	return StyleSetName;
}

const FSlateBrush* FNewCustomEditorModeStyle::GetBrush(FName PropertyName, const ANSICHAR* Specifier /*= NULL*/)
{
	return Get()->GetBrush(PropertyName, Specifier);
}

FString FNewCustomEditorModeStyle::InContent(const FString& RelativePath, const ANSICHAR* Extension)
{
	static FString ContentDir = FPaths::ProjectContentDir() / TEXT("Slate/NewCustomEditorModeStyle");
	return (ContentDir / RelativePath) + Extension;
}
