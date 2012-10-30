
## ==============================================================================
##
##  CMake project settings
##
## ==============================================================================

## Name of the project handled by CMake
project (RANT)

## Minimum required version of CMake to configure the project
cmake_minimum_required (VERSION 2.8)

## Enforced CMake policy
cmake_policy (VERSION 2.8)

##  Package information
set (RANT_VERSION        "0.5.8" )
set (RANT_SOURCE_ARCHIVE "rant-${RANT_VERSION}.tar.gz" )
set (RANT_URL            "http://rubyforge.org/frs/download.php/14775/${RANT_SOURCE_ARCHIVE}" )
set (RANT_SVN            "http://rant.rubyforge.org/svn" )

## ==============================================================================
##
##  Options
##
## ==============================================================================

option (RANT_FORCE_BUILD    "Force build and installation of package?" NO )
option (RANT_FROM_REPOS     "Install package from repository?"         NO )
option (RANT_ENABLE_TESTING "Enable testing and experimental builds?"  YES )

## Handle options

if (RANT_ENABLE_TESTING)
  include (CTest)
  enable_testing()
endif (RANT_ENABLE_TESTING)

## ==============================================================================
##
##  System inspection
##
## ==============================================================================

find_program (RANT_EXECUTABLE rant)

if (RANT_EXECUTABLE)
  set (RANT_FOUND TRUE)
else (RANT_EXECUTABLE)
  set (RANT_FOUND FALSE)
endif (RANT_EXECUTABLE)

## ==============================================================================
##
##  Build instructions
##
## ==============================================================================

if (RANT_FROM_REPOS)
  set (RANT_FORCE_BUILD TRUE)
endif (RANT_FROM_REPOS)

if (NOT RANT_FOUND OR RANT_FORCE_BUILD)

  ## Locate source file to build from

  find_file (RANT_SOURCE ${RANT_SOURCE_ARCHIVE}
    PATHS ${PROJECT_SOURCE_DIR}
    )

  if (NOT RANT_SOURCE)
    set (RANT_SOURCE ${RANT_URL})
  endif (NOT RANT_SOURCE)

  ## Build package from source

  if (RANT_FROM_REPOS)

    ExternalProject_Add (rant
      PREFIX ${PROJECT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      SVN_REPOSITORY ${RANT_SVN}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ruby setup.rb config --prefix=${CMAKE_INSTALL_PREFIX}
      BUILD_COMMAND ruby setup.rb setup
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} ruby setup.rb install
      )

  else (RANT_FROM_REPOS)

    ExternalProject_Add (rant
      PREFIX ${PROJECT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      URL ${RANT_SOURCE}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ruby setup.rb config --prefix=${CMAKE_INSTALL_PREFIX}
      BUILD_COMMAND ruby setup.rb setup
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} ruby setup.rb install
      )

  endif (RANT_FROM_REPOS)

else (NOT RANT_FOUND OR RANT_FORCE_BUILD)

  add_custom_target (rant
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "[rant] Found system-wide installation; skipping rebuild!"
    )

endif (NOT RANT_FOUND OR RANT_FORCE_BUILD)
