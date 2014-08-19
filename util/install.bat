@echo off
set PLUGIN_NAME=QtcCppcheck
set BUILD_DIR=c:\Projects\qt-creator\3.2.0\qtcreator-5.3.1-vc10-release
set INSTALL_DIR=c:\Qt\qtcreator-3.2.0\
mkdir %INSTALL_DIR%\lib\qtcreator\plugins
@echo on

copy /Y %BUILD_DIR%\lib\qtcreator\plugins\%PLUGIN_NAME%.dll        %INSTALL_DIR%\lib\qtcreator\plugins
copy /Y %BUILD_DIR%\lib\qtcreator\plugins\%PLUGIN_NAME%.pluginspec %INSTALL_DIR%\lib\qtcreator\plugins
copy /Y ..\translation\*.qm                                        %INSTALL_DIR%\share\qtcreator\translations
