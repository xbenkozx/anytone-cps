cmake_minimum_required(VERSION 3.16...3.27)
project(anytone-cps VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

IF (WIN32)
set(CMAKE_PREFIX_PATH "C:/Qt/6.10.2/msvc2022_64/lib/cmake")
ELSE()
set(CMAKE_PREFIX_PATH "$ENV{QT_GCC_DIR}/lib/cmake")
ENDIF()

add_subdirectory(anytone-lib)
add_subdirectory(desktop)

# DEBUG cmake -B build; cmake --build build;
# RELEASE cmake -B build; cmake --build build --config Release;
