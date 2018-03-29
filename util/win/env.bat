@echo off

if "%ARCH%" == "" set ARCH=x86

if /i %ARCH% == x86       goto x86
if /i %ARCH% == x64       goto x64
goto end

:x64
call "c:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" amd64
set PATH=c:\Qt\5.10.1\msvc2015_64\bin\;%PATH%
set QT_DIR=c:\Qt\5.10.1\msvc2015_64\
goto end

:x86
call "c:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86
set PATH=c:\Qt\5.10.1\msvc2015\bin\;%PATH%
set QT_DIR=c:\Qt\5.10.1\msvc2015\
goto end

:end
