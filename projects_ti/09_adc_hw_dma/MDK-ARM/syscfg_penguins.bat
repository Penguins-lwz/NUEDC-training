@echo off

set SDK_JSON="C:\ti\mspm0_sdk_2_03_00_07\.metadata\product.json"
set SYSCFG_BAT="C:\ti\sysconfig_1.22.0\sysconfig_cli.bat"
set SYSCFG_DIR="%~dp0..\MSPM0-SDK"
set SYSCFG_FILE="%~dp0..\MSPM0-SDK\project.syscfg"

call %SYSCFG_BAT% -o %SYSCFG_DIR% -s %SDK_JSON% --compiler keil %SYSCFG_FILE%
