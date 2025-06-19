// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"
#include "UEPluginLocalizeStyle.h"

class FUEPluginLocalizeCommands : public TCommands<FUEPluginLocalizeCommands>
{
public:

	FUEPluginLocalizeCommands()
		: TCommands<FUEPluginLocalizeCommands>(TEXT("UEPluginLocalize"), NSLOCTEXT("Contexts", "UEPluginLocalize", "UEPluginLocalize Plugin"), NAME_None, FUEPluginLocalizeStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
