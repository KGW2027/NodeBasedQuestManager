#include "Model/QuestAssetInfo.h"

#include "Control/EditorEventListener.h"
#include "Control/QuestAssetEditor.h"
#include "Model/QuestInfo.h"

FName UQuestAssetInfo::CreateNewUniqueId() const
{
	return FName(FString::Printf(TEXT("%d"), QuestInfos.Num() + 1));
}

void UQuestAssetInfo::Add(UQuestInfo* NewQuest)
{
	NewQuest->UniqueId = CreateNewUniqueId();
	QuestInfos.Add(NewQuest);
	FQuestAssetEditor::Listener->OnAddQuest.Broadcast(NewQuest);
}
