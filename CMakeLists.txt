cmake_minimum_required(VERSION 3.16...3.27)
# The version number is written in one place only: the file VERSION. CMake reads it here, the
# application gets it as a compile definition (anytone-lib/CMakeLists.txt) and the About window
# shows it together with CHANGELOG.md, whose first release heading must carry the same number.
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" ANYTONE_CPS_VERSION LIMIT_COUNT 1)
if(NOT ANYTONE_CPS_VERSION MATCHES "^[0-9]+\\.[0-9]+\\.[0-9]+$")
  message(FATAL_ERROR "VERSION must contain MAJOR.MINOR.PATCH, found '${ANYTONE_CPS_VERSION}'")
endif()
project(anytone-cps VERSION ${ANYTONE_CPS_VERSION} LANGUAGES CXX)
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" "${CMAKE_CURRENT_SOURCE_DIR}/CHANGELOG.md")
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/CHANGELOG.md" _changelog_headings
  REGEX "^## \\[[0-9]+\\.[0-9]+\\.[0-9]+\\]" LIMIT_COUNT 1)
string(REGEX REPLACE "^## \\[([0-9]+\\.[0-9]+\\.[0-9]+)\\].*$" "\\1" _changelog_version "${_changelog_headings}")
if(NOT _changelog_version STREQUAL ANYTONE_CPS_VERSION)
  message(FATAL_ERROR "Version mismatch: VERSION says ${ANYTONE_CPS_VERSION}, the first release heading "
                      "of CHANGELOG.md says '${_changelog_version}'. Update both together.")
endif()

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

option(ANYTONE_BUILD_TESTS "Build the headless tests in tests/" OFF)
if(ANYTONE_BUILD_TESTS)
  add_subdirectory(tests)
endif()

# DEBUG cmake -B build; cmake --build build;
# RELEASE cmake -B build; cmake --build build --config Release;
