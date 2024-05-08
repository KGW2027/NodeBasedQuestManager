#pragma once
#include "QuestAssetCache.generated.h"

USTRUCT()
struct NODEBASEDQUESTMANAGER_API FQuestAssetCache
{
	GENERATED_BODY();
	
	UPROPERTY()
	FVector2D LastOffset;

	UPROPERTY()
	FName LastSelectedId;
	
};
