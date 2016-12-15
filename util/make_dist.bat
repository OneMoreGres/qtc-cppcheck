@echo off

set /p VERSION=<..\..\qtcreator-latest\version
set PLUGIN_NAME=QtcCppcheck
set BUILD_DIR=..\..\qtcreator-latest\release
del %PLUGIN_NAME%-%VERSION%-win.zip

rd /Q /S dist
mkdir dist\lib\qtcreator\plugins
mkdir dist\share\qtcreator\translations
copy /Y %BUILD_DIR%\lib\qtcreator\plugins\%PLUGIN_NAME%4.dll        dist\lib\qtcreator\plugins
copy /Y ..\translation\*.qm                                        dist\share\qtcreator\translations

cd dist
zip -q -r ../%PLUGIN_NAME%-%VERSION%-win.zip *
cd ..

rd /Q /S dist
