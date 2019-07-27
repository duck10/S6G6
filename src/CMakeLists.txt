cmake_minimum_required(VERSION 3.6)
project(S6G6)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
find_package(R REQUIRED)
find_package(Rcpp REQUIRED)
find_package(RcppArmadillo REQUIRED)
find_package(RcppParallel)

find_package(OpenMP)
if (OPENMP_FOUND)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

find_package( Threads )

message(&{${CMAKE_SOURCE_DIR}})
message(&{${R_INCLUDE_DIRS}})
message(&{${RCPP_INCLUDE_DIRS}})
message(&{${RCPPARMA_INCLUDE_DIRS}})
message(&{${RCPPPARA_INCLUDE_DIRS}})
include_directories("${CMAKE_SOURCE_DIR}" )
include_directories("${R_INCLUDE_DIRS}" )
include_directories("${RCPP_INCLUDE_DIRS}" )
include_directories("${RCPPARMA_INCLUDE_DIRS}" )
include_directories("${RCPPPARA_INCLUDE_DIRS}")

include_directories(../include)

set(PROJECT_SOURCES G6.cpp LatticeConverter.cpp LRL_Cell.cpp LRL_StringTools.cpp
MatG6.cpp MatN.cpp Niggli.cpp S6.cpp Selling.cpp VecN.cpp)

add_library(s6g6 SHARED ${PROJECT_SOURCES})

include_directories(../../test/include "${CMAKE_SOURCE_DIR}" "${R_INCLUDE_DIRS}"
"${RCPP_INCLUDE_DIRS}" "${RCPPARMA_INCLUDE_DIRS}" "${RCPPPARA_INCLUDE_DIRS}")


set(TEST_SOURCES CellInputData.cpp LRL_ReadLatticeData.cpp S6G6_test.cpp)

add_executable(s6g6_test ${TEST_SOURCES} )

target_link_libraries(s6g6_test s6g6)

set(RCPP_DISTANCE_SOURCES Rcpp_distance.cpp)

add_library(Rcpp_distance SHARED  ${RCPP_DISTANCE_SOURCES} )

target_link_libraries(Rcpp_distance s6g6)
