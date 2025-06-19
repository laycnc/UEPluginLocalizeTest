# UEPluginLocalizeTest.uprojectのフルパスを取得
$projectRoot = Split-Path -Parent $MyInvocation.MyCommand.Definition
$uprojectPath = Get-ChildItem -Path $projectRoot -Filter *.uproject -Recurse -ErrorAction SilentlyContinue | Select-Object -First 1 -ExpandProperty FullName
# UEPluginLocalize.iniのフルパスを取得
$iniPath = Get-ChildItem -Path $projectRoot -Filter UEPluginLocalize.ini -Recurse -ErrorAction SilentlyContinue | Select-Object -First 1 -ExpandProperty FullName

if (-not $uprojectPath || -not $iniPath) {
    Write-Error "ファイルが見つかりませんでした。"
    exit 1
}

# uprojectファイルからエンジンのバージョンを取得
$json = Get-Content $uprojectPath -Raw | ConvertFrom-Json
[string] $EngineAssociation = $json.EngineAssociation

# レジストリからUnrealEngineのパスを取得する
$regPath = "HKLM:\SOFTWARE\EpicGames\Unreal Engine\$EngineAssociation"
$installedDir = (Get-ItemProperty -Path $regPath -Name 'InstalledDirectory').InstalledDirectory


# UnrealEditor-Cmd.exe UEPluginLocalizeTest.uproject -run=GatherText -config="Plugins\UEPluginLocalize\Config\Localization\UEPluginLocalize.ini"
# 上記のコマンドをフルパスで実行させる
$unrealeditorCmd = Join-Path $installedDir 'Engine\Binaries\Win64\UnrealEditor-Cmd.exe'
& $unrealeditorCmd $uprojectPath -run=GatherText -config="$iniPath"
