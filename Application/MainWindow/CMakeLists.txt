set(Qt5_Application_Components Core Widgets Sql REQUIRED)
find_package(Qt5 COMPONENTS ${Qt5_Application_Components})

set(MainWindow_SRC
    ApplicationWindow.cpp
    ApplicationWindow.h
    WindowContainer.cpp
    WindowContainer.h
    )

add_library(MainWindow_static
    ${MainWindow_SRC}
    )

target_link_libraries(MainWindow_static
    Qt5::Widgets        # -> Widgets
    Qt5::Core           # -> Core
    Qt5::Sql            # -> Sql
    )

target_include_directories(MainWindow_static
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    )

include_directories(EditorModule_static)
