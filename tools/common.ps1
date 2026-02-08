# Common PowerShell helpers
# license     MIT

function Get-CAA-Version {
    $Version = $env:CAA_MK_VERSION
    if ([string]::IsNullOrEmpty($Version)) {
        $Version = "19"
    }
    return $Version
}

# Initialize and check run.bat-style batch file paths under BaseDir. Returns object with TckInit, TckProfile, MkCreateRuntimeView, Mkrun.
function Get-CAA-RunBatchPaths {
    param(
        [string]$Workspace,
        [string]$Version = ""
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
    
    # Set base directory
    $BaseDir = "C:\DS\RADE$Version\intel_a"


    # Display configuration
    Write-Host "Version: $Version" -ForegroundColor Yellow
    if ($Workspace) {
    } 

    # Check if base directory exists
    if (-not (Test-Path $BaseDir)) {
        Write-Host "Error: Base directory does not exist: $BaseDir" -ForegroundColor Red
        Write-Host "Please check if the DS installation path is correct" -ForegroundColor Red
        exit 1
    }

    # Create temp directory if it doesn't exist
    $tempDir = "C:\temp"
    if (-not (Test-Path $tempDir)) {
        Write-Host "Creating temp directory: $tempDir" -ForegroundColor Yellow
        New-Item -ItemType Directory -Path $tempDir -Force | Out-Null
    }

    $paths = [PSCustomObject]@{
        TckInit             = Join-Path $BaseDir "code\command\tck_init.bat"
        TckProfile          = Join-Path $BaseDir "TCK\command\tck_profile.bat"
        TckProfileCmd       = Join-Path $BaseDir "TCK\command\tck_profile.bat `"V5R${Version}_B$Version`""
        MkCreateRuntimeView = Join-Path $BaseDir "code\command\mkCreateRuntimeView.bat"
        Mkrun               = Join-Path $BaseDir "code\command\mkrun.bat"
        TempDir             = $tempDir
        Version             = $Version
        Workspace           = $Workspace
        BaseDir             = $BaseDir
    }

    Write-Host " - Workspace: $Workspace" -ForegroundColor Yellow
    Write-Host " - Checking batch files..." -ForegroundColor Yellow
    Write-Host "   - tck_init.bat: $(Test-Path $paths.TckInit)" -ForegroundColor Gray
    Write-Host "   - tck_profile.bat: $(Test-Path $paths.TckProfile)" -ForegroundColor Gray
    Write-Host "   - mkCreateRuntimeView.bat: $(Test-Path $paths.MkCreateRuntimeView)" -ForegroundColor Gray
    # Write-Host "  - mkrun.bat: $(Test-Path $paths.Mkrun)" -ForegroundColor Gray
    Write-Host ""
    return $paths
}

# Check workspaces and required file; return valid workspace name array (empty = all failed)
function Test-WorkspaceFileCheck {
    param(
        [string]$RootDir,
        [string[]]$Workspaces,
        [string]$CommandFile = "clangfile.ps1"
    )
    $valid = @()
    $index = 0
    foreach ($ws in $Workspaces) {
        $index++
        $wsPath = Join-Path $RootDir $ws
        $targetFile = Join-Path $wsPath $CommandFile
        if (Test-Path $wsPath) {
            if (Test-Path $targetFile) {
                $valid += $ws
                Write-Host ("{0,3} : [OK] ./$ws/$CommandFile - Exists" -f $index) -ForegroundColor Green
            }
            else {
                Write-Host ("{0,3} : [ERROR] ./$ws - $CommandFile not found" -f $index) -ForegroundColor Red
            }
        }
        else {
            Write-Host ("{0,3} : [ERROR] ./$ws - Directory not found" -f $index) -ForegroundColor Red
        }
    }
    return $valid
}

# Run a command in new window for each valid workspace.
# Workspaces: full list; when provided without ValidWorkspaces, run Test-WorkspaceFileCheck first; when with ValidWorkspaces, used for error count.
# ValidWorkspaces: pre-validated list; when provided, skip check and use this list. Can be used together with Workspaces for "N errors remaining".
# CommandFile: script filename to run in each workspace (e.g. "clangfile.ps1", "mk.ps1"); also used in messages.
# ScriptArguments: optional args when invoking the script (e.g. "-Version 20"). Empty = no args.
function Start-WorkspaceTasks {
    param(
        [string]$RootDir,
        [string[]]$Workspaces = $null,
        [string[]]$ValidWorkspaces = $null,
        [string]$CommandFile,
        [string]$ScriptArguments = ""
    )

    if ($null -ne $ValidWorkspaces -and $ValidWorkspaces.Count -gt 0) {
        $toRun = $ValidWorkspaces
    }
    elseif ($null -ne $Workspaces -and $Workspaces.Count -gt 0) {
        $toRun = Test-WorkspaceFileCheck -RootDir $RootDir -Workspaces $Workspaces -CommandFile $CommandFile
        if ($toRun.Count -eq 0) {
            Write-Host ""
            Write-Host "Error: No valid workspace found!" -ForegroundColor Red
            exit 1
        }
    }
    else {
        return
    } 

    Write-Host ""
    Write-Host "Preparing to start $($toRun.Count) $CommandFile task(s)..." -ForegroundColor Yellow
    Write-Host ""

    $StartTime = Get-Date
    Write-Host "Start time: $($StartTime.ToString('yyyy-MM-dd HH:mm:ss'))" -ForegroundColor Green
    Write-Host ""

    $processes = @()
    $index = 0
    foreach ($ws in $toRun) {
        $index++
        $wsPath = Join-Path $RootDir $ws
        $scriptPath = Join-Path $wsPath $CommandFile
        if ($ScriptArguments) {
            $invokePart = "& '$scriptPath' $ScriptArguments"
        }
        else {
            $invokePart = "& '$scriptPath'"
        }
        $command = "Set-Location '$wsPath'; Write-Host ''; Write-Host '=== Workspace: $ws ===' -ForegroundColor Green; Write-Host ''; $invokePart"

        Write-Host ("{0,3} : Starting $CommandFile window: $ws" -f $index)  -ForegroundColor Cyan
        $process = Start-Process powershell -ArgumentList "-NoExit", "-ExecutionPolicy", "Bypass", "-Command", $command -PassThru
        $processes += @{
            Name      = $ws
            Process   = $process
            StartTime = Get-Date
        }
        Start-Sleep -Milliseconds 500
    }

    $processedCount = $toRun.Count
    if ($null -ne $Workspaces) { $errorCount = $Workspaces.Count - $processedCount } else { $errorCount = 0 }
    Write-Host ""
    $summaryMsg = "Started $processedCount $CommandFile window(s)."
    if ($null -ne $Workspaces -and $errorCount -gt 0) { $summaryMsg += ", $errorCount errors remaining."; $summaryColor = "Yellow" } else { $summaryColor = "Green" }
    Write-Host $summaryMsg -ForegroundColor $summaryColor
    Write-Host "All $CommandFile windows started successfully!" -ForegroundColor Green
    Write-Host "$CommandFile windows will continue running in background." -ForegroundColor Yellow
    Write-Host ""
} # end Start-WorkspaceTasks

# Run an array of batch command strings via a temporary .bat file (handles call "path", copy, etc.).
# Workspace: optional; when set, prepends "cd /d \"path\"" so batch runs in that directory.
# JoinWith: optional (e.g. " && "); when set, writes one line with commands joined (stop on first failure); otherwise one command per line.
# Returns the exit code from the batch; exits script with that code if non-zero.
function Invoke-BatchCommands
{
    param(
        [string[]]$BatchCommands,
        [string]$Workspace = ""
    )
    if ($null -eq $BatchCommands -or $BatchCommands.Count -eq 0) { return 0 }

    
    # Record start time
    $StartTime = Get-Date
    Write-Host ""
    Write-Host "=== START ===" -ForegroundColor Cyan    
    Write-Host "- Start time: $($StartTime.ToString('HH:mm:ss'))" -ForegroundColor Green

    $exitCode = 0
    $cmds = @($BatchCommands)
    if (-not [string]::IsNullOrEmpty($Workspace)) {
        $cmds = @("cd /d `"$Workspace`"") + $cmds
    }
    $tempBat = [System.IO.Path]::GetTempFileName() + ".bat"
    $cmds | Set-Content -Path $tempBat -Encoding ASCII
    Write-Host " - Temp bat file: $tempBat" -ForegroundColor Yellow
    Write-Host " - Batch commands: `n$($cmds -join "`n")" -ForegroundColor Yellow

    try {
        & cmd /c "`"$tempBat`""
        $exitCode = $LASTEXITCODE

        # Record end time and calculate runtime
        $EndTime = Get-Date
        $Duration = $EndTime - $StartTime
        
        Write-Host ""
        Write-Host "- End time: $($EndTime.ToString('HH:mm:ss'))" -ForegroundColor Green
        Write-Host "- Runtime: $($Duration.ToString('hh\:mm\:ss'))" -ForegroundColor Green
        Write-Host "- Run completed successfully!" -ForegroundColor Green
    }
    catch {
        Write-Host ""
        Write-Host "- Error occurred during run:" -ForegroundColor Red
        Write-Host $_.Exception.Message -ForegroundColor Red
        Write-Host ""
        Write-Host "- End time: $(Get-Date -Format 'HH:mm:ss')" -ForegroundColor Red
        $exitCode = 1
    }
    finally {
        if (Test-Path $tempBat) { Remove-Item $tempBat -Force }
    } 

    Write-Host "=== END ===" -ForegroundColor Green
    return $exitCode
}

