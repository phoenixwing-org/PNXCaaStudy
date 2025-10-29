$parentPath = Split-Path $PSScriptRoot -Parent
& "../tools/mk.ps1" -v 19 -Workspace "$parentPath\KTCAutoCodeWsp"