#pragma once
#include "QuestAssetFactory.generated.h"

UCLASS()
class NODEBASEDQUESTMANAGER_API UQuestAssetFactory : public UFactory
{
	GENERATED_BODY()
public:

	UQuestAssetFactory();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;
	
};
