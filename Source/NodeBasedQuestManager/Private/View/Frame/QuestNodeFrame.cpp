#include "View/Frame/QuestNodeFrame.h"

#include "View/Panel/QuestNodeGraphPanel.h"

#define LOCTEXT_NAMESPACE "NodeBasedQuestModule"

TSharedRef<SDockTab> QuestNodeFrame::CreateTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab).TabRole(PanelTab)
		[
			SNew(SQuestNodeGraphPanel)
		];
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