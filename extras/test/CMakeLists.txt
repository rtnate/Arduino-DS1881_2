cmake_minimum_required(VERSION 3.23)

project(arduino_DS1881_2-Tests)

include(${CMAKE_CURRENT_LIST_DIR}/ArduinoLibTesting/rt_arduino_test.cmake)

enable_testing()


rt_create_test_suite(arduino_DS1881_2-tests
        ${CMAKE_CURRENT_LIST_DIR}/tests/UnitTests.cpp
)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../../ libDS1881_2)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/ArduinoLibTesting/MockArduino)

target_link_libraries(arduino_DS1881_2 PUBLIC arduino_MockCore)
target_include_directories(arduino_DS1881_2 PUBLIC ${CMAKE_CURRENT_LIST_DIR}/fakes)
target_link_libraries(arduino_DS1881_2-tests PUBLIC arduino_DS1881_2)

include(GoogleTest)
gtest_discover_tests(arduino_DS1881_2-tests)


