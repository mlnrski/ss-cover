cmake_minimum_required(VERSION 3.13)
project(ss_cover)

set(CMAKE_CXX_STANDARD 14)

find_package( PkgConfig REQUIRED)

pkg_search_module( TESSERACT REQUIRED tesseract )

pkg_search_module( LEPTONICA REQUIRED lept )

include_directories( ${TESSERACT_INCLUDE_DIRS} )

include_directories( ${LEPTONICA_INCLUDE_DIRS} )

link_directories( ${TESSERACT_LIBRARY_DIRS} )

link_directories( ${LEPTONICA_LIBRARY_DIRS} )

add_executable(ss_cover main.cpp)

target_link_libraries( ss_cover ${TESSERACT_LIBRARIES} )

target_link_libraries(ss_cover ${LEPTONICA_LIBRARIES} )