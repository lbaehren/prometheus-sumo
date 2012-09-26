
## ==============================================================================
##
##  CMake project settings
##
## ==============================================================================

## Name of the project handled by CMake
project (YAZ)

## Minimum required version of CMake to configure the project
cmake_minimum_required (VERSION 2.8)

## Enforced CMake policy
cmake_policy (VERSION 2.8)

##  Package information
set (YAZ_VERSION        "4.2.38" )
set (YAZ_SOURCE_ARCHIVE "yaz-${YAZ_VERSION}.tar.gz" )
set (YAZ_URL            "http://ftp.indexdata.dk/pub/yaz/${YAZ_SOURCE_ARCHIVE}" )
set (YAZ_SVN            "" )

## ==============================================================================
##
##  Options
##
## ==============================================================================

option (YAZ_FORCE_BUILD    "Force build and installation of package?" NO )
option (YAZ_FROM_REPOS     "Install package from repository?"         NO )
option (YAZ_ENABLE_TESTING "Enable testing and experimental builds?"  YES )

## Handle options

if (YAZ_ENABLE_TESTING)
  include (CTest)
  enable_testing()
endif (YAZ_ENABLE_TESTING)

## ==============================================================================
##
##  System inspection
##
## ==============================================================================

find_package (YAZ)

## ==============================================================================
##
##  Build instructions
##
## ==============================================================================

if (YAZ_FROM_REPOS)
  set (YAZ_FORCE_BUILD TRUE)
endif (YAZ_FROM_REPOS)

if (NOT YAZ_FOUND OR YAZ_FORCE_BUILD)

  ## Locate source file to build from

  find_file (YAZ_SOURCE ${YAZ_SOURCE_ARCHIVE}
    PATHS ${PROJECT_SOURCE_DIR}
    )

  if (NOT YAZ_SOURCE)
    set (YAZ_SOURCE ${YAZ_URL})
  endif (NOT YAZ_SOURCE)

  ## Build package from source

  if (YAZ_FROM_REPOS)

    ExternalProject_Add (yaz
      PREFIX ${PROJECT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      SVN_REPOSITORY ${YAZ_SVN}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ${PROJECT_BINARY_DIR}/source/configure --prefix=${CMAKE_INSTALL_PREFIX}
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )

  else (YAZ_FROM_REPOS)

    ExternalProject_Add (yaz
      PREFIX ${PROJECT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      URL ${YAZ_SOURCE}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ${PROJECT_BINARY_DIR}/source/configure --prefix=${CMAKE_INSTALL_PREFIX}
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )

  endif (YAZ_FROM_REPOS)

else (NOT YAZ_FOUND OR YAZ_FORCE_BUILD)

  add_custom_target (yaz
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "[yaz] Found system-wide installation; skipping rebuild!"
    )

endif (NOT YAZ_FOUND OR YAZ_FORCE_BUILD)
