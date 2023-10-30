set(Qt5_Application_Components Core Widgets REQUIRED)
find_package(Qt5 COMPONENTS ${Qt5_Application_Components})

set(PaintingManager_src
    PaintingManager.cpp
    PaintingManager.h
    ImageController.cpp
    ImageController.h
    RectangleSelectionOperator.cpp
    RectangleSelectionOperator.h
    ShapeOperator.cpp
    ShapeOperator.h
    ShapeSharing.cpp
    ShapeSharing.h
    ImageText.cpp
    ImageText.h
    CommonTypes.h
    )

add_library(PaintingManager_static
    ${PaintingManager_src}
)

target_link_libraries(PaintingManager_static
    Qt5::Widgets        # -> Widgets
    Qt5::Core           # -> Core
    )

target_include_directories(PaintingManager_static
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    )
