// Copyright Epic Games, Inc. All Rights Reserved.

#include "LearnToolbarButton.h"
#include "LearnToolbarButtonStyle.h"
#include "LearnToolbarButtonCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

// STATIC VARIABLE DEFINITION
TSharedPtr<SWindow> FLearnToolbarButtonModule::EmptyWindow;
TSharedPtr<SWindow> FLearnToolbarButtonModule::ContentWindow;
TSharedPtr<SMyEmptyWindow> FLearnToolbarButtonModule::MyEmptyWindow;

// GLOBAL VARIABLES
static const FName LearnToolbarButtonTabName("LearnToolbarButton");

// TEXT LOCALIZATION
#define LOCTEXT_NAMESPACE "FLearnToolbarButtonModule"

void FLearnToolbarButtonModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FLearnToolbarButtonStyle::Initialize();
	FLearnToolbarButtonStyle::ReloadTextures();

	FLearnToolbarButtonCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FLearnToolbarButtonCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FLearnToolbarButtonModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FLearnToolbarButtonModule::RegisterMenus));
}

void FLearnToolbarButtonModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FLearnToolbarButtonStyle::Shutdown();

	FLearnToolbarButtonCommands::Unregister();
}

void FLearnToolbarButtonModule::PluginButtonClicked()
{
	/*
	FText DialogText = FText::Format( LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"), FText::FromString(TEXT("FLearnToolbarButtonModule::PluginButtonClicked()")), FText::FromString(TEXT("LearnToolbarButton.cpp")) );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
	*/

	// MakeEmptyWindow();
	MakeMyEmptyWindow();
	// MakeContentWindow();
}

void FLearnToolbarButtonModule::MakeEmptyWindow()
{
	if (EmptyWindow.IsValid())
	{
		FSlateApplication::Get().DestroyWindowImmediately(EmptyWindow.ToSharedRef());
	}

	FAccessibleWidgetData AccessibleParams = FAccessibleWidgetData(EAccessibleBehavior::Auto);

	// NOTE: Goto line 137 in SWindow.h to see default values
	EmptyWindow = SNew(SWindow)
		.AccessibleParams(AccessibleParams)
		.ActivationPolicy(EWindowActivationPolicy::Always) // NOTE: ActivateWhenFirstShown() - Deprecated since 4.16
		//@TODO .Cursor( EMouseCursor::GrabHand ) // NOTE: This didn't change the cursor; probably needs content
		.IsEnabled_Static(&FLearnToolbarButtonModule::IsEmptyWindowEnabled)
		//@TODO .IsEnabled_Lambda()
		// .IsPopupWindow(false) // WARNING: setting this to true resulted in it being a black box
		.MaxHeight(640.f)
		.MaxWidth(480.f)
		.MinHeight(180.f)
		.MinWidth(180.f)
		.ShouldPreserveAspectRatio(false)
		.SizingRule(ESizingRule::UserSized)
		.Title(NSLOCTEXT("NS_SLATE_WINDOWS", "EmptyWindowKey", "Empty Window"))
		.Type(EWindowType::Normal);
		// .Visibility(EVisibility::All); // WARNING: "EVisibility::Visible" crashes the editor here
	EmptyWindow->Resize(FVector2D(640, 480)); // NOTE: Call this or else the MinHeight and MinWidth will be used
	FSlateApplication::Get().AddWindow(EmptyWindow.ToSharedRef());
}

void FLearnToolbarButtonModule::MakeContentWindow()
{
	if (ContentWindow.IsValid())
	{
		FSlateApplication::Get().DestroyWindowImmediately(ContentWindow.ToSharedRef());
	}

	FAccessibleWidgetData AccessibleParams = FAccessibleWidgetData(EAccessibleBehavior::Auto);

	ContentWindow = SNew(SWindow)
		.AccessibleParams(AccessibleParams)
		.ActivationPolicy(EWindowActivationPolicy::Always) 
		.IsEnabled_Static(&FLearnToolbarButtonModule::IsEmptyWindowEnabled)
		.MinHeight(320.f)
		.MinWidth(240.f)
		.ShouldPreserveAspectRatio(false)
		.SizingRule(ESizingRule::UserSized)
		.Title(NSLOCTEXT("NS_SLATE_WINDOWS", "ContentWindowKey", "Content Window"))
		.Type(EWindowType::Normal);

	TSharedRef<SBorder> RootBorder = SNew(SBorder)
		.HAlign( EHorizontalAlignment::HAlign_Fill )
		.VAlign( EVerticalAlignment::VAlign_Fill )
		.Padding(8)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign( EHorizontalAlignment::HAlign_Left )
			.Padding(2)
			[
				SNew(STextBlock)
				.AutoWrapText(true)
				.Text(NSLOCTEXT("NS_NONE", "ContentWindowSectionTitleKey", "Content Window Section"))
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign( EHorizontalAlignment::HAlign_Left )
			.Padding(2)
			[
				SNew(STextBlock)
				.AutoWrapText(true)
				.Text(NSLOCTEXT("NS_NONE", "ContentWindowSection2TitleKey", "Content Window Section 2"))
			]
		];
	ContentWindow->SetContent(RootBorder);

	ContentWindow->Resize(FVector2D(640, 480)); 
	FSlateApplication::Get().AddWindow(ContentWindow.ToSharedRef());
}

void FLearnToolbarButtonModule::MakeMyEmptyWindow()
{
	if (MyEmptyWindow.IsValid())
	{
		FSlateApplication::Get().DestroyWindowImmediately(MyEmptyWindow.ToSharedRef());
	}

	MyEmptyWindow = SNew(SMyEmptyWindow)
		.Title(NSLOCTEXT("NS_SLATE_WINDOWS", "MyEmptyWindowKey", "My Empty Window"));
	MyEmptyWindow->Resize(FVector2D(640, 480));
	FSlateApplication::Get().AddWindow(MyEmptyWindow.ToSharedRef());
}

void FLearnToolbarButtonModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FLearnToolbarButtonCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FLearnToolbarButtonCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLearnToolbarButtonModule, LearnToolbarButton)