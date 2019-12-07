cmake_minimum_required (VERSION 3.12.4)

set_source_files_properties (org.kde.kdeconnect.device.xml
PROPERTIES
    NO_NAMESPACE ON
)

# https://doc.qt.io/qt-5/qtdbus-cmake-qt5-add-dbus-interface.html
qt5_add_dbus_interface (KCLIB_DBUS_GEN_FILES org.kde.kdeconnect.daemon.xml daemon_interface)
qt5_add_dbus_interface (KCLIB_DBUS_GEN_FILES org.kde.kdeconnect.device.xml device_interface)

set (KCLIB_PUBLIC_HEADER_FILES
    kcmanager.h
    kcdevice.h
)

set (KCLIB_PRIVATE_HEADER_FILES
    kcdbuscommon.h
)

set (KCLIB_PRIVATE_CPP_FILES
    kcmanager.cpp
    kcdevice.cpp
)

add_library (kdeconnect-qt
    ${KCLIB_DBUS_GEN_FILES}
    ${KCLIB_PUBLIC_HEADER_FILES}
    ${KCLIB_PRIVATE_HEADER_FILES}
    ${KCLIB_PRIVATE_CPP_FILES}
)

target_include_directories (kdeconnect-qt
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries (kdeconnect-qt Qt5::Core Qt5::DBus)
