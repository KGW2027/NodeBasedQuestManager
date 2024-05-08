#include "Control/QuestAssetAction.h"
#include "Control/QuestAssetEditor.h"
#include "Model/QuestAssetInfo.h"

#define LOCTEXT_NAMESPACE "NodeBasedQuestModule"

void FQuestAssetAction::OpenAssetEditor(const TArray<UObject*>& InObjects,
                                        TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	MakeShared<FQuestAssetEditor>()->InitAssetEditorExternal(InObjects);
}

FText FQuestAssetAction::GetName() const
{
	return LOCTEXT("QuestAssetAction", "Quest Info");
}

UClass* FQuestAssetAction::GetSupportedClass() const
{
	return UQuestAssetInfo::StaticClass();
}

FColor FQuestAssetAction::GetTypeColor() const
{
	return FColor::Green;
}

uint32 FQuestAssetAction::GetCategories()
{
	return CatKey;
}

#undef LOCTEXT_NAMESPACE
