
set(TEST_SRC
    EventsTests.cpp
    EventsTests.h)

add_executable(EventsTexts ${TEST_SRC})
add_test(NAME EventsTexts COMMAND EventsTexts)

find_package(Qt5Test REQUIRED)

target_link_libraries(EventsTexts PRIVATE
    Qt5::Test
    EditorModule_static)

