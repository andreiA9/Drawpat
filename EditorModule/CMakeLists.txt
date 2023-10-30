set(Qt5_Application_Components Core Widgets REQUIRED)
find_package(Qt5 COMPONENTS ${Qt5_Application_Components})

set(EditorModule_SRC
    EditorModule.cpp
    EditorModule.h
    EditorView.cpp
    EditorView.h
    ImageEditor.cpp
    ImageEditor.h
    TextEditor.cpp
    TextEditor.h
    Events.cpp
    Events.h
    Logger.cpp
    Logger.h
    )

add_library(EditorModule_static
    ${EditorModule_SRC}
)

target_link_libraries(EditorModule_static
    Qt5::Widgets        # -> Widgets
    Qt5::Core           # -> Core
    PaintingManager_static
    Components_static
    )

target_include_directories(EditorModule_static
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    )
