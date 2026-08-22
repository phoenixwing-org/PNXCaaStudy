$ErrorActionPreference = "Stop"

$envValues = @{
    CAA_MK_VERSION = "19"
    ROOT_DIR = "E:\PNXRoot"
    ROOT_DIR_3rdParty = "E:\3rdParty"
}

$envValues.ROOT_DIR_CORE = Join-Path $envValues.ROOT_DIR "kt\core"
$envValues.ROOT_DIR_INCLUDE = Join-Path $envValues.ROOT_DIR_CORE "include"

foreach ($entry in $envValues.GetEnumerator()) {
    [Environment]::SetEnvironmentVariable($entry.Key, $entry.Value, "User")
    Set-Item -Path "Env:$($entry.Key)" -Value $entry.Value
    Write-Host "$($entry.Key)=$($entry.Value)"
}

Write-Host "User environment variables updated."
