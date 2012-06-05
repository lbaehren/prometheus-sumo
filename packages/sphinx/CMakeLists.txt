
## ==============================================================================
##
##  CMake project settings
##
## ==============================================================================

## Name of the project handled by CMake
project (SPHINX)

## Minimum required version of CMake to configure the project
cmake_minimum_required (VERSION 2.8)

## Enforced CMake policy 
cmake_policy (VERSION 2.8)

##  Package information
set (SPHINX_VERSION        "2.0.4" )
set (SPHINX_SOURCE_ARCHIVE "sphinx-${SPHINX_VERSION}-release.tar.gz" )
set (SPHINX_URL            "http://sphinxsearch.com/files/${SPHINX_SOURCE_ARCHIVE}" )
set (SPHINX_SVN            "" )

## ==============================================================================
##
##  Options
##
## ==============================================================================

option (SPHINX_FORCE_BUILD    "Force build and installation of package?" NO )
option (SPHINX_FROM_REPOS     "Install package from repository?"         NO )
option (SPHINX_ENABLE_TESTING "Enable testing and experimental builds?"  YES )

## Handle options

if (SPHINX_ENABLE_TESTING)
  include (CTest)
  enable_testing()
endif (SPHINX_ENABLE_TESTING)

## ==============================================================================
##
##  System inspection
##
## ==============================================================================

#include (FindSPHINX)

## ==============================================================================
##
##  Build instructions
##
## ==============================================================================

if (SPHINX_FROM_REPOS)
  set (SPHINX_FORCE_BUILD TRUE)
endif (SPHINX_FROM_REPOS)

if (NOT SPHINX_FOUND OR SPHINX_FORCE_BUILD)
  
  ## Locate source file to build from
  
  find_file (SPHINX_SOURCE ${SPHINX_SOURCE_ARCHIVE}
    PATHS ${PROJECT_SOURCE_DIR}
    )
  
  if (NOT SPHINX_SOURCE)
    set (SPHINX_SOURCE ${SPHINX_URL})
  endif (NOT SPHINX_SOURCE)
  
  ## Build package from source
  
  if (SPHINX_FROM_REPOS)
    
    ExternalProject_Add (sphinx
      PREFIX ${PROJECT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      SVN_REPOSITORY ${SPHINX_SVN}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ${PROJECT_BINARY_DIR}/source/configure --prefix=${CMAKE_INSTALL_PREFIX}
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )
  
  else (SPHINX_FROM_REPOS)
    
    ExternalProject_Add (sphinx
      PREFIX ${PROJECT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      URL ${SPHINX_SOURCE}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ${PROJECT_BINARY_DIR}/source/configure --prefix=${CMAKE_INSTALL_PREFIX} --with-mysql-includes=${MYSQL_INCLUDES} --with-mysql-libs=${MYSQL_LIBRARY_PATH} --without-iconv
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )
    
  endif (SPHINX_FROM_REPOS)
  
else (NOT SPHINX_FOUND OR SPHINX_FORCE_BUILD)
  
  add_custom_target (sphinx
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "[sphinx] Found system-wide installation; skipping rebuild!"
    )
  
endif (NOT SPHINX_FOUND OR SPHINX_FORCE_BUILD)
