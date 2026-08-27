[CmdletBinding()]
param(
    [string]$TargetCoreDirectory,
    [string]$TargetIncludeRoot
)

$ErrorActionPreference = "Stop"
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$sourceDir = Join-Path $scriptDir "KtCore\public\KtCore"

if ([string]::IsNullOrWhiteSpace($env:ROOT_DIR)) {
    throw "ROOT_DIR must be set before running export.ps1"
}
if ([string]::IsNullOrWhiteSpace($env:ROOT_DIR_CORE)) { $env:ROOT_DIR_CORE = Join-Path $env:ROOT_DIR "kt\core" }
if ([string]::IsNullOrWhiteSpace($TargetCoreDirectory)) { $TargetCoreDirectory = Join-Path $env:ROOT_DIR "kt\core" }

if ([string]::IsNullOrWhiteSpace($TargetIncludeRoot)) { $TargetIncludeRoot = $env:ROOT_DIR_INCLUDE }
if ([string]::IsNullOrWhiteSpace($TargetIncludeRoot)) { $TargetIncludeRoot = Join-Path $env:ROOT_DIR_CORE "include" }
if ([string]::IsNullOrWhiteSpace($TargetIncludeRoot)) {
    throw "Cannot determine the common header directory. Pass it as the second argument."
}

if (-not (Test-Path -LiteralPath $sourceDir -PathType Container)) {
    throw "Public header directory not found: $sourceDir"
}

$targetIncludeDir = Join-Path $TargetIncludeRoot "KtCore"
New-Item -ItemType Directory -Force -Path $targetIncludeDir | Out-Null

Write-Host "Exporting headers:"
Write-Host "  From: $sourceDir"
Write-Host "  To:   $targetIncludeDir"

Get-ChildItem -LiteralPath $sourceDir -Recurse -File |
    Where-Object { $_.Extension -in @(".h", ".hpp") } |
    ForEach-Object {
        $relativePath = $_.FullName.Substring($sourceDir.Length).TrimStart('\', '/')
        $destination = Join-Path $targetIncludeDir $relativePath
        New-Item -ItemType Directory -Force -Path (Split-Path $destination -Parent) | Out-Null
        Copy-Item -LiteralPath $_.FullName -Destination $destination -Force
    }

Write-Host "Header export completed successfully."
