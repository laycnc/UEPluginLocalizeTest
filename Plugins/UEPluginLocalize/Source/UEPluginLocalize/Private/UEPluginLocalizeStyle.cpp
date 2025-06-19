// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEPluginLocalizeStyle.h"
#include "UEPluginLocalize.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FUEPluginLocalizeStyle::StyleInstance = nullptr;

void FUEPluginLocalizeStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FUEPluginLocalizeStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FUEPluginLocalizeStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("UEPluginLocalizeStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FUEPluginLocalizeStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("UEPluginLocalizeStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("UEPluginLocalize")->GetBaseDir() / TEXT("Resources"));

	Style->Set("UEPluginLocalize.PluginAction", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));
	return Style;
}

void FUEPluginLocalizeStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FUEPluginLocalizeStyle::Get()
{
	return *StyleInstance;
}
