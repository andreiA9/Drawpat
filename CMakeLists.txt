cmake_minimum_required(VERSION 2.8)

# numele PROIECTULUI
set(PROJECT_NAME Drawpat)
project(${PROJECT_NAME})


# Test for supported Qt version
set(QT_MINIMUM_VERSION 5.9.0)
find_program(QMAKE_EXECUTABLE NAMES qmake HINTS ${QTDIR} ENV QTDIR PATH_SUFFIXES bin)
execute_process(COMMAND ${QMAKE_EXECUTABLE} -query QT_VERSION OUTPUT_VARIABLE QT_VERSION)
if(QT_VERSION VERSION_LESS QT_MINIMUM_VERSION)
        MESSAGE(FATAL_ERROR "Minimum supported Qt version: ${QT_MINIMUM_VERSION}. Installed version: ${QT_VERSION}")
endif()


# INSTRUCT CMake to call COMPILER=MOC automatically
set(CMAKE_AUTOMOC ON)
# this will alllow INDEXING of RESOURCES=icons
# NU ESTE NEVOIE de asta daca ai
# qt5_add_resources()
set(CMAKE_AUTORCC ON)
# NU SE stie de ce ai adaugat o
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)


#if(CMAKE_COMPILER_IS_GNUCXX)
    set(COMPANY_MANAGEMENT_MAJOR 0)
    set(COMPANY_MANAGEMENT_MINOR 1)
    set(COMPANY_MANAGEMENT_MICRO 1)
    set(COMPANY_MANAGEMENT_VERSION ${COMPANY_MANAGEMENT_MAJOR}.${COMPANY_MANAGEMENT_MINOR}.${COMPANY_MANAGEMENT_MICRO})
    # this message is only shown when running CMAKE for the project from the BEGINNING
    message(STATUS "Using CompanyManagement version: ${COMPANY_MANAGEMENT_VERSION}")
#endif(CMAKE_COMPILER_IS_GNUCXX)
#else()
#        message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")





add_subdirectory(Application)
add_subdirectory(Network)



# NOT WORKING
# ENVIRONMENT VARIABLE for
# qgetenv()
set_property(DIRECTORY APPEND PROPERTY
    $<APPLICATION_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}">
    )

#set(IpoLogMfFileName "IPO.Log_4_MF")
#set(RICHCLIENT_INSTALL_DESTINATION ${IpoLogMfFileName} CACHE STRING "The richclient install destination")
#set(IPO_INSTALL_DESTINATION ${RICHCLIENT_INSTALL_DESTINATION} CACHE STRING "The default install destination")
# SET(INSTALL_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/bin/$<CONFIG>)




# ASTEA nu fac altceva deca sa iti adauge HEADER ELE si CPP urile la gramada

# nu ai inteles < EXPLICATIA pentru aceste NOT DEFINED
# There are also conditional commands in CMake. The code below detects if there are HEADERS in the project.
# If header files were not previously set, the file(GLOB ... *.h) command creates a list of all header files
# in the current directory and passes them as header files of the current project. The same applies to the
# *.cpp sources that are stored in the SOURCES variable if that was not defined.

#if(NOT DEFINED HEADERS)
#    file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}⁄*.h)
#endif()
#if(NOT DEFINED SOURCES)
#    file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}⁄*.cpp)
#endif()

## nu ai inteles < EXPLICATIA pentru aceste source_group
## The source_group definition creates a group of files that are placed in some build systems (e.g. project
## sub-directories in Visual Studio).
#source_group("Header Files" FILES ${HEADERS})
#source_group("Source Files" FILES ${SOURCES})

##qt5_add_resources(QT_RESOURCES qml.qrc)

#add_executable(${PROJECT} ${HEADERS} ${SOURCES} ${QT_RESOURCES})
