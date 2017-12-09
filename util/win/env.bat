@echo off

if "%ARCH%" == "" set ARCH=x64

if /i %ARCH% == x86       goto x86
if /i %ARCH% == x64       goto x64
goto end

:x64
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars64.bat"
set PATH=c:\Qt\5.10\msvc2017_64\bin\;%PATH%
set QT_DIR=c:\Qt\5.10\msvc2017_64\
goto end

:x86
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars32.bat"
set PATH=c:\Qt\5.10\msvc2017\bin\;%PATH%
set QT_DIR=c:\Qt\5.10\msvc2017\
goto end

:end
