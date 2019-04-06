#!/bin/bash

set -e

NORMAL=$(tput sgr0)
BOLD=$(tput bold)
MAGENTA=$(tput setaf 5)
function printTitle() {
    printf "${BOLD}${MAGENTA}$1\n${NORMAL}"
}
function printText() {
    printf "${NORMAL}$1\n"
}

if [ $# != 2 ]
then
    printText "Usage: package_macos.sh bundle_dir bundle_name"
    printText ""
    printText "  bundle_dir    The path to the executable."
    printText "  bundle_name   The executable file name."
    exit
fi

if [ ! -d $1 ]
then
    printText "Project path ($1) does not exist!"
    exit
fi

bundle_dir=$1
bundle_name=$2
bundle_framework_dir=${bundle_name}.app/Contents/Frameworks
bundle_target_dir=${bundle_name}.app/Contents/MacOS
bundle_executable=${bundle_target_dir}/${bundle_name}
system_framework_dir="/Library/Frameworks/"

printTitle "Copying frameworks into target bundle"
function copyFramework() {
    printText "  Copying $1"

    framework_name=$1
    framework_dir=${bundle_dir}/${bundle_framework_dir}/${framework_name}.framework

    rm -rf ${framework_dir}
    mkdir -p ${framework_dir}
    cp -R $2${framework_name}.framework/ ${framework_dir}
}
copyFramework "SDL2" ${system_framework_dir}
copyFramework "SDL2_image" ${system_framework_dir}
copyFramework "SDL2_ttf" ${system_framework_dir}
copyFramework "SDL2_mixer" ${system_framework_dir}

printTitle "Relocating frameworks"
function relocateFramework() {
    printText "  Relocating $1"

    framework_name=$1
    framework_version=$2
    framework_name_with_path=$1.framework/Versions/${framework_version}/$1

    install_name_tool -change @rpath/${framework_name_with_path} @executable_path/../Frameworks/${framework_name_with_path} ${bundle_dir}/${bundle_executable}
}
relocateFramework "SDL2" "A"
relocateFramework "SDL2_image" "A"
relocateFramework "SDL2_ttf" "A"
relocateFramework "SDL2_mixer" "A"

printTitle "Copying libraries into target bundle"
function copyLibrary() {
    printText "  Copying $1"

    library_system_path=$2
    framework_dir=${bundle_dir}/${bundle_framework_dir}/$1

    mkdir -p ${framework_dir}
    cp -f ${library_system_path}$1 ${framework_dir}
}
copyLibrary "libc++.1.dylib" "/usr/lib/"
copyLibrary "libSystem.B.dylib" "/usr/lib/"

printTitle "Relocating libraries"
function relocateLibrary() {
    printText "  Relocating $1"
    install_name_tool -change $2$1 @executable_path/../Frameworks/$1 ${bundle_dir}/${bundle_executable}
}
relocateLibrary "libc++.1.dylib" "/usr/lib/"
relocateLibrary "libSystem.B.dylib" "/usr/lib/"

printTitle "Checking relocation results"
otool -L ${bundle_dir}/${bundle_executable}

printTitle "Creating final archive"
archiveName="${bundle_name}-macOS.tar.gz"
cd ${bundle_dir}
tar -czf ${archiveName} ${bundle_name}.app/*

printTitle "Archive ${archiveName} is available in folder: ${bundle_dir}"
