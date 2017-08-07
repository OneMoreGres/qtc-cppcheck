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
make
cd ..


PLUGIN_NAME="QtcCppcheck"
VERSION=$(cat qtcreator-latest/version)

if [ ! -f qtcreator-latest/compiled/Contents/PlugIns/lib$PLUGIN_NAME.dylib ]; then exit 1; fi
cp qtcreator-latest/compiled/Contents/PlugIns/lib$PLUGIN_NAME.dylib lib$PLUGIN_NAME.dylib

ls -l lib$PLUGIN_NAME.dylib
