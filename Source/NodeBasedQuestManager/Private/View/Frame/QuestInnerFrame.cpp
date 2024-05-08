#include "View/Frame/QuestInnerFrame.h"

#define LOCTEXT_NAMESPACE "NodeBasedQuestModule"

TSharedRef<SDockTab> QuestInnerFrame::CreateTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab).TabRole(PanelTab)[SNew(STextBlock).Text(FText::FromString("Hello, Inner?"))];
}

FName QuestInnerFrame::GetTabName()
{
	return FName("NBQS_QuestInnerEditor");
}

FText QuestInnerFrame::GetDisplayName()
{
	return LOCTEXT("QuestInnerTab", "Quest Inner Node Editor");
}

#undef LOCTEXT_NAMESPACE