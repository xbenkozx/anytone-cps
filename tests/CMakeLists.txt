# Headless tests, not part of the default build:
#   cmake -B build -DANYTONE_BUILD_TESTS=ON && cmake --build build --target list-order-test
#   build/tests/list-order-test <codeplug.atd> [...]
find_package(Qt6 REQUIRED COMPONENTS Core SerialPort)

qt_add_executable(list-order-test
    list_order_test.cpp
    ${CMAKE_SOURCE_DIR}/desktop/src/device.cpp
    ${CMAKE_SOURCE_DIR}/desktop/include/device.h
)
set_target_properties(list-order-test PROPERTIES
    CXX_STANDARD 20
    AUTOMOC ON
)
target_include_directories(list-order-test PRIVATE ${CMAKE_SOURCE_DIR}/desktop/include)
target_link_libraries(list-order-test PRIVATE Qt6::Core Qt6::SerialPort anytone-lib)
