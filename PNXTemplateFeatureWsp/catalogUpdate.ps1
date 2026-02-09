# NOTE: PNXTemplateFeature Start Version is R20
# Converted from CatalogUpdatePNXTemplateFeature.bat
 
$ErrorActionPreference = "Stop"

# Import common functions
$parentPath = Split-Path $PSScriptRoot -Parent
. "$parentPath/tools/common.ps1"

# initialize batch paths
$Version = Get-CAA-Version # get version
$batchPaths = Get-CAA-RunBatchPaths -Version $Version -Workspace "$PSScriptRoot"
$sourcePath = ".\PNXTemplateFeatureFrm\CNext\resources\graphic"

# 设置 PATH（临时生效，仅当前会话）
$env:Path = "C:\DS\B$($batchPaths.Version)\win_b64\code\bin;$PSScriptRoot\win_b64\code\bin;$env:Path"

# Build batch commands array
$batchCommands = @(
    "PNXTemplateFeatureCatalog $sourcePath",
    "copy $sourcePath\*.CATFct .\win_b64\resources\graphic\"
)

# run batch commands
Invoke-BatchCommands -BatchCommands $batchCommands -Workspace "$PSScriptRoot"


