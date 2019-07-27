#Cmake module to find RcppArmadillo
# - Try to find RcppArmadillo
# Once done, this will define
#
#  RCPPARMA_FOUND - system has RcppArmadillo
#  RCPPARMA_INCLUDE_DIRS - the RcppArmadillo include directories
#  RCPPARMA_LIBRARIES - link these to use RcppArmadillo
#Autor: Omar Andres Zapata Mesa 31/05/2013
#
#  Adopted for ncdist package from https://root.cern.ch/
#  because it is covered by the LGPL (and therefore,
#  optionally, the GPL) which are the overall licenses
#  for ncdist.

message(STATUS "Looking for RcppArmadillo")

find_program ( R_EXECUTABLE
               NAMES R R.exe
              )

execute_process ( COMMAND echo "cat(find.package('RcppArmadillo'))"
                    COMMAND ${R_EXECUTABLE} --vanilla --slave
                    OUTPUT_VARIABLE RCPPARMA_PATH
                    ERROR_VARIABLE RCPPARMA_PATH_ERR
                    OUTPUT_STRIP_TRAILING_WHITESPACE
                  )

MESSAGE(STATUS "RCPPARMA_PATH=${RCPPARMA_PATH}")

set(RCPPARMA_PKGCONF_LIBRARY_DIRS
	"/usr/local/lib" "/usr/lib" "/usr/local/lib64" "/usr/lib64"
        "/opt/R/site-library/RcppArmadillo/lib"
        "/usr/local/lib/R/site-library/RcppArmadillo/lib"
        "/usr/local/lib64/R/site-library/RcppArmadillo/lib"
        "/usr/lib/R/site-library/RcppArmadillo/lib"
        "/usr/lib64/R/site-library/RcppArmadillo/lib"
        "${RCPPARMA_PATH}/libs"
        "/$ENV{HOMEPATH}/Documents/R/win-library/3.6/RcppArmadillo/lib"
        )

set(RCPPARMA_PKGCONF_INCLUDE_DIRS
	"/usr/local/include" "/usr/include"
        "/opt/R/site-library/RcppArmadillo/include"
        "/usr/local/lib/R/site-library/RcppArmadillo/include"
        "/usr/local/lib64/R/site-library/RcppArmadillo/include"
        "/usr/lib/R/site-library/RcppArmadillo/include"
        "/usr/lib64/R/site-library/RcppArmadillo/include"
        "${RCPPARMA_PATH}/include"
        "/$ENV{HOMEPATH}/Documents/R/win-library/3.6/RcppArmadillo/include"
        )


# Finally the library itself
find_library(RCPPARMA_LIBRARY
  NAMES libRcppArmadillo.a libRcppArmadillo.so  libRcppArmadillo.lib RcppArmadillo.so libRcppArmadillo.dll RcppArmadillo.dll RcppArmadillo.dylib libRcppArmadillo.dylib
  PATHS ${RCPPARMA_PKGCONF_LIBRARY_DIRS}
)

# find the path with the include file
find_path(RCPPARMA_INCLUDE_DIR "RcppArmadillo.h"
  PATHS ${RCPPARMA_PKGCONF_INCLUDE_DIRS}
)

MESSAGE(STATUS "RCPPARMA_INCLUDE_DIR=${RCPPARMA_INCLUDE_DIR}")
MESSAGE(STATUS "RCPPARMA_LIBRARY=${RCPPARMA_LIBRARY}")

# Setting up the results 
set(RCPPARMA_INCLUDE_DIRS ${RCPPARMA_INCLUDE_DIR})
set(RCPPARMA_LIBRARIES ${RCPPARMA_LIBRARY})
if (("${RCPPARMA_INCLUDE_DIR}" STREQUAL "") OR ("${RCPPARMA_LIBRARY}" STREQUAL ""))
  set(RCPPARMA_FOUND FALSE)
  message(STATUS "Looking for RcppArmadillo -- not found ")
  message(STATUS "Install it running 'R -e \"install.packages(\\\"RcppArmadillo\\\",repos=\\\"http://cran.irsn.fr/\\\")\"'")
else()
  set(RCPPARMA_FOUND TRUE)
  message(STATUS "Looking for RcppArmadillo -- found")
endif()
