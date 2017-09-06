@echo off

set SELF_PATH=%~dp0
call %SELF_PATH%\env.bat


mkdir qtcreator-latest
mklink /D qtcreator-latest\Qt %QT_DIR%
if "%VERSION%"=="" set VERSION=debug
echo %VERSION%>qtcreator-latest\version


if exist qtcreator-latest/src goto build

mkdir download
if not exist download/src.zip  curl -fsSLk -o download\src.zip http://download.qt.io/official_releases/qtcreator/4.4/4.4.0/qt-creator-opensource-src-4.4.0.zip
unzip -qq download\src.zip -d qtcreator-latest
move qtcreator-latest\qt-creator* qtcreator-latest\src


:build

if exist qtcreator-latest\compiled\bin\qtcreator.exe goto end

mkdir qtcreator-latest\compiled
cd qtcreator-latest\compiled
qmake QMAKE_CXXFLAGS+=/MP ..\src
nmake /S
rd /Q /S src
cd ..\..

:end
