# PNXCaaStudy Symbolic Link Script

# Load common functions
$CommonScript = Join-Path $PSScriptRoot "tools\LinkWinb64Common.ps1"
. $CommonScript

# Display header
Show-ScriptHeader -Title "PNXCaaStudy Symbolic Link Script"

# Get script directory
$ScriptDir = $PSScriptRoot
if (-not $ScriptDir) {
    $ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
}

# Set source directory
$SourceDir = Join-Path $ScriptDir "win_b64"

# Define directory array for symbolic links
$DirList = @(    
    (Join-Path $ScriptDir "KTCAutoCodeWsp\win_b64"),
    (Join-Path $ScriptDir "PNXBomAnalysisWsp\win_b64"),
    (Join-Path $ScriptDir "PNXCombinedCurveWsp\win_b64"),
    (Join-Path $ScriptDir "PNXCurveDivisionWsp\win_b64"),
    (Join-Path $ScriptDir "PNXTemplateFeatureWsp\win_b64"),
    (Join-Path $ScriptDir "PNXTemplateBaseWsp\win_b64")
)

# Step 1: Remove existing symbolic links or regular folders
Remove-SymbolicLinkList -DirList $DirList

# Step 2: Recreate symbolic links
New-SymbolicLinkList -DirList $DirList -SourceDir $SourceDir

# Display footer
Show-ScriptFooter
