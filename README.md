#Qt Creator Cppcheck Integration

##Introduction
Plugin integrates some [Cppcheck](http://cppcheck.sourceforge.net/ "Cppcheck") functionality into Qt Creator IDE.

##Features
* Automatically check active project after build
* Automatically check active project's files on save
* Manually check any project's file
* Display found error in task pan (with marks in editor)
* Most settings are configurable
* Translation support

##Tips
* Checking for unused functions prevents use of several threads and can decrease performance
* Custom launch parameters are passing *before* plugin's so can take no effect

##Downloads
Built plugin can be downloaded [here](https://sourceforge.net/projects/qtc-cppcheck/ "Sourceforge")
or from github releases.


##Installation
IMPORTANT: plugin's version must match Qt Creator's version (difference in last digit is acceptable)

###From source
1. Change paths.pri:

 - set `QTCREATOR_SOURCES` = path to Qt Creator source dir (with qtcreator.pro)
 - set `IDE_BUILD_TREE` = path to compiled Qt Creator dir (with bin,lib,libexec,...)

2. Compile plugin.

###From binaries
1. Extract/copy files from archive into Qt Creator's dir (archive already contains proper paths).
2. Enable plugin in Help->Modules menu.


##More info
Additional information can be obtained [here](http://gres.biz/qtc-cppcheck/ "Homepage") (in russian)
