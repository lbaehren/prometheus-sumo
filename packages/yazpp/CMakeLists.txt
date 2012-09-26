
## ==============================================================================
##
##  CMake project settings
##
## ==============================================================================

# YAZ++ is an application programming interface (API) to YAZ which supports
# the development of Z39.50/SRW/SRU client and server applications using C++.
# Like YAZ, it supports Z39.50-2003 (version 3) as well as SRW/SRU version 1.1
# in both the client and server roles. YAZ++ includes an implementation of the
# ZOOM C++ binding and a generic client/server API based on the Observer/Observable
# design pattern.

## Name of the project handled by CMake
project (YAZPP)

## Minimum required version of CMake to configure the project
cmake_minimum_required (VERSION 2.8)

## Enforced CMake policy
cmake_policy (VERSION 2.8)

##  Package information
set (YAZPP_VERSION        "1.3.2" )
set (YAZPP_SOURCE_ARCHIVE "yazpp-${YAZPP_VERSION}.tar.gz" )
set (YAZPP_URL            "http://ftp.indexdata.dk/pub/yazpp/${YAZPP_SOURCE_ARCHIVE}" )
set (YAZPP_SVN            "" )

## ==============================================================================
##
##  Options
##
## ==============================================================================

option (YAZPP_FORCE_BUILD    "Force build and installation of package?" NO )
option (YAZPP_FROM_REPOS     "Install package from repository?"         NO )
option (YAZPP_ENABLE_TESTING "Enable testing and experimental builds?"  YES )

## Handle options

if (YAZPP_ENABLE_TESTING)
  include (CTest)
  enable_testing()
endif (YAZPP_ENABLE_TESTING)

## ==============================================================================
##
##  Build instructions
##
## ==============================================================================

if (YAZPP_FROM_REPOS)
  set (YAZPP_FORCE_BUILD TRUE)
endif (YAZPP_FROM_REPOS)

if (NOT YAZPP_FOUND OR YAZPP_FORCE_BUILD)
  
  ## Locate source file to build from
  
  find_file (YAZPP_SOURCE ${YAZPP_SOURCE_ARCHIVE}
    PATHS ${PROJECT_SOURCE_DIR}
    )
  
  if (NOT YAZPP_SOURCE)
    set (YAZPP_SOURCE ${YAZPP_URL})
  endif (NOT YAZPP_SOURCE)
  
  ## Build package from source
  
  if (YAZPP_FROM_REPOS)
    
    ExternalProject_Add (yazpp
      PREFIX ${PROJECT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      SVN_REPOSITORY ${YAZPP_SVN}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ${PROJECT_BINARY_DIR}/source/configure --prefix=${CMAKE_INSTALL_PREFIX} --with-yaz=${CMAKE_INSTALL_PREFIX}/bin
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )
  
  else (YAZPP_FROM_REPOS)
    
    ExternalProject_Add (yazpp
      PREFIX ${PROJECT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      URL ${YAZPP_SOURCE}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ${PROJECT_BINARY_DIR}/source/configure --prefix=${CMAKE_INSTALL_PREFIX} --with-yaz=${CMAKE_INSTALL_PREFIX}/bin
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )
    
  endif (YAZPP_FROM_REPOS)
  
else (NOT YAZPP_FOUND OR YAZPP_FORCE_BUILD)
  
  add_custom_target (yazpp
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "[yazpp] Found system-wide installation; skipping rebuild!"
    )
  
endif (NOT YAZPP_FOUND OR YAZPP_FORCE_BUILD)