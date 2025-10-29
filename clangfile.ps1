# copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
# license     MIT

# Parameters
param(
    [string]$Workspace = "",
    [switch]$Help
)

# Show help information
if ($Help -or [string]::IsNullOrEmpty($Workspace)) {
    Write-Host "clangfile.ps1 - Code formatting tool" -ForegroundColor Green
    Write-Host "=====================================" -ForegroundColor Green
    Write-Host ""
    Write-Host "Usage: clangfile.ps1 -Workspace <path> [options]" -ForegroundColor Yellow
    Write-Host ""
    Write-Host "Parameters:" -ForegroundColor Yellow
    Write-Host "  -Workspace or -w   Workspace path (required)" -ForegroundColor White
    Write-Host "  -Help or -h        Show this help message" -ForegroundColor White
    Write-Host ""
    Write-Host "Examples:" -ForegroundColor Yellow
    Write-Host "  .\clangfile.ps1 -w 'C:\MyWorkspace'" -ForegroundColor Cyan
    Write-Host "  .\clangfile.ps1 -Workspace 'C:\MyWorkspace' -Help" -ForegroundColor Cyan
    Write-Host ""
    if ([string]::IsNullOrEmpty($Workspace)) {
        Write-Host "Error: Workspace path is required!" -ForegroundColor Red
    }
    exit 0
}

# Check if the workspace path exists
if (-not (Test-Path $Workspace)) {
    Write-Host "Error: Workspace path does not exist: $Workspace" -ForegroundColor Red
    Write-Host "Please provide a valid workspace path using -Workspace parameter" -ForegroundColor Red
    exit 1
}

# Set the directories to ignore
$ignoreDirectories = @(
    '.git',
    'ToolsData',
    '.vs',
    '.vscode',
    '.obsidian',
    'Debug',
    'Release',
    'win_b64',
    'intel_a',
    'build',
    'ImportedInterfaces',
    'ProtectedGenerated',
    'LocalGenerated',
    'Objects',
    'various',
    'CATEnv',
    'CNext'
)

$showDebug = 0

# Set the file extensions to process
$fileExtensions = @('*.h', '*.c', '*.hpp', '*.cpp')

# Statistics
$script:processedFiles = 0
$script:processedDirs = 0
$script:skippedDirs = 0

# Check if the directory should be ignored
function ShouldIgnoreDirectory {
    param (
        [string]$dirPath
    )
    
    if ($showDebug -ne 0) {
        Write-Host "Checking directory: $dirPath" -ForegroundColor Gray
    }
    
    foreach ($ignoreDir in $ignoreDirectories) {
        if ($dirPath -match "\\$ignoreDir(\\|$)") {
            if ($showDebug -ne 0) {
                Write-Host "  - Matched ignore pattern: $ignoreDir" -ForegroundColor Yellow
            }
            return $true
        }
    }
    if ($showDebug -ne 0) {
        Write-Host "  - Directory will be processed" -ForegroundColor Green
    }
    return $false
}

# Process a single file
function ProcessFile {
    param (
        [string]$filePath
    )
    
    Write-Host "Formatting file: $filePath"
    & clang-format.exe -style=file -i $filePath
    $script:processedFiles++
}

# Main processing function
function ProcessDirectory {
    param (
        [string]$currentDir
    )
    
    if ($showDebug -ne 0) {
        Write-Host "`n=== Checking Directory ===" -ForegroundColor Cyan
    }
    
    # Check if the current directory should be ignored
    if (ShouldIgnoreDirectory $currentDir) {
        if ($showDebug -ne 0) {
            Write-Host ">>> Skipping directory: $currentDir" -ForegroundColor Yellow
        }
        $script:skippedDirs++
        return
    }
    
    if ($showDebug -ne 0) {
        Write-Host ">>> Processing directory: $currentDir" -ForegroundColor Green
    }
    $script:processedDirs++
    
    # Process the files in the current directory
    foreach ($ext in $fileExtensions) {
        Get-ChildItem -Path $currentDir -Filter $ext -File | ForEach-Object {
            ProcessFile $_.FullName
        }
    }
    
    # Recursively process the subdirectories
    Get-ChildItem -Path $currentDir -Directory | ForEach-Object {
        ProcessDirectory $_.FullName
    }
}

Write-Host "-----Format files------" -ForegroundColor Cyan
Write-Host "Workspace: $Workspace" -ForegroundColor Cyan
Write-Host ""

# Clear the output: Clear-Host  No action

# Start processing
Write-Host ""
Write-Host "=== START ===" -ForegroundColor Cyan
Write-Host "=== clang-formt Workspace : $Workspace ===" -ForegroundColor Green
ProcessDirectory $Workspace

# Show statistics
Write-Host "`nSummary:" -ForegroundColor Cyan
Write-Host "- Processed directories: $script:processedDirs"
Write-Host "- Skipped directories: $script:skippedDirs"
Write-Host "- Formatted files: $script:processedFiles"

Write-Host "=== END ===" -ForegroundColor Green
