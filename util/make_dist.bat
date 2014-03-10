echo off
set VERSION=3.0.1
set PLUGIN_NAME=QtcCppcheck

set BIN_DIR=5.2.1-vc10-release
set RAR_PATH="c:\Program Files (x86)\WinRAR\Rar.exe"
set DIST_NAME=%PLUGIN_NAME%-%VERSION%-win.zip

del %DIST_NAME%
echo on

%RAR_PATH% a -aplib\qtcreator\plugins\Gres   -ep %DIST_NAME% c:\Projects\qt-creator\%VERSION%\%BIN_DIR%\lib\qtcreator\plugins\Gres\%PLUGIN_NAME%.pluginspec 
%RAR_PATH% a -aplib\qtcreator\plugins\Gres   -ep %DIST_NAME% c:\Projects\qt-creator\%VERSION%\%BIN_DIR%\lib\qtcreator\plugins\Gres\%PLUGIN_NAME%.dll 
%RAR_PATH% a -apshare\qtcreator\translations -ep %DIST_NAME% ..\translation\*.qm

copy c:\Projects\qt-creator\%VERSION%\%BIN_DIR%\lib\qtcreator\plugins\Gres\%PLUGIN_NAME%.dll        c:\Qt\Qt5\Tools\QtCreator\lib\qtcreator\plugins\Gres
copy c:\Projects\qt-creator\%VERSION%\%BIN_DIR%\lib\qtcreator\plugins\Gres\%PLUGIN_NAME%.pluginspec c:\Qt\Qt5\Tools\QtCreator\lib\qtcreator\plugins\Gres
copy ..\translation\*.qm                                                                            c:\Qt\Qt5\Tools\QtCreator\share\qtcreator\translations