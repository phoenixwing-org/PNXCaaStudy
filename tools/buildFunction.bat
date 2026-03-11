@echo off
setlocal

rem Usage: buildFunction.bat [debug^|release] [work_dir]
rem   %1 = Debug or Release (default: Debug)
rem   %2 = Project root dir (default: script directory)

set "BUILD_TYPE=%~1"
set "WORK_DIR=%~2"

if "%BUILD_TYPE%"=="" set "BUILD_TYPE=Debug"
if "%WORK_DIR%"=="" set "WORK_DIR=%~dp0"
if "%WORK_DIR:~-1%"=="\" set "WORK_DIR=%WORK_DIR:~0,-1%"

rem build_debug / build_release (or build_<Config> for others)
set "BUILD_DIR=%WORK_DIR%\build_%BUILD_TYPE%"
if /i "%BUILD_TYPE%"=="Debug"   set "BUILD_DIR=%WORK_DIR%\build_debug"
if /i "%BUILD_TYPE%"=="Release" set "BUILD_DIR=%WORK_DIR%\build_release"

cd /d "%WORK_DIR%"

echo Building %BUILD_TYPE% in "%BUILD_DIR%"

cmake -DCMAKE_BUILD_TYPE:STRING=%BUILD_TYPE% -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE --no-warn-unused-cli^
  -S "%WORK_DIR%" ^
  -B "%BUILD_DIR%"

cmake --build "%BUILD_DIR%" --config %BUILD_TYPE%

pause
endlocal
