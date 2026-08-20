@echo off
setlocal
cd /d %~dp0

@REM  start debug and release
set "workDir=%~dp0"
start "Build Debug"   cmd /k ""%workDir%..\tools\buildFunction.bat" Debug "%workDir%""
start "Build Release" cmd /k ""%workDir%..\tools\buildFunction.bat" Release "%workDir%""

echo Both build windows started.
endlocal
