// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

/** MODULE Slate Core */
#include "Widgets/SWindow.h"

class FToolBarBuilder;
class FMenuBuilder;

class SMyEmptyWindow : public SWindow
{
public:

	/**
	* Without SLATE_BEGIN_ARGS()/SLATE_END_ARGS(), the properties
	* of SWindow may be specified during object instantiation, i.e:
	*
	*	MyEmptyWindow = SNew(SMyEmptyWindow)
	*		.SupportsMaximize(true);
	*
	* With SLATE_BEGIN_ARGS()/SLATE_END_ARGS(), the properties of
	* SWindow will not appear and must be redeclared and assigned in
	* the Construct() method, i.e.
	*
	*	SWindow::Construct( 
	*		SWindow.FArguments().Title(InArgs._Title)
	*		...
	*
	*/
	SLATE_BEGIN_ARGS(SMyEmptyWindow)
	{ 
		/** Initialize Arguments with Default Values */
		_bMyCustomBoolProperty = false;
		_Title = FText();

		// See TSlateBasedNameArgs for arguments that don't need to be redeclared:
		_AccessibleParams = FAccessibleWidgetData(EAccessibleBehavior::Auto);
	}
		/** Custom Arguments */
		SLATE_ARGUMENT(bool, bMyCustomBoolProperty)

		/** Redeclare inherited arguments and assign in Construct */
		SLATE_ARGUMENT(FText, Title)	// Assigned in Construct: .Title(InArgs._Title)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		//@TODO: Initialize UI Resources

		FAccessibleWidgetData AccessibleParams = FAccessibleWidgetData(EAccessibleBehavior::Auto);

		// NOTE: Without this, the window will appear as a black box 
		SWindow::Construct(
			SWindow::FArguments()
			.ActivationPolicy(EWindowActivationPolicy::Never)
			.SizingRule(ESizingRule::UserSized)
			.Title(InArgs._Title)
			.SupportsMaximize(true)
			.SupportsMinimize(true)
			.SupportsTransparency(EWindowTransparency::None));
	}
};

class FLearnToolbarButtonModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();

public:
	/** Practice Slate Windows Methods */

	// TODO: SWindow as return value

	/**
	* Makes an instance of SWindow using SNew()
	* and assigns it to this->EmptyWindow.
	*/
	void MakeEmptyWindow();

	/**
	*
	*/
	void MakeContentWindow();
	
	/** 
	* Make an instances of SMyEmptyWindow using SNew()
	* and assigns it to this->MyEmptyWindow.
	*/
	void MakeMyEmptyWindow();	
	
private:
	void RegisterMenus();

private:
	TSharedPtr<class FUICommandList> PluginCommands;

private:

	// See MakeEmptyWindow()
	static TSharedPtr<SWindow> EmptyWindow;
	static bool IsEmptyWindowEnabled() { return true; }

	// See MakeContentWindow()
	static TSharedPtr<SWindow> ContentWindow;

	// See MakeMyEmptyWindow()
	static TSharedPtr<SMyEmptyWindow> MyEmptyWindow;
};
