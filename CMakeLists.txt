project (kdeconnect-dbus)

cmake_minimum_required (VERSION 3.12.4)

option (BUILD_DDE_DOCK_PLUGIN "Build DDE dock plugin" ON)
option (BUILD_TESTS "Build tests" ON)

set (CMAKE_AUTOMOC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

set (QT_MINIMUM_VERSION "5.6.3")

find_package (Qt5 ${QT_MINIMUM_VERSION} CONFIG REQUIRED Core DBus)

add_subdirectory (libkdeconnect-qt)

if (BUILD_TESTS)
    find_package (Qt5 ${QT_MINIMUM_VERSION} CONFIG REQUIRED Test)
    add_subdirectory (tests)
endif ()

if (BUILD_DDE_DOCK_PLUGIN)
    find_package (Qt5 ${QT_MINIMUM_VERSION} CONFIG REQUIRED Widgets)
    add_subdirectory (kdeconnect-qt)
endif ()
