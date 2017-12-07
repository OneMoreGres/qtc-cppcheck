#!/bin/bash

set -e

SELF_PATH="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

mkdir -p download
mkdir -p qtcreator-latest
if [ -z "$VERSION" ]; then VERSION="debug"; fi
echo "$VERSION" > qtcreator-latest/version

if [ ! -d "qtcreator-latest/src" ]; then
  curl -fsSLk -o download/src.tar.gz http://download.qt.io/official_releases/qtcreator/4.5/4.5.0/qt-creator-opensource-src-4.5.0.tar.gz
  tar zxf download/src.tar.gz -C qtcreator-latest
  mv qtcreator-latest/qt-creator* qtcreator-latest/src
fi

if [ ! -d "qtcreator-latest/compiled" ]; then
  curl -fsSLk -o download/installer.dmg http://download.qt.io/official_releases/online_installers/qt-unified-mac-x64-online.dmg
  hdiutil attach -mountpoint installer download/installer.dmg
  ln -s installer/qt-*/Contents/MacOS/qt-* run
  ls -l run
  sudo QT_QPA_PLATFORM="minimal" ./run --script "$SELF_PATH/qt_install.qs" -v
  rm run
  hdiutil unmount installer
  sudo chmod a+w /opt/qt/Qt\ Creator.app/Contents/PlugIns
  ln -s /opt/qt/5.10.0/clang_64 qtcreator-latest/Qt
  ln -s /opt/qt/Qt\ Creator.app qtcreator-latest/compiled
fi

