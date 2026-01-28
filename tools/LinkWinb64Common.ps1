# Common functions for symbolic link management scripts

# Remove a directory (symbolic link or regular folder)
function Remove-SymbolicLinkOrFolder {
    param(
        [string]$Path
    )
    
    if (-not (Test-Path $Path)) {
        Write-Host "    Directory does not exist, skipping" -ForegroundColor DarkGray
        return $true
    }
    
    Write-Host "    Deleting... " -NoNewline -ForegroundColor Gray
    
    try {
        $item = Get-Item $Path -Force -ErrorAction SilentlyContinue
        
        # Check if it's a symbolic link (Junction or SymbolicLink)
        $isLink = $false
        if ($null -ne $item) {
            if ($item.LinkType) {
                $isLink = $true
                Write-Host "(Symbolic Link) " -NoNewline -ForegroundColor DarkYellow
            } else {
                Write-Host "(Regular Folder) " -NoNewline -ForegroundColor DarkYellow
            }
        } else {
            Write-Host "(Regular Folder) " -NoNewline -ForegroundColor DarkYellow
        }
        
        # Remove directory (symbolic link or regular folder)
        Remove-Item -Path $Path -Force -Recurse -ErrorAction Stop
        
        # Verify deletion success
        Start-Sleep -Milliseconds 100
        if (Test-Path $Path) {
            Write-Host "Failed: Directory still exists!" -ForegroundColor Red
            Write-Host "    Please delete manually: $Path" -ForegroundColor Red
            return $false
        } else {
            if ($isLink) {
                Write-Host "Success: Symbolic link deleted" -ForegroundColor Green
            } else {
                Write-Host "Success: Regular folder force deleted" -ForegroundColor Green
            }
            return $true
        }
    } catch {
        Write-Host "Failed: $($_.Exception.Message)" -ForegroundColor Red
        Write-Host "    Please check permissions or delete manually: $Path" -ForegroundColor Red
        return $false
    }
}

# Create a symbolic link (Junction)
function New-SymbolicLink {
    param(
        [string]$Path,
        [string]$Target
    )
    
    try {
        # Create parent directory (if not exists)
        $ParentDir = Split-Path -Parent $Path
        if (-not (Test-Path $ParentDir)) {
            Write-Host "    Creating parent directory: $ParentDir" -ForegroundColor DarkGray
            New-Item -ItemType Directory -Path $ParentDir -Force | Out-Null
        }
        
        # Create symbolic link (Junction)
        New-Item -ItemType Junction -Path $Path -Target $Target -Force | Out-Null
        
        # Verify creation success
        Start-Sleep -Milliseconds 100
        if (Test-Path $Path) {
            $linkItem = Get-Item $Path -Force
            if ($linkItem.LinkType -eq "Junction") {
                Write-Host "    Success: Symbolic link created" -ForegroundColor Green
                return $true
            } else {
                Write-Host "    Warning: Created item is not a symbolic link" -ForegroundColor Yellow
                return $false
            }
        } else {
            Write-Host "    Error: Failed to create symbolic link!" -ForegroundColor Red
            return $false
        }
    } catch {
        Write-Host "    Error: Failed to create symbolic link!" -ForegroundColor Red
        Write-Host "    $($_.Exception.Message)" -ForegroundColor Red
        return $false
    }
}

# Process directory list: remove existing links/folders
function Remove-SymbolicLinkList {
    param(
        [string[]]$DirList,
        [string]$StepTitle = "[Step 1] Removing existing links/folders"
    )
    
    Write-Host $StepTitle -ForegroundColor Yellow
    Write-Host "----------------------------------------" -ForegroundColor Yellow
    Write-Host ""
    
    $index = 0
    foreach ($CurrentDir in $DirList) {
        Write-Host "  $index. Processing: " -NoNewline -ForegroundColor White
        Write-Host $CurrentDir -ForegroundColor Cyan
        
        Remove-SymbolicLinkOrFolder -Path $CurrentDir
        
        Write-Host ""
        $index++
    }
}

# Process directory list: create symbolic links
function New-SymbolicLinkList {
    param(
        [string[]]$DirList,
        [string]$SourceDir,
        [string]$StepTitle = "[Step 2] Creating symbolic links"
    )
    
    Write-Host $StepTitle -ForegroundColor Yellow
    Write-Host "----------------------------------------" -ForegroundColor Yellow
    Write-Host ""
    
    # Check if source directory exists
    if (-not (Test-Path $SourceDir)) {
        Write-Host "Error: Source directory does not exist!" -ForegroundColor Red
        Write-Host "Please check: $SourceDir" -ForegroundColor Red
        Read-Host "Press Enter to exit"
        exit 1
    }
    
    $index = 0
    foreach ($CurrentDir in $DirList) {
        Write-Host "$index. Creating: " -NoNewline -ForegroundColor White
        Write-Host $CurrentDir -ForegroundColor Cyan
        Write-Host "    Target: " -NoNewline -ForegroundColor Gray
        Write-Host $SourceDir -ForegroundColor DarkCyan
        
        New-SymbolicLink -Path $CurrentDir -Target $SourceDir
        
        Write-Host ""
        $index++
    }
}

# Display header
function Show-ScriptHeader {
    param(
        [string]$Title
    )
    
    Write-Host ""
    Write-Host "========================================" -ForegroundColor Magenta
    Write-Host "  $Title" -ForegroundColor Magenta
    Write-Host "========================================" -ForegroundColor Magenta
    Write-Host ""
}

# Display footer
function Show-ScriptFooter {
    Write-Host "========================================" -ForegroundColor Magenta
    Write-Host "  Operation completed!" -ForegroundColor Magenta
    Write-Host "========================================" -ForegroundColor Magenta
    Write-Host ""
}
