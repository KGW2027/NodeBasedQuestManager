#pragma once
#include "AssetTypeActions_Base.h"

class FQuestAssetAction : public FAssetTypeActions_Base
{
public:
	FQuestAssetAction(const uint32 CategoryKey) : CatKey(CategoryKey) {}
	
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;
	virtual FText GetName() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;
	
private:
	uint32 CatKey;
};
