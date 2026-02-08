# ClangFormat All
# license     MIT

# Command file name
$CommandFile = "clangfile.ps1"

# Get script root directory
$RootDir = $PSScriptRoot

# Define all workspaces (just directory names)
$Workspaces = @(
    "KTCAutoCodeWsp",
    "PNXBomAnalysisWsp",
    "PNXCombinedCurveWsp",
    "PNXCurveDivisionWsp",
    "PNXTemplateBaseWsp",
    "PNXTemplateFeatureWsp",
    "PNXV5V6AdapterWsp"
)

# Import common functions
. "$RootDir/tools/common.ps1"

# Run CommandFile in new window per workspace
$scriptArgs = "-Version " + $Version
Start-WorkspaceTasks -RootDir $RootDir -Workspaces $Workspaces -CommandFile $CommandFile -ScriptArguments $scriptArgs
