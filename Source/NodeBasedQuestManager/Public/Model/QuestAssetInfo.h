#pragma once
#include "QuestAssetCache.h"
#include "QuestAssetInfo.generated.h"

UCLASS()
class NODEBASEDQUESTMANAGER_API UQuestAssetInfo : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<class UQuestInfo*> QuestInfos;

	UPROPERTY()
	FQuestAssetCache QuestCache;
	
};
