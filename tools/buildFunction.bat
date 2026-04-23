@echo off
setlocal

rem Usage: buildFunction.bat [debug^|release] [workDir]
rem   %1 = Debug or Release (default: Debug)
rem   %2 = Project root dir (default: script directory)

set "buildType=%~1"

@REM get workspace name and parent directory
set "workDir=%~2"
if "%workDir:~-1%"=="\" set "workDir=%workDir:~0,-1%"
@REM get parent directory and diretory name
for %%I in ("%workDir%") do set "workspaceName=%%~nxI"

@REM get parent directory
for %%I in ("%workDir%") do set "parentDir=%%~dpI"

set "buildDir=%parentDir%build\%workspaceName%"

if "%buildType%"=="" set "buildType=Debug"

rem buildDir like E:/workspace/build/KtCoreRelease
if /i "%buildType%"=="Debug"   set "buildDir=%buildDir%Debug"
if /i "%buildType%"=="Release" set "buildDir=%buildDir%Release"

echo CMake Building %workspaceName% in "%buildDir%"

cd /d "%workDir%"
cmake -DCMAKE_BUILD_TYPE:STRING=%buildType% -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE --no-warn-unused-cli^
  -S "%workDir%" ^
  -B "%buildDir%"

cmake --build "%buildDir%" --config %buildType%

endlocal
