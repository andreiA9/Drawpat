cmake_minimum_required(VERSION 3.19)

# numele PROIECTULUI
set(PROJECT_NAME Drawpat)
project(${PROJECT_NAME})


# INSTRUCT CMake to call COMPILER=MOC automatically
set(CMAKE_AUTOMOC ON)
# NU SE stie de ce ai adaugat o
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)


add_subdirectory(ApplicationWindow)
add_subdirectory(EditorModule)
add_subdirectory(PaintingManager)
add_subdirectory(Components)
add_subdirectory(Network)
add_subdirectory(ClientSimulator)
