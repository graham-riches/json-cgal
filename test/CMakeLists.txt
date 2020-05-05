set(BINARY JsonCGAL_test)
set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd /Zi /Ob0 /Od /RTC1")

find_package(CGAL)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})
add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} CGAL::CGAL)
target_link_libraries(${BINARY} gtest)
target_link_libraries(${BINARY} JsonCGAL_lib)