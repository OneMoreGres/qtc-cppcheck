#!/bin/bash

set -e

SELF_PATH="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

export PATH="$PWD/qtcreator-latest/Qt/bin/:$PATH"
ROOT="$SELF_PATH/../.."
echo `g++ --version`
echo `qmake --version`

export QTC_SOURCE="$PWD/qtcreator-latest/src"
export QTC_BUILD="$PWD/qtcreator-latest/compiled"

rm -rf build
mkdir -p build

cd build
lrelease "$ROOT/qtc-cppcheck.pro"
qmake "$ROOT/qtc-cppcheck.pro"
make -j`nproc`
cd ..


PLUGIN_NAME="QtcCppcheck"
VERSION=$(cat qtcreator-latest/version)

if [ ! -f "qtcreator-latest/compiled/lib/qtcreator/plugins/lib$PLUGIN_NAME.so" ]; then exit 1; fi

rm -rf dist
mkdir -p dist/lib/qtcreator/plugins
mkdir -p dist/share/qtcreator/translations
cp qtcreator-latest/compiled/lib/qtcreator/plugins/lib$PLUGIN_NAME.so dist/lib/qtcreator/plugins
strip dist/lib/qtcreator/plugins/lib$PLUGIN_NAME.so
ls -l dist/lib/qtcreator/plugins/lib$PLUGIN_NAME.so
cp $SELF_PATH/../../translation/*.qm dist/share/qtcreator/translations

rm -f $PLUGIN_NAME-$VERSION-linux-x64.tar.gz
cd dist
tar czf ../$PLUGIN_NAME-$VERSION-linux-x64.tar.gz . 
cd ..

ls -l $PLUGIN_NAME-$VERSION-linux-x64.tar.gz
