cmake_minimum_required(VERSION 3.23)

project(Arduino-Library-DS1881_2 LANGUAGES C CXX ASM)

add_library(arduino_DS1881_2 STATIC
  ${CMAKE_CURRENT_LIST_DIR}/src/MaximDS.cpp
)

target_include_directories(arduino_DS1881_2
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/src
)



