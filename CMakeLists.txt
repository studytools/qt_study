cmake_minimum_required(VERSION 2.8.11)

set(HSPRJ_NAME "qt_study")
project(${HSPRJ_NAME})

include_directories("include")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

add_subdirectory("source")

