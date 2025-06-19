// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEPluginLocalizeCommands.h"

#define LOCTEXT_NAMESPACE "FUEPluginLocalizeModule"

void FUEPluginLocalizeCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "UEPluginLocalize", "Execute UEPluginLocalize action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
