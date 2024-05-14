#include "Control/QuestAssetEditor.h"

#include "Control/EditorEventListener.h"
#include "Model/QuestInfo.h"
#include "View/Frame/QuestInnerFrame.h"
#include "View/Frame/QuestListFrame.h"
#include "View/Frame/QuestNodeFrame.h"
#include "View/Frame/QuestPropertyFrame.h"
#include "View/Panel/QuestNodeGraphPanel.h"


#define LOCTEXT_NAMESPACE "NodeBasedQuestModule"
TSharedPtr<FEditorEventListener> FQuestAssetEditor::Listener = MakeShared<FEditorEventListener>();
float FQuestAssetEditor::ZoomMultiplier = 1.0;
FName QuestAssetEditorIdentifier("NodeBasedQuestEditor");

#pragma region Default Override Functions
FName FQuestAssetEditor::GetToolkitFName() const
{
	return FName(QuestAssetEditorIdentifier.ToString() + "_Toolkit");
}
FText FQuestAssetEditor::GetBaseToolkitName() const
{
	return LOCTEXT("ToolkitName", "NodeBasedQuestToolkit");
}
FString FQuestAssetEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "NBQTab").ToString();
}
FLinearColor FQuestAssetEditor::GetWorldCentricTabColorScale() const
{
	return FColor::Green;
}
#pragma endregion 

#pragma region Asset Editor Functions
void FQuestAssetEditor::InitAssetEditorExternal(const TArray<UObject*>& Args)
{
	// Args Initialize
	check(Args.Num() > 0 && Args[0]->IsA(UQuestAssetInfo::StaticClass()));
	Quests = static_cast<UQuestAssetInfo*>(Args[0]);

	// Layout Initialize
	FName LayoutKey = FName(QuestAssetEditorIdentifier.ToString() + "_Layout");
	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout(LayoutKey)
	->AddArea
	(
		FTabManager::NewPrimaryArea()
		->SetOrientation(Orient_Horizontal)
		->Split
		(
			FTabManager::NewSplitter()
			->SetSizeCoefficient(0.15f)
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack() // QuestList
				->SetSizeCoefficient(0.4f)
				->AddTab(QuestListFrame::GetTabName(), ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewStack() // Property Editor
				->SetSizeCoefficient(0.6f)
				->AddTab(QuestPropertyFrame::GetTabName(), ETabState::OpenedTab)
			)
		)
		->Split
		(
			FTabManager::NewStack() // QuestNodes
			->SetSizeCoefficient(0.5f)
			->AddTab(QuestNodeFrame::GetTabName(), ETabState::OpenedTab)
		)
		->Split
		(
			FTabManager::NewStack() // Quest Inner Editor
			->SetSizeCoefficient(0.35f)
			->AddTab(QuestInnerFrame::GetTabName(), ETabState::OpenedTab)
		)
	);
	AddToolbarWidget(
		SNew(SButton)
		.Text(FText::FromString("Set Layout to Default"))
		.ToolTipText(FText::FromString("Click this button if the layout did not load properly and re-open this widget."))
		.OnClicked_Lambda([this, Layout]
		{
			FLayoutSaveRestore::SaveToConfig(GEditorLayoutIni, Layout);
			FUnrealEdMisc::Get().AllowSavingLayoutOnClose(false);
			CloseWindow(EAssetEditorCloseReason::AssetForceDeleted);
			return FReply::Handled();
		})
	);
	InitAssetEditor(EToolkitMode::Standalone, {}, QuestAssetEditorIdentifier, Layout, false, true, Args);
	FUnrealEdMisc::Get().AllowSavingLayoutOnClose(true);

	Listener->OnZoomMultiplierChanged.AddStatic(&FQuestAssetEditor::OnChangedZoomMultiplier);
	Listener->OnKeyDown.AddRaw(this, &FQuestAssetEditor::OnKeyDown);
}

void FQuestAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& _TabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(_TabManager);
	WorkspaceMenuCategory = _TabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_QuestEditor", "Quest Asset Category"));

	_TabManager->RegisterTabSpawner(QuestInnerFrame::GetTabName(), FOnSpawnTab::CreateStatic(&QuestInnerFrame::CreateTab))
	.SetDisplayName(QuestInnerFrame::GetDisplayName())
	.SetGroup(WorkspaceMenuCategory.ToSharedRef());
	
	_TabManager->RegisterTabSpawner(QuestListFrame::GetTabName(), FOnSpawnTab::CreateStatic(&QuestListFrame::CreateTab))
	.SetDisplayName(QuestListFrame::GetDisplayName())
	.SetGroup(WorkspaceMenuCategory.ToSharedRef());
	
	_TabManager->RegisterTabSpawner(QuestNodeFrame::GetTabName(), FOnSpawnTab::CreateStatic(&QuestNodeFrame::CreateTab))
	.SetDisplayName(QuestNodeFrame::GetDisplayName())
	.SetGroup(WorkspaceMenuCategory.ToSharedRef());
	
	_TabManager->RegisterTabSpawner(QuestPropertyFrame::GetTabName(), FOnSpawnTab::CreateStatic(&QuestPropertyFrame::CreateTab))
	.SetDisplayName(QuestPropertyFrame::GetDisplayName())
	.SetGroup(WorkspaceMenuCategory.ToSharedRef());

}
void FQuestAssetEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& _TabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(_TabManager);
	
	_TabManager->UnregisterTabSpawner(QuestInnerFrame::GetTabName());
	_TabManager->UnregisterTabSpawner(QuestListFrame::GetTabName());
	_TabManager->UnregisterTabSpawner(QuestNodeFrame::GetTabName());
	_TabManager->UnregisterTabSpawner(QuestPropertyFrame::GetTabName());
}
#pragma endregion

#pragma region EventListener
void FQuestAssetEditor::OnChangedZoomMultiplier(float Delta)
{
	ZoomMultiplier = FMath::Clamp(ZoomMultiplier + Delta / 10, 0.5, 2.0);
}

void FQuestAssetEditor::OnKeyDown(SWidget* Widget, FKey Key, bool IsCtrlDown, bool IsAltDown, bool IsShiftDown)
{
	if(static_cast<SQuestNodeGraphPanel*>(Widget))
	{
		if(Key == EKeys::A)
		{
			UQuestInfo* NewQuest = NewObject<UQuestInfo>();
			NewQuest->DisplayName = "How to use a Sword?";
			NewQuest->Position = FVector2D(0, 0);
			Quests->Add(NewQuest);
		}
	}
	
}
#pragma endregion

#undef LOCTEXT_NAMESPACE