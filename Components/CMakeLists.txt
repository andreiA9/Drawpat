set(Qt5_Application_Components Core Widgets Sql REQUIRED)
find_package(Qt5 COMPONENTS ${Qt5_Application_Components})

set(Components_SRC
    DocumentContainer.cpp
    DocumentContainer.h
    ResourceManipulation.cpp
    ResourceManipulation.h
    CompaniesWrapper.cpp
    CompaniesWrapper.h
    Company.cpp
    Company.h
    ProgrammersWrapper.cpp
    Programmer.cpp
    ProgrammersWrapper.h
    Programmer.h
    )

add_library(Components_static
    ${Components_SRC}
    )

target_link_libraries(Components_static
    Qt5::Widgets        # -> Widgets
    Qt5::Core           # -> Core
    Qt5::Sql            # -> Sql
    )

target_include_directories(Components_static
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

