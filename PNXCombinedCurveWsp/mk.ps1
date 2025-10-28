# combine directory path
$parentPath = Split-Path $PSScriptRoot -Parent
$workspacePreq = Join-Path $parentPath "KTCAutoCodeWsp"

# call main mk.ps1 script
& "../mk.ps1" -v 19 -Workspace $workspacePreq