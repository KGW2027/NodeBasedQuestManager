#pragma once

DECLARE_MULTICAST_DELEGATE_OneParam(ZoomMultiplierChanged, float)

class EditorEventListener
{
public:
	ZoomMultiplierChanged OnZoomMultiplierChanged;
	
	
};
