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

	// SLATE_BEGIN_ARGS(SMyEmptyWindow)
	// 	: _SupportsMaximize(true)
	// {
	// }
	// SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		UE_LOG(LogTemp, Log, TEXT("SEmptyWindow Args:"), *InArgs._Title.Get().ToString());

		// NOTE: Without this, the window will appear as a black box and cannot be closed.
		SWindow::Construct(InArgs);
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

	/**
	* Makes an instance of SWindow using SNew()
	* and assigns it to this->EmptyWindow.
	*/
	void MakeEmptyWindow();
	
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

	// See MakeMyEmptyWindow()
	static TSharedPtr<SMyEmptyWindow> MyEmptyWindow;
};
