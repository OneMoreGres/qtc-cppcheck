@echo off
set VERSION=3.2.0
set PLUGIN_NAME=QtcCppcheck
set BUILD_DIR=c:\Projects\qt-creator\3.2.0\qtcreator-5.3.1-vc10-release
del %PLUGIN_NAME%-%VERSION%-win.zip

rd /Q /S dist
mkdir dist\lib\qtcreator\plugins
mkdir dist\share\qtcreator\translations
copy /Y %BUILD_DIR%\lib\qtcreator\plugins\%PLUGIN_NAME%.dll        dist\lib\qtcreator\plugins
copy /Y %BUILD_DIR%\lib\qtcreator\plugins\%PLUGIN_NAME%.pluginspec dist\lib\qtcreator\plugins
copy /Y ..\translation\*.qm                                             dist\share\qtcreator\translations

cd dist
zip -q -r ../%PLUGIN_NAME%-%VERSION%-win.zip *
cd ..

rd /Q /S dist
