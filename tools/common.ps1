# Common PowerShell helpers
# license     MIT

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


