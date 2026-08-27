$parentPath = Split-Path $PSScriptRoot -Parent
& "$env:ROOT_DIR\tools\mk.ps1" -Workspace "$parentPath\KTCAutoCodeWsp"
