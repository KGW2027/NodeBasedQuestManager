#pragma once
#include "Model/QuestAssetInfo.h"

// ZoomMultiplierChanged (float ZoomChangedValue)
DECLARE_MULTICAST_DELEGATE_OneParam(ZoomMultiplierChanged, float)
// KeyDown (SWidget self, FKey Key, bool IsCtrlDown, bool IsAltDown, bool IsShiftDown)
DECLARE_MULTICAST_DELEGATE_FiveParams(KeyDown, SWidget*, FKey, bool, bool, bool)
// AdDQuest (UQuestAssetInfo QuestInfo)
DECLARE_MULTICAST_DELEGATE_OneParam(AddQuest, UQuestInfo*)

class FEditorEventListener
{
public:
	ZoomMultiplierChanged OnZoomMultiplierChanged;
	KeyDown OnKeyDown;
	AddQuest OnAddQuest;
	
	
};
