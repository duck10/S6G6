#Cmake module to find RcppParallel
# - Try to find RcppParallel
# Once done, this will define
#
#  RCPPPARA_FOUND - system has RcppParallel
#  RCPPPARA_INCLUDE_DIRS - the RcppParallel include directories
#  RCPPPARA_LIBRARIES - link these to use RcppParallel
#Autor: Omar Andres Zapata Mesa 31/05/2013
#
#  Adopted for ncdist package from https://root.cern.ch/
#  because it is covered by the LGPL (and therefore,
#  optionally, the GPL) which are the overall licenses
#  for ncdist.

message(STATUS "Looking for RcppParallel")

find_program ( R_EXECUTABLE
               NAMES R R.exe
              )

execute_process ( COMMAND echo "cat(find.package('RcppParallel'))"
                    COMMAND ${R_EXECUTABLE} --vanilla --slave
                    OUTPUT_VARIABLE RCPPPARA_PATH
                    ERROR_VARIABLE RCPPPARA_PATH_ERR
                    OUTPUT_STRIP_TRAILING_WHITESPACE
                  )
                  
                  

set(RCPPPARA_PKGCONF_LIBRARY_DIRS
	"/usr/local/lib" "/usr/lib" "/usr/local/lib64" "/usr/lib64"
        "/opt/R/site-library/RcppParallel/lib"
        "/usr/lib/R/site-library/RcppParallel/lib"
        "/usr/lib64/R/site-library/RcppParallel/lib"
        "/usr/local/lib/R/site-library/RcppParallel/lib"
        "/usr/local/lib64/R/site-library/RcppParallel/lib"
        "${RCPPPARA_PATH}/libs"
        "/$ENV{HOMEPATH}/Documents/R/win-library/3.6/RcppParallel/lib"
        )

set(RCPPPARA_PKGCONF_INCLUDE_DIRS
	"/usr/local/include" "/usr/include"
        "/opt/R/site-library/RcppParallel/include"
        "/usr/local/lib/R/site-library/RcppParallel/include"
        "/usr/local/lib64/R/site-library/RcppParallel/include"
        "/usr/lib/R/site-library/RcppParallel/include"
        "/usr/lib64/R/site-library/RcppParallel/include"
        "${RCPPPARA_PATH}/include"
        "/$ENV{HOMEPATH}/Documents/R/win-library/3.6/RcppParallel/include"
        )


# Finally the library itself
find_library(RCPPPARA_LIBRARY
  NAMES libRcppParallel.a libRcppParallel.so  libRcppParallel.lib RcppParallel.so libRcppParallel.dll RcppParallel.dll RcppParallel.dylib libRcppParallel.dylib
  PATHS ${RCPPPARA_PKGCONF_LIBRARY_DIRS}
)

# find the path with the include file
find_path(RCPPPARA_INCLUDE_DIR "RcppParallel.h"
  PATHS ${RCPPPARA_PKGCONF_INCLUDE_DIRS}
  PATH_SUFFIXES include /)

MESSAGE(STATUS "RCPPPARA_INCLUDE_DIR=${RCPPPARA_INCLUDE_DIR}")
MESSAGE(STATUS "RCPPPARA_LIBRARY=${RCPPPARA_LIBRARY}")

# Setting up the results 
set(RCPPPARA_INCLUDE_DIRS ${RCPPPARA_INCLUDE_DIR} )
set(RCPPPARA_LIBRARIES ${RCPPPARA_LIBRARY})
if (("${RCPPPARA_INCLUDE_DIR}" STREQUAL "") OR ("${RCPPPARA_LIBRARY}" STREQUAL ""))
  set(RCPPPARA_FOUND FALSE)
  message(STATUS "Looking for RcppParallel -- not found ")
  message(STATUS "Install it running 'R -e \"install.packages(\\\"RcppParallel\\\",repos=\\\"http://cran.irsn.fr/\\\")\"'")
else()
  set(RCPPPARA_FOUND TRUE)
  message(STATUS "Looking for RcppParallel -- found")
endif()
