cmake_minimum_required(VERSION 2.8)

# headers included in both[Qt Widgests/Qt QML]
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${QtQml_INCLUDE_DIRS})

set(MainWindow_SRC
    MainWindow/ApplicationWindow.cpp
    MainWindow/ApplicationWindow.h
    MainWindow/MainLayout.cpp
    MainWindow/MainLayout.h
    MainWindow/CentralWidget.cpp
    MainWindow/CentralWidget.h
    )

set(EditorModule_SRC
    EditorModule/EditorModule.cpp
    EditorModule/EditorModule.h
    EditorModule/EditorView.cpp
    EditorModule/EditorView.h
    EditorModule/DrawingView.cpp
    EditorModule/DrawingView.h
    EditorModule/TextEditor.cpp
    EditorModule/TextEditor.h
    EditorModule/Events.cpp
    EditorModule/Events.h
    )

set(Utils_SRC
    )

set(Misc_SRC
    Constants.cpp
    Constants.h
    )

# ADD new FILE
# file(TOUCH Qml/TabButton.qml)
# RENAME
# file(RENAME Qml/TabButton.qml Qml/TabButtonBackground.qml)


add_executable(Drawpat WIN32
    main.cpp
    )


# !!!!!!!!!!!!!! NOT USED
# Telling CMake location of our app .qrc file
# ${CMAKE_CURRENT_SOURCE_DIR} = full path to the source directory that is currently being processed by cmake
#qt5_add_resources(APP_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/qml.qrc)

add_library(MainWindowLib_static
    ${MainWindow_SRC}
    # add the CPP FILES
    ${EditorModule_SRC}
    ${Utils_SRC}
#    ${Misc_SRC}
    # add the RESOURCES
    ${APP_RESOURCES}
    )

# this will be shown only if the CMakeLists.txt is present inside FOLDER = MainWindow
#add_subdirectory(UiComponent)



target_link_libraries(MainWindowLib_static
    Qt5::Widgets        # -> Widgets
    Qt5::Core           # -> Core
    Qt5::Sql            # -> Sql
    )


# AICI vei gasi MODULELE
# < pentru a le adauga mai sus
# http://doc.qt.io/qt-5/qtmodules.html

# link the EXECUTABLE to the main LIBRARY
# < this was you will also have the [ Qt5::QuickWidgets / Qt5::Quick / Qt5::Qml]
# for #include<QQmlApplicationEngine>

target_link_libraries(Drawpat PRIVATE
    MainWindowLib_static
    )
