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

# Import $Workspaces from project.ps1
. "$ScriptDir\project.ps1"

$DirList = @( ) 

# Define directory array for symbolic links
foreach ($ws in $Workspaces) {
    $DirList += Join-Path $ScriptDir "$ws\win_b64"
}

# Set source directory
$SourceDir = Join-Path $ScriptDir "win_b64"

# Step 1: Remove existing symbolic links or regular folders
Remove-SymbolicLinkList -DirList $DirList

# Step 2: Recreate symbolic links
New-SymbolicLinkList -DirList $DirList -SourceDir $SourceDir

# Display footer
Show-ScriptFooter
