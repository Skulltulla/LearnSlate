// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "LearnDropdownButtonStyle.h"

class FLearnDropdownButtonCommands : public TCommands<FLearnDropdownButtonCommands>
{
public:

	FLearnDropdownButtonCommands()
		: TCommands<FLearnDropdownButtonCommands>(TEXT("LearnDropdownButton"), NSLOCTEXT("Contexts", "LearnDropdownButton", "LearnDropdownButton Plugin"), NAME_None, FLearnDropdownButtonStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
