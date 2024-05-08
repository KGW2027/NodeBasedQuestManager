#include "View/Frame/QuestListFrame.h"

#define LOCTEXT_NAMESPACE "NodeBasedQuestModule"

TSharedRef<SDockTab> QuestListFrame::CreateTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab).TabRole(PanelTab)[SNew(STextBlock).Text(FText::FromString("Hello, World?"))];
}

FName QuestListFrame::GetTabName()
{
	return FName("NBQS_QuestList");
}

FText QuestListFrame::GetDisplayName()
{
	return LOCTEXT("QuestListTab", "Quest List");
}

#undef LOCTEXT_NAMESPACE