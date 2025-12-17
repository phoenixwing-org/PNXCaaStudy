# PowerShell version of mk.bat
param(
    [string]$Version = "",
    [string]$Workspace = "",
    [switch]$Help,
    [switch]$UseBat
)

# if Version is empty use env CAA_MK_VERSION
if ([string]::IsNullOrEmpty($Version)) {
    $Version = $env:CAA_MK_VERSION
    Write-Host "Version from env: $Version" -ForegroundColor Yellow
    if ([string]::IsNullOrEmpty($Version)) {
        $Version = "19"
        Write-Host "Version set to default: $Version" -ForegroundColor Yellow
    }
}
else {
    Write-Host "Version from parameter: $Version" -ForegroundColor Yellow
}

# Show help if requested
if ($Help) {
    Write-Host "Usage: mk.ps1 [options]" -ForegroundColor Green
    Write-Host "Options:" -ForegroundColor Yellow
    Write-Host "  -Help or -h        Show this help message" -ForegroundColor White
    Write-Host "  -Version or -v     Set version number (default: 19)" -ForegroundColor White
    Write-Host "  -Workspace or -w   Set workspace path" -ForegroundColor White
    Write-Host "  -UseBat            Use original mk.bat instead of PowerShell" -ForegroundColor White
    Write-Host ""
    Write-Host "Examples:" -ForegroundColor Yellow
    Write-Host "  .\mk.ps1" -ForegroundColor Cyan
    Write-Host "  .\mk.ps1 -Version 20" -ForegroundColor Cyan
    Write-Host "  .\mk.ps1 -Version 20 -Workspace 'C:\MyWorkspace'" -ForegroundColor Cyan
    Write-Host "  .\mk.ps1 -UseBat" -ForegroundColor Cyan
    Write-Host "  .\mk.ps1 -Help" -ForegroundColor Cyan
    exit 0
}

# If UseBat is specified, call the original mk.bat
if ($UseBat) {
    Write-Host "Using original mk.bat..." -ForegroundColor Yellow
    $batFile = Join-Path $PSScriptRoot "mk.bat"
    if (Test-Path $batFile) {
        & $batFile
        exit $LASTEXITCODE
    }
    else {
        Write-Host "Error: mk.bat not found at $batFile" -ForegroundColor Red
        exit 1
    }
}

# Clear screen Clear-Host No action

Write-Host ""
Write-Host "=== START ===" -ForegroundColor Cyan
# Set base directory
$BaseDir = "C:\DS\RADE$Version\intel_a"

# Record start time
$StartTime = Get-Date
Write-Host "Start time: $($StartTime.ToString('HH:mm:ss'))" -ForegroundColor Green

# Display configuration
Write-Host "Version: $Version" -ForegroundColor Yellow
if ($Workspace) {
    Write-Host "Workspace: $Workspace" -ForegroundColor Yellow
}
Write-Host ""

# Check if base directory exists
if (-not (Test-Path $BaseDir)) {
    Write-Host "Error: Base directory does not exist: $BaseDir" -ForegroundColor Red
    Write-Host "Please check if the DS installation path is correct" -ForegroundColor Red
    exit 1
}

# Execute commands with error handling
try {
    # Check each batch file exists before executing
    $tckInit = "$BaseDir\code\command\tck_init.bat"
    $tckProfile = "$BaseDir\TCK\command\tck_profile.bat"
    $mkGetPreq = "$BaseDir\code\command\mkGetPreq.bat"
    $mkmk = "$BaseDir\code\command\mkmk.bat"
    $mkrtv = "$BaseDir\code\command\mkrtv.bat"
    
    Write-Host "Checking batch files..." -ForegroundColor Yellow
    Write-Host "  tck_init.bat: $(Test-Path $tckInit)" -ForegroundColor Gray
    Write-Host "  tck_profile.bat: $(Test-Path $tckProfile)" -ForegroundColor Gray
    Write-Host "  mkGetPreq.bat: $(Test-Path $mkGetPreq)" -ForegroundColor Gray
    Write-Host "  mkmk.bat: $(Test-Path $mkmk)" -ForegroundColor Gray
    Write-Host "  mkrtv.bat: $(Test-Path $mkrtv)" -ForegroundColor Gray
    Write-Host ""
    
    # Execute all batch files in a single cmd session to preserve environment variables
    Write-Host "Executing all batch files in sequence..." -ForegroundColor Cyan
   
    # add workspace preq parameter
    $workspacePreq = "C:\DS\B$Version"
    if ($Workspace) {
        $workspacePreq += ";$Workspace"
    } 
    Write-Host "Workspace preq: $workspacePreq" -ForegroundColor Yellow
    Write-Host ""
    
    $batchCommands = @(
        "call `"$tckInit`"",
        "call `"$tckProfile`" `"V5R${Version}_B$Version`"",
        "call `"$mkGetPreq`" -p `"$workspacePreq`"",
        "call `"$mkmk`" -au",
        "call `"$mkrtv`""
    )
    
    $allCommands = $batchCommands -join " && "
    & cmd /c $allCommands
    
    # Check if any command failed
    if ($LASTEXITCODE -ne 0) {
        throw "Command failed with exit code: $LASTEXITCODE"
    }
    
    # Record end time and calculate runtime
    $EndTime = Get-Date
    $Duration = $EndTime - $StartTime
    
    Write-Host ""
    Write-Host "End time: $($EndTime.ToString('HH:mm:ss'))" -ForegroundColor Green
    Write-Host "Runtime: $($Duration.ToString('hh\:mm\:ss'))" -ForegroundColor Green
    Write-Host "Build completed successfully!" -ForegroundColor Green
    Write-Host "=== END ===" -ForegroundColor Green
}
catch {
    Write-Host ""
    Write-Host "Error occurred during build:" -ForegroundColor Red
    Write-Host $_.Exception.Message -ForegroundColor Red
    Write-Host ""
    Write-Host "End time: $(Get-Date -Format 'HH:mm:ss')" -ForegroundColor Red
    Write-Host "=== END ===" -ForegroundColor Green

    exit 1
}
