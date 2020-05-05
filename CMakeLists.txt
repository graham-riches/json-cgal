cmake_minimum_required(VERSION 3.1...3.15)
set(BINARY JsonCGAL)
project(JsonCGAL)

include_directories(src)

set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd /Zi /Ob0 /Od /RTC1")

find_package(CGAL REQUIRED)
add_subdirectory(test)
add_subdirectory(test/googletest)


file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

add_library(${BINARY} STATIC ${SOURCES})

target_link_libraries(${BINARY} CGAL::CGAL)
target_link_libraries(${BINARY} gtest)
