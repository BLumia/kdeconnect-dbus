option (BUILD_TEST_EXECUTABLE "Build test executable program" ON)

set (KCDDE_CPP_FILES
    devicelistwindow.cpp
    devicewidget.cpp
    notificationitemdelegate.cpp
    devicemanager.cpp
    batterywidget.cpp
)

set (KCDDE_HEADER_FILES
    devicelistwindow.h
    devicewidget.h
    notificationitemdelegate.h
    devicemanager.h
    batterywidget.h
)

if (BUILD_TEST_EXECUTABLE)
    add_executable (tst_gui
        executable_main.cpp
        ${KCDDE_HEADER_FILES}
        ${KCDDE_CPP_FILES}
    )
    target_link_libraries (tst_gui kdeconnect-qt Qt5::Widgets)
endif ()
