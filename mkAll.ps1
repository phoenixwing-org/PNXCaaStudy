# mkAll.ps1 - Build all workspaces in parallel
# license     MIT

# Command file name
$CommandFile = "mk.ps1"

# Get script root directory
$RootDir = $PSScriptRoot
 
# Import $Workspaces from project.ps1
. "$RootDir\project.ps1"

# Import common functions
. "$RootDir/tools/common.ps1"

# Run CommandFile in new window per workspace
Start-WorkspaceTasks -RootDir $RootDir -Workspaces $Workspaces -CommandFile $CommandFile