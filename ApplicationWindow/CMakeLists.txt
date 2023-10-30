find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# headers included in both[Qt Widgests/Qt QML]
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${QtQml_INCLUDE_DIRS})

# this will alllow INDEXING of RESOURCES=icons
set(CMAKE_AUTORCC ON)

# INSTRUCT CMake to call COMPILER=MOC automatically
set(CMAKE_AUTOMOC ON)

set(ApplicationWindow_res
    Resources/resources.qrc
    )

set(ApplicationWindow_src
    ApplicationWindow.cpp
    ApplicationWindow.h
    WindowContainer.cpp
    WindowContainer.h
    main.cpp
    )

add_executable(${PROJECT_NAME}
    # add the RESOURCES
    # RESURSELE doar aici merg
    ${ApplicationWindow_res}
    ${ApplicationWindow_src}
    )

target_link_libraries(${PROJECT_NAME} PUBLIC
    EditorModule_static
    Qt5::Widgets        # -> Widgets
    Qt5::Core           # -> Core
    )


install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Resources/Images
    DESTINATION ${PROJECT_BINARY_DIR}/ApplicationWindow/
    )


# expose values to c++ files
set(PROJECT_VERSION 1.0)
set(PROJECT_BUNDLE_NAME AppName)
target_compile_definitions(${PROJECT_NAME} PRIVATE
        CMAKE_DEF_PROJECT_VERSION="${PROJECT_VERSION}"
        CMAKE_DEF_APP_NAME="${PROJECT_BUNDLE_NAME}"
)
