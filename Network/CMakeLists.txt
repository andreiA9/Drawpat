set(Qt5_Network_Components Core Network REQUIRED)
find_package(Qt5 COMPONENTS ${Qt5_Network_Components})

set(Network_SRC
    NetworkModule.cpp
    NetworkModule.h
    RestController.cpp
    RestController.h
    HttpClient.cpp
    HttpClient.h
    JsonDeserializer.h
    JsonDeserializer.cpp
    )

add_library(Network_static
    ${Network_SRC}
)

target_link_libraries(Network_static
    Qt5::Core           # -> Core
    Qt5::Network        # -> Network from QT += network
    Components_static
    )

target_include_directories(Network_static
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    )
