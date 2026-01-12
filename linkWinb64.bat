

@echo off
setlocal enabledelayedexpansion

echo ========================================
echo   PNXCaaStudy软链接重新连接脚本
echo ========================================



REM 设置源目录和目标目录
set SOURCE_DIR=%~dp0win_b64

REM 定义需要创建软链接的目录数组
set DIR_LIST[0]=%~dp0KTCAutoCodeWsp\win_b64
set DIR_LIST[1]=%~dp0PNXBomAnalysisWsp\win_b64
set DIR_LIST[2]=%~dp0PNXCombinedCurveWsp\win_b64
set DIR_LIST[3]=%~dp0PNXCurveDivisionWsp\win_b64
set DIR_LIST[4]=%~dp0PNXTemplateFeatureWsp\win_b64
set DIR_LIST[5]=%~dp0PNXTemplateBaseWsp\win_b64

REM 第一步：删除现有的软链接
echo.
echo [步骤1] 删除现有软链接
echo ----------------------------------------

set /a index=0
:delete_loop
if defined DIR_LIST[%index%] (
    set CURRENT_DIR=!DIR_LIST[%index%]!
    
    echo  %index%. 处理: !CURRENT_DIR!
    
    REM 检查目录是否存在
    if exist "!CURRENT_DIR!" (
        echo   正在删除...
        REM 直接尝试删除（适用于软链接）
        rmdir "!CURRENT_DIR!" >nul 2>&1
        if errorlevel 1 (
            REM 如果失败，尝试强制删除（适用于普通目录）
            rmdir /s /q "!CURRENT_DIR!" >nul 2>&1
            if errorlevel 1 (
                echo   错误：删除失败！请检查权限或手动删除
            ) else (
                echo   成功：已删除
            )
        ) else (
            echo   成功：已删除
        )
    ) else (
        echo   目录不存在，无需删除
    )
    
    echo.
    set /a index+=1
    goto delete_loop
)

REM 第二步：重新创建软链接
echo.
echo [步骤2] 重新创建软链接
echo ----------------------------------------

REM 检查源目录是否存在
if not exist "%SOURCE_DIR%" (
    echo 错误：源目录不存在！请检查：%SOURCE_DIR%
    pause
    exit /b 1
)

set /a index=0
:create_loop
if defined DIR_LIST[%index%] (
    set CURRENT_DIR=!DIR_LIST[%index%]!
    
    echo %index%.创建: !CURRENT_DIR!
    echo   指向: %SOURCE_DIR%
    
    REM 创建父目录（如果不存在）
    for %%A in ("!CURRENT_DIR!") do (
        set PARENT_DIR=%%~dpA
    )
    
    if not exist "!PARENT_DIR!" (
        echo   创建父目录: !PARENT_DIR!
        mkdir "!PARENT_DIR!" >nul 2>&1
    )
    
    REM 创建软链接
    mklink /J "!CURRENT_DIR!" "%SOURCE_DIR%" >nul 2>&1
    
    if errorlevel 1 (
        echo   错误：创建软链接失败！
    ) else (
        echo   成功：软链接已创建
    )
    
    echo.
    set /a index+=1
    goto create_loop
)

echo ========================================
echo   操作完成！
echo ========================================
