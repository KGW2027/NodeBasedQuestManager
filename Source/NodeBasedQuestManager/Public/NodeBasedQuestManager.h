// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FQuestAssetAction;
class FToolBarBuilder;
class FMenuBuilder;

class FNodeBasedQuestManagerModule : public IModuleInterface
{
	TSharedPtr<FQuestAssetAction> SharedAssetAction;
	
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
