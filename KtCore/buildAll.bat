@echo off
setlocal
cd /d %~dp0

@REM  start debug and release
start "Build Debug"   cmd /k ""%~dp0..\tools\buildFunction.bat" Debug "%~dp0""
start "Build Release" cmd /k ""%~dp0..\tools\buildFunction.bat" Release "%~dp0""

echo Both build windows started.
endlocal
