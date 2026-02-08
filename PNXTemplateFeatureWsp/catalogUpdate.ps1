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

# Build batch commands array
$batchCommands = @(
    "call `"$($batchPaths.TckInit)`"",
    "call `"$($batchPaths.TckProfile)`" $($batchPaths.ProfileVer)",
    "call `"$($batchPaths.MkCreateRuntimeView)`"",
    "call PNXTemplateFeatureCatalog $sourcePath",
    "copy $sourcePath\*.CATFct `".\win_b64\resources\graphic\`""
)

 # run batch commands
$null = Invoke-BatchCommands -BatchCommands $batchCommands -Workspace "$PSScriptRoot"
