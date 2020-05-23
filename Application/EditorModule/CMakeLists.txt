set(Qt5_Application_Components Core Widgets Sql REQUIRED)
find_package(Qt5 COMPONENTS ${Qt5_Application_Components})

set(EditorModule_SRC
    EditorModule.cpp
    EditorModule.h
    EditorView.cpp
    EditorView.h
    DrawingView.cpp
    DrawingView.h
    TextEditor.cpp
    TextEditor.h
    Events.cpp
    Events.h
    Logger.cpp
    Logger.h
    )

set(Utils_SRC
    )

set(Misc_SRC
    Constants.cpp
    Constants.h
    )

add_library(EditorModule_static
    ${EditorModule_SRC}
    ${Utils_SRC}
)

target_link_libraries(EditorModule_static
    Qt5::Widgets        # -> Widgets
    Qt5::Core           # -> Core
    Qt5::Sql            # -> Sql
    )


target_include_directories(EditorModule_static
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    )
