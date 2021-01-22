cmake_minimum_required(VERSION 3.0.0)
project(delaunay VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(delaunay Delaunay.cpp)

target_include_directories(delaunay
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
