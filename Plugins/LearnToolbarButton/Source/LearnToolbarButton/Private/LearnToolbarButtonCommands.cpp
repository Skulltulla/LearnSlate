// Copyright Epic Games, Inc. All Rights Reserved.

#include "LearnToolbarButtonCommands.h"

#define LOCTEXT_NAMESPACE "FLearnToolbarButtonModule"

void FLearnToolbarButtonCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "LearnToolbarButton", "Execute LearnToolbarButton action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
