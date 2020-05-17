// Copyright Epic Games, Inc. All Rights Reserved.

#include "LearnDropdownButton.h"
#include "LearnDropdownButtonStyle.h"
#include "LearnDropdownButtonCommands.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "ToolMenus.h"

#include "LevelEditor.h"

static const FName LearnDropdownButtonTabName("LearnDropdownButton");

#define LOCTEXT_NAMESPACE "FLearnDropdownButtonModule"

void FLearnDropdownButtonModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FLearnDropdownButtonStyle::Initialize();
	FLearnDropdownButtonStyle::ReloadTextures();

	FLearnDropdownButtonCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FLearnDropdownButtonCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FLearnDropdownButtonModule::PluginButtonClicked),
		FCanExecuteAction());

	// The LevelEditorModule allows us to add Menu and Toolbar Extensions
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FLearnDropdownButtonModule::AddToolbarExtension));
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FLearnDropdownButtonModule::RegisterMenus));
}

void FLearnDropdownButtonModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);

	FLearnDropdownButtonStyle::Shutdown();

	FLearnDropdownButtonCommands::Unregister();
}

void FLearnDropdownButtonModule::PluginButtonClicked()
{
}

void FLearnDropdownButtonModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FLearnDropdownButtonCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FLearnDropdownButtonCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

void FLearnDropdownButtonModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.BeginSection("LearnSlate"); // make an editor extension point 
	{
		Builder.AddComboButton(
			FUIAction(),  // no action (don't do anything when the dropdown button is clicked)
			FOnGetContent::CreateStatic(&FLearnDropdownButtonModule::GenerateToolbarButton, PluginCommands.ToSharedRef()),
			NSLOCTEXT("NS_DROPDOWN_BUTTON", "LearnToolbarMenu_Label", "LearnDropdown"), // what you see below the toolbar button
			NSLOCTEXT("NS_DROPDOWN_BUTTON", "LearnToolbarMenu_Tooltip", "A dropdown button."),
			FSlateIcon(FLearnDropdownButtonStyle::GetStyleSetName(), "LearnDropdownButton.DropdownButtonIcon")
			// false,		// bInSimpleComboBox
			// NAME_None	// InTutorialHighlightName
		);
	}
	Builder.EndSection();

	// The original button generated
	// Builder.AddToolBarButton(FLearnDropdownButtonCommnads::Get().PluginAction);
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLearnDropdownButtonModule, LearnDropdownButton)