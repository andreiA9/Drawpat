set(ClientSimulator_SRC
    Constants.h
    ClientSimulator.cpp
    ClientSimulator.h
    Menu.cpp
    Menu.h
    main.cpp
    )

add_executable(ClientSimulator
    ${ClientSimulator_SRC}
    )

# ASTA iti trebuie pentru
# std::variant<>
set_target_properties(ClientSimulator PROPERTIES
    CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    )

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

find_package(Qt5 COMPONENTS Core)

target_link_libraries(ClientSimulator PUBLIC
    Network_static
    Components_static
    Threads::Threads        # pthreads
    )

add_subdirectory(Tests)
