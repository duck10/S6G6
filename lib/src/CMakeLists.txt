cmake_minimum_required(VERSION 3.6)

project(S6G6_lib)

include_directories(../include)

set(PROJECT_SOURCES G6.cpp LatticeConvert.cpp LRL_Cell.cpp LRL_StringTools.cpp MatG6.cpp MatN.cpp Niggli.cpp S6.cpp Selling.cpp VecN.cpp)

add_library(s6g6 PROJECT_SOURCES)

