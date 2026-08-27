[CmdletBinding()]
param()

$ErrorActionPreference = "Stop"
$workDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$workspaceName = Split-Path $workDir -Leaf
$parentDir = Split-Path $workDir -Parent
$buildRoot = Join-Path (Join-Path $parentDir "build") $workspaceName

if ([string]::IsNullOrWhiteSpace($env:ROOT_DIR)) { $env:ROOT_DIR = "E:\KtRoot" }
if ([string]::IsNullOrWhiteSpace($env:ROOT_DIR_CORE)) { $env:ROOT_DIR_CORE = Join-Path $env:ROOT_DIR "kt\core" }
if ([string]::IsNullOrWhiteSpace($env:ROOT_DIR_INCLUDE)) { $env:ROOT_DIR_INCLUDE = Join-Path $env:ROOT_DIR "kt\core\include" }

& (Join-Path $workDir "export.ps1")
if ($LASTEXITCODE -ne 0) { throw "Header export failed." }

foreach ($buildType in @("Debug", "Release")) {
    $buildDir = "${buildRoot}${buildType}"
    Write-Host "===== CMake configure $buildType ====="
    & cmake "-DCMAKE_BUILD_TYPE=$buildType" "-DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE" `
        "--no-warn-unused-cli" -S $workDir -B $buildDir
    if ($LASTEXITCODE -ne 0) { throw "CMake configure $buildType failed." }

    Write-Host "===== CMake build $buildType ====="
    & cmake --build $buildDir --config $buildType
    if ($LASTEXITCODE -ne 0) { throw "CMake build $buildType failed." }
}

Write-Host "===== CMake install Release ====="
& cmake --install "${buildRoot}Release" --config Release
if ($LASTEXITCODE -ne 0) { throw "CMake install Release failed." }

Write-Host "Header export, Debug build and Release build completed."
