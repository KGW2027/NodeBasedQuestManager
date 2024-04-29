// Copyright Epic Games, Inc. All Rights Reserved.

#include "NodeBasedQuestManagerCommands.h"

#define LOCTEXT_NAMESPACE "FNodeBasedQuestManagerModule"

void FNodeBasedQuestManagerCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "NodeBasedQuestManager", "Bring up NodeBasedQuestManager window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
