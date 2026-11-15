

file(GLOB_RECURSE LIBSOURCES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
file(GLOB_RECURSE LIBHEADERS CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)

find_package(Qt6 REQUIRED COMPONENTS Core SerialPort)

qt_add_library(anytone-lib STATIC ${LIBSOURCES} ${LIBHEADERS})

set_target_properties(anytone-lib PROPERTIES
  CXX_STANDARD 20
  AUTOMOC ON
  AUTOUIC ON
  AUTORCC ON
)

# Version shown by the application, taken from the VERSION file (see the top level CMakeLists.txt)
target_compile_definitions(anytone-lib PRIVATE ANYTONE_CPS_VERSION="${ANYTONE_CPS_VERSION}")

target_include_directories(anytone-lib
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/memory"
)


target_link_libraries(anytone-lib PUBLIC 
    Qt6::Core 
    Qt6::SerialPort
)