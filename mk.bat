SET VERSION=19

@REM setlocal enabledelayedexpansion
SET BASE_DIR=C:\DS\RADE%VERSION%\intel_a
call "%BASE_DIR%\code\command\tck_init.bat"
call "%BASE_DIR%\TCK\command\tck_profile.bat" "V5R%VERSION%_B%VERSION%"
call "%BASE_DIR%\code\command\mkGetPreq.bat" -p "C:\DS\B%VERSION%"
call "%BASE_DIR%\code\command\mkmk.bat" -au
call "%BASE_DIR%\code\command\mkrtv.bat"
