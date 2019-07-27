#Cmake module to find R 
# - Try to find R
# Once done, this will define
#
#  R_FOUND - system has R
#  R_INCLUDE_DIRS - the R include directories
#  R_LIBRARIES - link these to use R
#Autor: Omar Andres Zapata Mesa 31/05/2013
#
#  Adopted for ncdist package from https://root.cern.ch/
#  because it is covered by the LGPL (and therefore,
#  optionally, the GPL) which are the overall licenses
#  for ncdist.


message(STATUS "Looking for R")

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_FIND_APPBUNDLE "LAST")
endif()

find_program ( R_EXECUTABLE
               NAMES R R.exe
              )

MESSAGE(STATUS "R_EXECUTABLE=${R_EXECUTABLE}")

execute_process ( COMMAND echo "cat(Sys.getenv(\"R_HOME\"))"
                    COMMAND ${R_EXECUTABLE} --vanilla --slave
                    OUTPUT_VARIABLE R_HOME
                    ERROR_VARIABLE R_HOME_ERR
                    OUTPUT_STRIP_TRAILING_WHITESPACE
                  )

set(R_PKGCONF_LIBRARY_DIRS
        "${R_HOME}/lib"
        "/usr/local/lib" "/usr/lib" "/usr/local/lib64" "/usr/lib64"
        )

set(R_PKGCONF_INCLUDE_DIRS
        "${R_HOME}/include"
        "/usr/local/include" "/usr/include" "/usr/share/R/include"
		"/Program Files/R/R-3.6.1/include"
        )

# Finf the R, Rblas and Rlapack libraries
find_library(R_LIBRARY
  NAMES libR.a libR.so  libR.lib R.so libR.dll R.dll R.dylib libR.dylib
  PATHS ${R_PKGCONF_LIBRARY_DIRS}
)

find_library(RBLAS_LIBRARY
NAMES  libRblas.a libRblas.so  libRblas.lib
       Rblas.so libRblas.dll Rblas.dll
       Rblas.dylib libRblas.dylib
       libblas.a libblas.so  libblas.lib
       blas.so libblas.dll blas.dll
       blas.dylib libblas.dylib
PATHS ${R_PKGCONF_LIBRARY_DIRS}
)

find_library(RLAPACK_LIBRARY
NAMES  libRlapack.a libRlapack.so  libRlapack.lib
       Rlapack.so libRlapack.dll Rlapack.dll
       Rlapack.dylib libRlapack.dylib
       liblapack.a liblapack.so  liblapack.lib
       lapack.so liblapack.dll lapack.dll
       lapack.dylib liblapack.dylib
PATHS ${R_PKGCONF_LIBRARY_DIRS}
)

# find the path with the include file
find_path(R_INCLUDE_DIR "R.h"
  PATHS ${R_PKGCONF_INCLUDE_DIRS}
)

MESSAGE(STATUS "R_HOME=${R_HOME}")
MESSAGE(STATUS "R_INCLUDE_DIR=${R_INCLUDE_DIR}")
MESSAGE(STATUS "R_LIBRARY=${R_LIBRARY}")
MESSAGE(STATUS "RBLAS_LIBRARY=${RBLAS_LIBRARY}")
MESSAGE(STATUS "RLAPACK_LIBRARY=${RLAPACK_LIBRARY}")


# Setting up the results 
set(R_INCLUDE_DIRS ${R_INCLUDE_DIR})
set(R_LIBRARIES ${R_LIBRARY})
if (("${R_INCLUDE_DIR}" STREQUAL "") OR ("${R_LIBRARY}" STREQUAL ""))
  set(R_FOUND FALSE)
  message(STATUS "Looking for R -- not found ")
else()
  set(R_FOUND TRUE)
  message(STATUS "Looking for R -- found")
endif()
