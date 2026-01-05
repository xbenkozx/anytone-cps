cmake_minimum_required(VERSION 3.16...3.27)
project(anytone-cps LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

IF (WIN32)
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.1/msvc2022_64/lib/cmake")
ELSE()
set(CMAKE_PREFIX_PATH "$ENV{QT_GCC_DIR}/lib/cmake")
ENDIF()

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets SerialPort Multimedia)

set(CMAKE_AUTOUIC_SEARCH_PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui
)

file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/include/*.h"
)

qt_standard_project_setup()

qt_add_executable(anytone-cps
    anytone-cps.cpp
    ${SOURCES}
    resources.qrc
)

# Or conditionally
IF (WIN32)
    set_property(TARGET anytone-cps PROPERTY WIN32_EXECUTABLE TRUE)
endif()

target_include_directories(anytone-cps PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/ui
    ${CMAKE_SOURCE_DIR}/include/memory
    ${CMAKE_SOURCE_DIR}/include/table_model
)

target_link_libraries(anytone-cps PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::SerialPort
    Qt6::Multimedia
)

find_program(WINDEPLOYQT_BIN windeployqt.exe HINTS "C:/Qt/6.9.1/msvc2022_64/bin")

IF (WIN32)
    if(WINDEPLOYQT_BIN)
        add_custom_command(
            TARGET anytone-cps
            POST_BUILD
            COMMAND ${WINDEPLOYQT_BIN} --pdb $<TARGET_FILE:anytone-cps>
            WORKING_DIRECTORY $<TARGET_FILE_DIR:anytone-cps>
            COMMENT "Running windeployqt on anytone-cps executable..."
        )
    endif()
endif()
# DEBUG cmake -B build; cmake --build build;
# RELEASE cmake -B build; cmake --build build --config Release;