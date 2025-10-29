# mkAll.ps1 - Build all workspaces in parallel
# copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
# license     MIT

param(
    [string]$Version = "19",
    [switch]$Help
)

# Show help information
if ($Help) {
    Write-Host "mkAll.ps1 - Build all workspaces in parallel" -ForegroundColor Green
    Write-Host "=====================================" -ForegroundColor Green
    Write-Host ""
    Write-Host "Usage: mkAll.ps1 [options]" -ForegroundColor Yellow
    Write-Host ""
    Write-Host "Options:" -ForegroundColor Yellow
    Write-Host "  -Help or -h        Show this help message" -ForegroundColor White
    Write-Host "  -Version or -v     Set version number (default: 19)" -ForegroundColor White
    Write-Host ""
    Write-Host "Description:" -ForegroundColor Yellow
    Write-Host "  This script opens a new PowerShell window for each workspace" -ForegroundColor White
    Write-Host "  and builds them in parallel. Windows remain open after completion." -ForegroundColor White
    Write-Host ""
    Write-Host "Examples:" -ForegroundColor Yellow
    Write-Host "  .\mkAll.ps1" -ForegroundColor Cyan
    Write-Host "  .\mkAll.ps1 -Version 20" -ForegroundColor Cyan
    Write-Host "  .\mkAll.ps1 -Help" -ForegroundColor Cyan
    Write-Host ""
    exit 0
}

# Get script root directory
$RootDir = $PSScriptRoot

# Define all workspaces (just directory names)
$workspaces = @(
    "KTCAutoCodeWsp",
    "PNXBomAnalysisWsp",
    "PNXCombinedCurveWsp",
    "PNXCurveDivisionWsp"
)

Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "   Build All Workspaces in Parallel" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "Root directory: $RootDir" -ForegroundColor Yellow
Write-Host "Version: $Version" -ForegroundColor Yellow
Write-Host "Workspace count: $($workspaces.Count)" -ForegroundColor Yellow
Write-Host ""

# Check if workspaces exist
$validWorkspaces = @()
foreach ($ws in $workspaces) {
    $wsPath = Join-Path $RootDir $ws
    $mkScript = Join-Path $wsPath "mk.ps1"
    
    if (Test-Path $wsPath) {
        if (Test-Path $mkScript) {
            $validWorkspaces += $ws
            Write-Host "[OK] $ws - Ready" -ForegroundColor Green
        }
        else {
            Write-Host "[ERROR] $ws - mk.ps1 not found" -ForegroundColor Red
        }
    }
    else {
        Write-Host "[ERROR] $ws - Directory not found" -ForegroundColor Red
    }
}

if ($validWorkspaces.Count -eq 0) {
    Write-Host ""
    Write-Host "Error: No valid workspace found!" -ForegroundColor Red
    exit 1
}

Write-Host ""
Write-Host "Preparing to start $($validWorkspaces.Count) build task(s)..." -ForegroundColor Yellow
Write-Host ""

# Record start time
$StartTime = Get-Date
Write-Host "Start time: $($StartTime.ToString('yyyy-MM-dd HH:mm:ss'))" -ForegroundColor Green
Write-Host ""

# Start a new window for each workspace
$processes = @()
foreach ($ws in $validWorkspaces) {
    $wsPath = Join-Path $RootDir $ws
    $mkScript = Join-Path $wsPath "mk.ps1"
    
    Write-Host "Starting build window: $ws" -ForegroundColor Cyan
    
    # Build PowerShell command
    # -NoExit: Keep window open after execution
    # -ExecutionPolicy Bypass: Allow script execution
    # -Command: Command to execute
    $command = "Set-Location '$wsPath'; Write-Host ''; Write-Host '=== Workspace: $ws ===' -ForegroundColor Green; Write-Host ''; & '$mkScript' -Version $Version"
    
    # Start new PowerShell window
    $process = Start-Process powershell -ArgumentList "-NoExit", "-ExecutionPolicy", "Bypass", "-Command", $command -PassThru
    
    $processes += @{
        Name      = $ws
        Process   = $process
        StartTime = Get-Date
    }
    
    # Short delay to avoid resource competition
    Start-Sleep -Milliseconds 500
}

Write-Host ""
Write-Host "========================================" -ForegroundColor Green
Write-Host "  Started $($processes.Count) build window(s)" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Green
Write-Host ""
Write-Host "Tips:" -ForegroundColor Yellow
Write-Host "  - Each workspace builds in its own window" -ForegroundColor White
Write-Host "  - Windows remain open after build completion" -ForegroundColor White
Write-Host "  - You can check progress and results in each window" -ForegroundColor White
Write-Host "  - Closing a window does not affect other builds" -ForegroundColor White
Write-Host ""

# Display process information
Write-Host "Started build tasks:" -ForegroundColor Cyan
foreach ($p in $processes) {
    Write-Host "  - $($p.Name) (PID: $($p.Process.Id))" -ForegroundColor Gray
}

Write-Host ""
Write-Host "All build windows started successfully!" -ForegroundColor Green
Write-Host "Build windows will continue running in background." -ForegroundColor Yellow
Write-Host ""
