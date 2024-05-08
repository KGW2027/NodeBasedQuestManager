#pragma once
#include "QuestInfo.generated.h"

UCLASS()
class NODEBASEDQUESTMANAGER_API UQuestInfo : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FName UniqueId;

	UPROPERTY()
	FString DisplayName;

	UPROPERTY()
	FVector2D Position;
	
};
