// Copyright Epic Games, Inc. All Rights Reserved.

#include "LearnDropdownButtonCommands.h"

#define LOCTEXT_NAMESPACE "FLearnDropdownButtonModule"

void FLearnDropdownButtonCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "LearnDropdownButton", "Execute LearnDropdownButton action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
