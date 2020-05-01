cmake_minimum_required(VERSION 2.8)

# headers included in both[Qt Widgests/Qt QML]
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${QtQml_INCLUDE_DIRS})
# this will alllow INDEXING of RESOURCES=icons
# NU ESTE NEVOIE de asta daca ai
# qt5_add_resources()
set (CMAKE_AUTORCC ON)



set(MainWindow_SRC
    MainWindow/ApplicationWindow.cpp
    MainWindow/ApplicationWindow.h
    MainWindow/WindowContainer.cpp
    MainWindow/WindowContainer.h
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

set(MainWindow_RES
    Resources/resources.qrc
    )

set(Utils_SRC
    )

set(Misc_SRC
    Constants.cpp
    Constants.h
    )


add_library(MainWindowLib_static
    ${MainWindow_SRC}
    # add the CPP FILES
    ${EditorModule_SRC}
    ${Utils_SRC}
#    ${Misc_SRC}
    )


target_link_libraries(MainWindowLib_static
    Qt5::Widgets        # -> Widgets
    Qt5::Core           # -> Core
    Qt5::Sql            # -> Sql
    )


add_executable(${PROJECT_NAME} WIN32
    # add the RESOURCES
    # RESURSELE doar aici merg
    ${MainWindow_RES}
    main.cpp
    )


target_link_libraries(${PROJECT_NAME} PRIVATE
    MainWindowLib_static
    )


install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Resources/Images
    DESTINATION ${PROJECT_BINARY_DIR}/Application/
    )


# expose values to c++ files
set(PROJECT_VERSION 1.0)
set(PROJECT_BUNDLE_NAME AppName)
target_compile_definitions(${PROJECT_NAME} PRIVATE
        CMAKE_DEF_PROJECT_VERSION="${PROJECT_VERSION}"
        CMAKE_DEF_APP_NAME="${PROJECT_BUNDLE_NAME}"
)
