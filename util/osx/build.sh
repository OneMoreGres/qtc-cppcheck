#!/bin/bash

set -e

SELF_PATH="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

export PATH="$PWD/qtcreator-latest/Qt/bin/:$PATH"
ROOT="$SELF_PATH/../.."
echo `clang --version`
echo `qmake --version`


export QTC_SOURCE="$PWD/qtcreator-latest/src"
export QTC_BUILD="$PWD/qtcreator-latest/compiled"

rm -rf build
mkdir -p build

cd build
lrelease "$ROOT/qtc-cppcheck.pro"
qmake "$ROOT/qtc-cppcheck.pro"
make
cd ..


PLUGIN_NAME="QtcCppcheck"
VERSION=$(cat qtcreator-latest/version)

if [ ! -f "qtcreator-latest/compiled/Contents/PlugIns/lib$PLUGIN_NAME.dylib" ]; then exit 1; fi

rm -rf dist
mkdir -p dist/Contents/PlugIns/
mkdir -p dist/Contents/Resources/translations
cp qtcreator-latest/compiled/Contents/PlugIns/lib$PLUGIN_NAME.dylib dist/Contents/PlugIns/
ls -l dist/Contents/PlugIns/lib$PLUGIN_NAME.dylib
cp $ROOT/translation/*.qm dist/Contents/Resources/translations

rm -f $PLUGIN_NAME-$VERSION-osx.tar.gz
cd dist
tar czf ../$PLUGIN_NAME-$VERSION-osx.tar.gz .
cd ..

ls -l $PLUGIN_NAME-$VERSION-osx.tar.gz
