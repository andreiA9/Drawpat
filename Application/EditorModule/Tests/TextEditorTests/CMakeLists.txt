
set(TEST_SRC
    TextEditorTests.cpp
    TextEditorTests.h)

add_executable(TextEditorTests ${TEST_SRC})
add_test(NAME TextEditorTests COMMAND TextEditorTests)

find_package(Qt5Test REQUIRED)

target_link_libraries(TextEditorTests PRIVATE
    Qt5::Test
    EditorModule_static)
