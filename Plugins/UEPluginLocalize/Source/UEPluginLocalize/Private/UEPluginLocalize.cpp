// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEPluginLocalize.h"
#include "UEPluginLocalizeStyle.h"
#include "UEPluginLocalizeCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName UEPluginLocalizeTabName("UEPluginLocalize");

#define LOCTEXT_NAMESPACE "FUEPluginLocalizeModule"

void FUEPluginLocalizeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FUEPluginLocalizeStyle::Initialize();
	FUEPluginLocalizeStyle::ReloadTextures();

	FUEPluginLocalizeCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FUEPluginLocalizeCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FUEPluginLocalizeModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FUEPluginLocalizeModule::RegisterMenus));
}

void FUEPluginLocalizeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FUEPluginLocalizeStyle::Shutdown();

	FUEPluginLocalizeCommands::Unregister();
}

void FUEPluginLocalizeModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FUEPluginLocalizeModule::PluginButtonClicked()")),
							FText::FromString(TEXT("UEPluginLocalize.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FUEPluginLocalizeModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FUEPluginLocalizeCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FUEPluginLocalizeCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUEPluginLocalizeModule, UEPluginLocalize)