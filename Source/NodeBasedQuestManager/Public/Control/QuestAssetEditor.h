#pragma once
#include "Model/QuestAssetInfo.h"

class FEditorEventListener;

class FQuestAssetEditor : public FAssetEditorToolkit
{
public:
	static TSharedPtr<FEditorEventListener> Listener;
	static float ZoomMultiplier;
	
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	void InitAssetEditorExternal(const TArray<UObject*>& Args);

private:
	static void OnChangedZoomMultiplier(float Delta);
	void OnKeyDown(SWidget* Widget, FKey Key, bool IsCtrlDown, bool IsAltDown, bool IsShiftDown);
	
	UQuestAssetInfo* Quests = nullptr;
	
};
