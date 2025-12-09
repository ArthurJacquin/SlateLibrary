#include "CustomDetailsActorDetailsCustomization.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "IPropertyUtilities.h"
#include "Actors/CustomDetailsActor.h"

#define LOCTEXT_NAMESPACE "CustomDetailsActorDetailsCustomization"

void FCustomDetailsActorDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
    IDetailCategoryBuilder& CustomCategory = DetailBuilder.EditCategory("CustomSettings");

    CustomCategory.AddProperty(GET_MEMBER_NAME_CHECKED(ACustomDetailsActor, CustomBool));
    CustomCategory.AddProperty(GET_MEMBER_NAME_CHECKED(ACustomDetailsActor, CustomMesh));
    CustomCategory.AddProperty(GET_MEMBER_NAME_CHECKED(ACustomDetailsActor, CustomFloat));

    IDetailCategoryBuilder& SlateCategory = DetailBuilder.EditCategory("Slate");

	// Property style custom row
	FDetailWidgetRow& ButtonRow = SlateCategory.AddCustomRow(LOCTEXT("CustomPropertyRow", "Custom Property Row"))
	.NameContent()
	[
		SNew(STextBlock)
		.Text(LOCTEXT("ButtonRowText", "Button Row"))
	]
	.ValueContent()
	[
		SNew(SButton)
			.Text(LOCTEXT("ButtonText", "Button"))
			.ToolTipText(LOCTEXT("ButtonToolTip", "Button Tooltip"))
			.OnClicked(FOnClicked::CreateLambda([]() 
			{
				UE_LOG(LogTemp, Log, TEXT("Button Pressed!"));
				return FReply::Handled();
			}))
	];

	// Fully custom row
	FDetailWidgetRow& CustomRow = SlateCategory.AddCustomRow(LOCTEXT("CustomRow", "Custom Row"))
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.Padding(5, 0, 5, 0)
			.HAlign(HAlign_Fill)
			[
				SNew(SButton)
				.Text(LOCTEXT("Button1Text", "Button 1"))
				.ToolTipText(LOCTEXT("Button1ToolTip", "Button 1 Tooltip"))
				.OnClicked(FOnClicked::CreateLambda([]()
				{
					UE_LOG(LogTemp, Log, TEXT("Button 1 Pressed!"));
					return FReply::Handled();
				}))
			]

			+ SHorizontalBox::Slot()
			.Padding(5, 0, 5, 0)
			.HAlign(HAlign_Fill)
			[
				SNew(SButton)
				.Text(LOCTEXT("Button2Text", "Button 2"))
				.ToolTipText(LOCTEXT("Button2ToolTip", "Button 2 Tooltip"))
				.OnClicked(FOnClicked::CreateLambda([]()
				{
					UE_LOG(LogTemp, Log, TEXT("Button 2 Pressed!"));
					return FReply::Handled();
				}))
			]
		];
}

TSharedRef<IDetailCustomization> FCustomDetailsActorDetailsCustomization::MakeInstance()
{
    return MakeShareable(new FCustomDetailsActorDetailsCustomization);
}

#undef LOCTEXT_NAMESPACE
