// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "NodeBasedQuestManagerStyle.h"

class FNodeBasedQuestManagerCommands : public TCommands<FNodeBasedQuestManagerCommands>
{
public:

	FNodeBasedQuestManagerCommands()
		: TCommands<FNodeBasedQuestManagerCommands>(TEXT("NodeBasedQuestManager"), NSLOCTEXT("Contexts", "NodeBasedQuestManager", "NodeBasedQuestManager Plugin"), NAME_None, FNodeBasedQuestManagerStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};