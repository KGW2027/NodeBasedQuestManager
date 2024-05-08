#include "Control/QuestAssetFactory.h"

#include "Model/QuestAssetInfo.h"

UQuestAssetFactory::UQuestAssetFactory()
{
	SupportedClass = UQuestAssetInfo::StaticClass();
	bCreateNew = true;
}

UObject* UQuestAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	return NewObject<UQuestAssetInfo>(InParent, InClass, InName, Flags, Context);
}
