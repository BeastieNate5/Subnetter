cmake_minimum_required(VERSION 2.6.0)
project(subnetter C)

add_executable(${CMAKE_PROJECT_NAME} subnetter.c)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
else()
target_link_libraries(${CMAKE_PROJECT_NAME} m)
endif()
