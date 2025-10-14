# copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
# license     MIT
# 设置需要忽略的目录
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

# 设置要处理的文件扩展名
$fileExtensions = @('*.h', '*.c', '*.hpp', '*.cpp')

# 统计信息
$script:processedFiles = 0
$script:processedDirs = 0
$script:skippedDirs = 0

# 检查目录是否应该被忽略
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

# 处理单个文件
function ProcessFile {
    param (
        [string]$filePath
    )
    
    Write-Host "Formatting file: $filePath"
    & clang-format.exe -style=file -i $filePath
    $script:processedFiles++
}

# 主处理函数
function ProcessDirectory {
    param (
        [string]$currentDir
    )
    
    if ($showDebug -ne 0) {
        Write-Host "`n=== Checking Directory ===" -ForegroundColor Cyan
    }
    
    # 检查当前目录是否应该被忽略
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
    
    # 处理当前目录中的文件
    foreach ($ext in $fileExtensions) {
        Get-ChildItem -Path $currentDir -Filter $ext -File | ForEach-Object {
            ProcessFile $_.FullName
        }
    }
    
    # 递归处理子目录
    Get-ChildItem -Path $currentDir -Directory | ForEach-Object {
        ProcessDirectory $_.FullName
    }
}

Write-Host "-----Format files------" -ForegroundColor Cyan
Write-Host "Starting directory: $PWD" -ForegroundColor Cyan
Write-Host ""

# 清空输出
Clear-Host

# 开始处理
Write-Host "=== Starting to process directory: $PWD ===" -ForegroundColor Cyan
ProcessDirectory $PWD

# 显示统计信息
Write-Host "`nSummary:" -ForegroundColor Cyan
Write-Host "- Processed directories: $script:processedDirs"
Write-Host "- Skipped directories: $script:skippedDirs"
Write-Host "- Formatted files: $script:processedFiles"
