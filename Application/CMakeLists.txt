cmake_minimum_required(VERSION 2.8)

# headers included in both[Qt Widgests/Qt QML]
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${QtQml_INCLUDE_DIRS})



add_subdirectory(MainWindow)
add_subdirectory(EditorModule)




set(MainWindow_RES
    Resources/resources.qrc
    )


add_executable(${PROJECT_NAME} WIN32
    # add the RESOURCES
    # RESURSELE doar aici merg
    ${MainWindow_RES}
    main.cpp
    )


target_link_libraries(${PROJECT_NAME} PRIVATE
    MainWindow_static
    EditorModule_static
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
