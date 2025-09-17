@echo off

if not exist "C:\temp" (
    mkdir "C:\temp"
)
SET VERSION=19
SET BASE_DIR=C:\DS\RADE%VERSION%\intel_a
call "%BASE_DIR%\code\command\tck_init.bat"
call "%BASE_DIR%\TCK\command\tck_profile.bat" "V5R%VERSION%_B%VERSION%"
call "%BASE_DIR%\code\command\mkCreateRuntimeView.bat"
call "%BASE_DIR%\code\command\mkrun.bat" -c "cnext"
