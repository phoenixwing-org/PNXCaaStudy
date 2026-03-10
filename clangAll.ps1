# ClangFormat All
# license     MIT

# show clang-format version
$clangVersion = clang-format --version
Write-Host "Clang version: $clangVersion" -ForegroundColor Green

# Command file name
$CommandFile = "clangfile.ps1"

# Get script root directory
$RootDir = $PSScriptRoot

# Import $Workspaces from project.ps1
. "$RootDir\project.ps1"
$Workspaces += "PNXV5V6AdapterWsp"

# Import common functions
. "$RootDir/tools/common.ps1"

# Run CommandFile in new window per workspace
$scriptArgs = "-Version " + $Version
Start-WorkspaceTasks -RootDir $RootDir -Workspaces $Workspaces -CommandFile $CommandFile -ScriptArguments $scriptArgs
