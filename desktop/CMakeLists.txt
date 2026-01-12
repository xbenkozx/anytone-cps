

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets SerialPort Multimedia)

set(CMAKE_AUTOUIC_SEARCH_PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui
)

file(GLOB_RECURSE DESKTOP_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
file(GLOB_RECURSE DESKTOP_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)
qt_standard_project_setup()

qt_add_executable(anytone-cps
    anytone-cps.cpp
    ${DESKTOP_SOURCES}
    ${DESKTOP_HEADERS}
    resources.qrc
)

# Or conditionally
IF (WIN32)
    #set_property(TARGET anytone-cps PROPERTY WIN32_EXECUTABLE TRUE)
endif()


set_target_properties(anytone-cps PROPERTIES 
    CXX_STANDARD 20
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

target_include_directories(anytone-cps PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ui
    ${CMAKE_CURRENT_SOURCE_DIR}/include/table_model
)

target_link_libraries(anytone-cps PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::SerialPort
    Qt6::Multimedia
    anytone-lib
)

find_program(WINDEPLOYQT_BIN windeployqt.exe HINTS "C:/Qt/6.10.1/msvc2022_64/bin")

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