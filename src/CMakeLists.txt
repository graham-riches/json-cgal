set(BINARY JsonCGAL)
set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd /Zi /Ob0 /Od /RTC1")

find_package(CGAL)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false *.h *.cpp)

set(SOURCES ${SOURCES})

add_library(${BINARY} SHARED ${SOURCES})
add_library(${BINARY}_lib STATIC ${SOURCES})

target_link_libraries(${BINARY} CGAL::CGAL ${Boost_LIBRARIES})
target_link_libraries(${BINARY}_lib CGAL::CGAL ${Boost_LIBRARIES})