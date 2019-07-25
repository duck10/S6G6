cmake_minimum_required(VERSION 3.6)

project(S6G6_lib)

include_directories(${CMAKE_SOURCE_DIR}/inc)

set(PROJECT_SOURCES G6.cpp LatticeConvert.cpp LRL_Cell.cpp LRL_StringTools.cpp MatG6.cpp MatN.cpp Niggli.cpp S6.cpp Selling.cpp VecN.cpp)

add_executable( prog main.cpp ${PROJECT_SOURCES} )

