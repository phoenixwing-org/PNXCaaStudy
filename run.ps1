# PowerShell version of run.bat
param(
    [string]$Version = "19",
    [string]$Workspace = "",
    [switch]$Help
)

# Show help if requested
if ($Help) {
    Write-Host "Usage: run.ps1 [options]" -ForegroundColor Green
    Write-Host "Options:" -ForegroundColor Yellow
    Write-Host "  -Help or -h        Show this help message" -ForegroundColor White
    Write-Host "  -Version or -v     Set version number (default: 19)" -ForegroundColor White
    Write-Host "  -Workspace or -w   Set workspace path" -ForegroundColor White
    Write-Host ""
    Write-Host "Examples:" -ForegroundColor Yellow
    Write-Host "  .\run.ps1" -ForegroundColor Cyan
    Write-Host "  .\run.ps1 -Version 20" -ForegroundColor Cyan
    Write-Host "  .\run.ps1 -Version 20 -Workspace 'C:\MyWorkspace'" -ForegroundColor Cyan
    Write-Host "  .\run.ps1 -Help" -ForegroundColor Cyan
    exit 0
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
    $mkCreateRuntimeView = "$BaseDir\code\command\mkCreateRuntimeView.bat"
    $mkrun = "$BaseDir\code\command\mkrun.bat"
    
    Write-Host "Checking batch files..." -ForegroundColor Yellow
    Write-Host "  tck_init.bat: $(Test-Path $tckInit)" -ForegroundColor Gray
    Write-Host "  tck_profile.bat: $(Test-Path $tckProfile)" -ForegroundColor Gray
    Write-Host "  mkCreateRuntimeView.bat: $(Test-Path $mkCreateRuntimeView)" -ForegroundColor Gray
    Write-Host "  mkrun.bat: $(Test-Path $mkrun)" -ForegroundColor Gray
    Write-Host ""
    
    # Create temp directory if it doesn't exist
    $tempDir = "C:\temp"
    if (-not (Test-Path $tempDir)) {
        Write-Host "Creating temp directory: $tempDir" -ForegroundColor Yellow
        New-Item -ItemType Directory -Path $tempDir -Force | Out-Null
    }
    
    # Execute all batch files in a single cmd session to preserve environment variables
    Write-Host "Executing all batch files in sequence..." -ForegroundColor Cyan
    
    # Build batch commands array
    $batchCommands = @(
        "call `"$tckInit`"",
        "call `"$tckProfile`" `"V5R${Version}_B$Version`"",
        "call `"$mkCreateRuntimeView`"",
        "call `"$mkrun`" -c `"cnext`""
    )
    
    # Add workspace directory change at the beginning if provided
    if ($Workspace) {
        $batchCommands = @("cd /d `"$Workspace`"") + $batchCommands
    }
    
    $allCommands = $batchCommands -join " && "
    Write-Host "All commands: $allCommands" -ForegroundColor Yellow
 
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
    Write-Host "Run completed successfully!" -ForegroundColor Green
    Write-Host "=== END ===" -ForegroundColor Green
    
}
catch {
    Write-Host ""
    Write-Host "Error occurred during run:" -ForegroundColor Red
    Write-Host $_.Exception.Message -ForegroundColor Red
    Write-Host ""
    Write-Host "End time: $(Get-Date -Format 'HH:mm:ss')" -ForegroundColor Red
    Write-Host "=== END ===" -ForegroundColor Green
    exit 1
}
