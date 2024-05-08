#include "View/Frame/QuestNodeFrame.h"

#define LOCTEXT_NAMESPACE "NodeBasedQuestModule"

TSharedRef<SDockTab> QuestNodeFrame::CreateTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab).TabRole(PanelTab)[SNew(STextBlock).Text(FText::FromString("Hello, Nodes?"))];
}

FName QuestNodeFrame::GetTabName()
{
	return FName("NBQS_QuestNodes");
}

FText QuestNodeFrame::GetDisplayName()
{
	return LOCTEXT("QuestNodeTab", "Quest Nodes");
}

#undef LOCTEXT_NAMESPACE