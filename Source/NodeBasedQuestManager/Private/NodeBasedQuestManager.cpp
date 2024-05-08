// Copyright Epic Games, Inc. All Rights Reserved.

#include "NodeBasedQuestManager.h"

#include "AssetToolsModule.h"
#include "Control/QuestAssetAction.h"

#define LOCTEXT_NAMESPACE "NodeBasedQuestModule"

FName NodeBasedQuestCategoryKey("NodeBasedQuest");

void FNodeBasedQuestManagerModule::StartupModule()
{
	IAssetTools& ATModule = FAssetToolsModule::GetModule().Get();
	uint32 CatKey = ATModule.RegisterAdvancedAssetCategory(NodeBasedQuestCategoryKey, LOCTEXT("NodeBasedQuest_Category", "NodeBasedQuest"));
	SharedAssetAction = MakeShared<FQuestAssetAction>(CatKey);
	ATModule.RegisterAssetTypeActions(SharedAssetAction.ToSharedRef());
}

void FNodeBasedQuestManagerModule::ShutdownModule()
{
	if(!FModuleManager::Get().IsModuleLoaded("AssetTools")) return;
	FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(SharedAssetAction.ToSharedRef());
}
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNodeBasedQuestManagerModule, NodeBasedQuestManager)