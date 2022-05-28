set(Qt5_Network_Components Core Network REQUIRED)
find_package(Qt5 COMPONENTS ${Qt5_Network_Components})

set(HttpClientModule_SRC
    HttpClientModule/NetworkModule.cpp
    HttpClientModule/NetworkModule.h
    HttpClientModule/HttpClient.cpp
    HttpClientModule/HttpClient.h
    HttpClientModule/RestController.cpp
    HttpClientModule/RestController.h
    HttpClientModule/NetworkModule.h
    HttpClientModule/JsonDeserializer.cpp
    HttpClientModule/JsonDeserializer.h
    )

set(ResourceManipulationModule_SRC
    ResourceManipulationModule/CompaniesWrapper.cpp
    ResourceManipulationModule/CompaniesWrapper.h
    ResourceManipulationModule/Company.cpp
    ResourceManipulationModule/Company.h
    ResourceManipulationModule/ProgrammersWrapper.cpp
    ResourceManipulationModule/ProgrammersWrapper.h
    ResourceManipulationModule/Programmer.cpp
    ResourceManipulationModule/Programmer.h
    )


add_library(NetworkModule_static
    ${HttpClientModule_SRC}
    ${ResourceManipulationModule_SRC}
)

target_link_libraries(NetworkModule_static
    Qt5::Core           # -> Core
    Qt5::Network        # -> Network from QT += network
    )

target_include_directories(NetworkModule_static
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    )
