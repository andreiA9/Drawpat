
set(TEST_SRC
    DrawingViewTests.cpp
    DrawingViewTests.h)

add_executable(DrawingViewTests ${TEST_SRC})
add_test(NAME DrawingViewTests COMMAND DrawingViewTests)

find_package(Qt5Test REQUIRED)

target_link_libraries(DrawingViewTests
    Qt5::Test
    EditorModule_static)


#set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(CMAKE_AUTOMOC ON)
