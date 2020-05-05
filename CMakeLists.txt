cmake_minimum_required(VERSION 3.1...3.15)
project(JsonCGAL)
set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd /Zi /Ob0 /Od /RTC1")


include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(test/googletest)
