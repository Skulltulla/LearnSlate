// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "LearnToolbarButtonStyle.h"

class FLearnToolbarButtonCommands : public TCommands<FLearnToolbarButtonCommands>
{
public:

	FLearnToolbarButtonCommands()
		: TCommands<FLearnToolbarButtonCommands>(TEXT("LearnToolbarButton"), NSLOCTEXT("Contexts", "LearnToolbarButton", "LearnToolbarButton Plugin"), NAME_None, FLearnToolbarButtonStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
