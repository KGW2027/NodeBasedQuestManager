// Copyright Epic Games, Inc. All Rights Reserved.

#include "NodeBasedQuestManager.h"
#include "NodeBasedQuestManagerStyle.h"
#include "NodeBasedQuestManagerCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName NodeBasedQuestManagerTabName("NodeBasedQuestManager");

#define LOCTEXT_NAMESPACE "FNodeBasedQuestManagerModule"

void FNodeBasedQuestManagerModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FNodeBasedQuestManagerStyle::Initialize();
	FNodeBasedQuestManagerStyle::ReloadTextures();

	FNodeBasedQuestManagerCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FNodeBasedQuestManagerCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FNodeBasedQuestManagerModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FNodeBasedQuestManagerModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(NodeBasedQuestManagerTabName, FOnSpawnTab::CreateRaw(this, &FNodeBasedQuestManagerModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FNodeBasedQuestManagerTabTitle", "NodeBasedQuestManager"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FNodeBasedQuestManagerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FNodeBasedQuestManagerStyle::Shutdown();

	FNodeBasedQuestManagerCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(NodeBasedQuestManagerTabName);
}

TSharedRef<SDockTab> FNodeBasedQuestManagerModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FNodeBasedQuestManagerModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("NodeBasedQuestManager.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FNodeBasedQuestManagerModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(NodeBasedQuestManagerTabName);
}

void FNodeBasedQuestManagerModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FNodeBasedQuestManagerCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FNodeBasedQuestManagerCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNodeBasedQuestManagerModule, NodeBasedQuestManager)