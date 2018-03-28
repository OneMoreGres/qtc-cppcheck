#!/bin/bash

set -e

SELF_PATH="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"


sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get -qq update
sudo apt-get -y -qq install gcc-5 g++-5 wget libfontconfig libgl1-mesa-dev

GCC_PATH=/opt/gcc-5
sudo mkdir -p $GCC_PATH
sudo ln -sf /usr/bin/g++-5 $GCC_PATH/g++
sudo ln -sf /usr/bin/gcc-5 $GCC_PATH/gcc

mkdir -p download
mkdir -p qtcreator-latest
if [ -z "$VERSION" ]; then VERSION="debug"; fi
echo "$VERSION" > qtcreator-latest/version

if [ ! -d "qtcreator-latest/src" ]; then
  wget -cq http://download.qt.io/official_releases/qtcreator/4.6/4.6.0/qt-creator-opensource-src-4.6.0.tar.gz -O download/src.tar.gz
  tar axf download/src.tar.gz -C qtcreator-latest
  mv qtcreator-latest/qt-creator* qtcreator-latest/src
fi

if [ ! -d "qtcreator-latest/compiled" ]; then
  wget -cq http://download.qt.io/official_releases/online_installers/qt-unified-linux-x64-online.run -O download/installer.run
  chmod +x download/installer.run
  sudo QT_QPA_PLATFORM="minimal" download/installer.run --script "$SELF_PATH/qt_install.qs" -v
  sudo chmod a+w /opt/qt/Tools/QtCreator/lib/qtcreator/plugins
  ln -s /opt/qt/5.10.1/gcc_64 qtcreator-latest/Qt
  ln -s /opt/qt/Tools/QtCreator qtcreator-latest/compiled
fi

