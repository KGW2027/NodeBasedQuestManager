#include "View/Frame/QuestPropertyFrame.h"

#define LOCTEXT_NAMESPACE "NodeBasedQuestModule"

TSharedRef<SDockTab> QuestPropertyFrame::CreateTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab).TabRole(PanelTab)[SNew(STextBlock).Text(FText::FromString("Hello, Properties?"))];
}

FName QuestPropertyFrame::GetTabName()
{
	return FName("NBQS_QuestProperties");
}

FText QuestPropertyFrame::GetDisplayName()
{
	return LOCTEXT("QuestPropertyTab", "Quest Property Editor");
}

#undef LOCTEXT_NAMESPACE