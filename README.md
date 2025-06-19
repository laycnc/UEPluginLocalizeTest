# UEPluginLocalizeTest
UnrealEngine5のプラグインをローカライズする為のテストです

## プラグイン設定

```json
{
	"FileVersion": 3,
	"Version": 1,
	"VersionName": "1.0",
	"FriendlyName": "UEPluginLocalize",
	"Description": "",
	"Category": "Other",
	"CreatedBy": "",
	"CreatedByURL": "",
	"DocsURL": "",
	"MarketplaceURL": "",
	"SupportURL": "",
	"CanContainContent": false,
	"IsBetaVersion": false,
	"IsExperimentalVersion": false,
	"Installed": false,
	"Modules": [
		{
			"Name": "UEPluginLocalize",
			"Type": "Editor",
			"LoadingPhase": "Default"
		}
	],
    // ここが必要
	"LocalizationTargets": [
		{
			"Name": "UEPluginLocalize",
			"LoadingPolicy": "Editor",
			"ConfigGenerationPolicy": "Auto"
		}
	]
}
```

> FPluginManager::GetLocalizationPathsForEnabledPlugins

プラグインのローカライズパスの追加は上記のフォルダで行っています。  
LocalizationTargetsが無いとローカライズパスの追加が動作しないので注意してください

## ローカライズ設定

> Engine\Plugins\Online\OnlineSubsystem\Config\Localization\OnlineSubsystem.ini

エンジン側でローカライズ設定しているモノを移植します。  
上記のファイルをプラグイン名などにリネームした物を使う事でローカライズ設定を作る事ができます。

```ini
;METADATA=(Diff=true, UseCommands=true)
[CommonSettings]
SourcePath=%LOCPROJECTROOT%Plugins/プラグイン名/Content/Localization/プラグイン名
DestinationPath=Plugins/プラグイン名/Content/Localization/プラグイン名
ManifestName=プラグイン名.manifest
ArchiveName=プラグイン名.archive
PortableObjectName=プラグイン名.po
ResourceName=プラグイン名.locres
NativeCulture=en
CulturesToGenerate=en
CulturesToGenerate=ja

[GatherTextStep0]
CommandletClass=GatherTextFromSource
SearchDirectoryPaths=Plugins/UEPluginLocalize/Source/
FileNameFilters=*.cpp
FileNameFilters=*.h
FileNameFilters=*.c
FileNameFilters=*.inl
FileNameFilters=*.mm
FileNameFilters=*.ini
ShouldGatherFromEditorOnlyData=false

[GatherTextStep1]
CommandletClass=GenerateGatherManifest

[GatherTextStep2]
CommandletClass=GenerateGatherArchive

[GatherTextStep3]
CommandletClass=InternationalizationExport
bImportLoc=true

[GatherTextStep4]
CommandletClass=GenerateTextLocalizationResource

[GatherTextStep5]
CommandletClass=InternationalizationExport
bExportLoc=true
```


```bat
UnrealEditor-Cmd.exe プロジェクト名.uproject -run=GatherText -config="Plugins\プラグイン名\Config\Localization\プラグイン名.ini"
```

ローカライズ設定用のiniファイルを用意してから上記のコマンドを実行するとローカライズが出力されます