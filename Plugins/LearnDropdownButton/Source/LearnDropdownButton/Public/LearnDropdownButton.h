// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"					// FModuleManager

#include "Framework/Commands/UICommandList.h"		// FUICommandList
#include "Framework/MultiBox/MultiBoxBuilder.h"		// FMenuBuilder 
#include "Widgets/SWidget.h"						// SWidget

#include "LearnDropdownButtonCommands.h"

class FToolBarBuilder;
class FMenuBuilder;

class FLearnDropdownButtonModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();
	
private:
	void RegisterMenus();

	void AddToolbarExtension(FToolBarBuilder& Builder);

private:
	static TSharedRef<SWidget> GenerateToolbarButton(TSharedRef<FUICommandList> InCommandList)
	{
		const bool bShouldCloseWindowAfterMenuSelection = false;
		FMenuBuilder MenuBuilder(bShouldCloseWindowAfterMenuSelection, InCommandList);
		{
			MenuBuilder.AddMenuEntry(FLearnDropdownButtonCommands::Get().PluginAction);

			MenuBuilder.AddSubMenu(
				NSLOCTEXT("NS_DROPDOWN_BUTTON", "MenuKey", "MenuValue"),
				NSLOCTEXT("NS_DROPDOWN_BUTTON", "TooltipKey", "TooltipValue"),
				FNewMenuDelegate::CreateStatic(&FLearnDropdownButtonModule::MakeGenericSubmenu)
				// FUIAction(),
				// NAME_None,
				// EUserInterfaceActionType::None
			);
		}
		return MenuBuilder.MakeWidget();
	}

	static void MakeGenericSubmenu(FMenuBuilder& MenuBuilder)
	{
		MenuBuilder.AddMenuEntry(FLearnDropdownButtonCommands::Get().PluginAction);
		MenuBuilder.AddMenuSeparator(FName(TEXT("MySeperator"))); // a hor. line (no text)
		MenuBuilder.AddMenuEntry(FLearnDropdownButtonCommands::Get().PluginAction);
	}

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
