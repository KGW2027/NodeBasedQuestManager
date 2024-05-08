#pragma once

class QuestNodeFrame
{
public:
	static TSharedRef<SDockTab> CreateTab(const FSpawnTabArgs& SpawnTabArgs);
	static FName GetTabName();
	static FText GetDisplayName();
};
