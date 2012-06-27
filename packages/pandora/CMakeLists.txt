
## ==============================================================================
##
##  CMake project settings
##
## ==============================================================================

## Name of the project handled by CMake
project (PANDORA)

## Minimum required version of CMake to configure the project
cmake_minimum_required (VERSION 2.8)

## Enforced CMake policy 
cmake_policy (VERSION 2.8)

##  Package information
set (PANDORA_VERSION        "" )
set (PANDORA_SOURCE_ARCHIVE "" )
set (PANDORA_URL            "" )
set (PANDORA_SVN            "http://prometheus-srv.uni-koeln.de/svn/pandora/trunk" )

## ==============================================================================
##
##  Options
##
## ==============================================================================

option (PANDORA_FORCE_BUILD    "Force build and installation of package?" NO  )
option (PANDORA_FROM_REPOS     "Install package from repository?"         YES )
option (PANDORA_ENABLE_TESTING "Enable testing and experimental builds?"  YES )

## Handle options

if (PANDORA_ENABLE_TESTING)
  include (CTest)
  enable_testing()
endif (PANDORA_ENABLE_TESTING)

## ==============================================================================
##
##  System inspection
##
## ==============================================================================

#find_package (Pandora)

## ==============================================================================
##
##  Build instructions
##
## ==============================================================================

if (PANDORA_FROM_REPOS)

  ## Enforce build
  set (PANDORA_FORCE_BUILD TRUE)

  ## Check if a local version of the repository is available already;
  ## we need to be rather carefull here, in order not to accidentally
  ## pick up the Git repository files of the host project.
  find_file (PANDORA_REPOS_HEAD
    NAMES pandora/.git/HEAD pandora/HEAD
    HINTS ${prometheus-sumo_SOURCE_DIR} ${CMAKE_INSTALL_PREFIX}
    PATH_SUFFIXES data/repositories
    )
  
  if (PANDORA_REPOS_HEAD)
    get_filename_component (PANDORA_GIT ${PANDORA_REPOS_HEAD} PATH)
  endif (PANDORA_REPOS_HEAD)

endif (PANDORA_FROM_REPOS)

if (NOT PANDORA_FOUND OR PANDORA_FORCE_BUILD)
  
  ## Locate source file to build from
  
  find_file (PANDORA_SOURCE ${PANDORA_SOURCE_ARCHIVE}
    PATHS ${PROJECT_SOURCE_DIR}
    )
  
  if (NOT PANDORA_SOURCE)
    set (PANDORA_SOURCE ${PANDORA_URL})
  endif (NOT PANDORA_SOURCE)
  
  ## Build package from source
  
  if (PANDORA_FROM_REPOS)
    
    if (PANDORA_GIT)
      
      ExternalProject_Add (pandora
	PREFIX ${PROJECT_BINARY_DIR}
	DOWNLOAD_DIR download
	SOURCE_DIR source
	GIT_REPOSITORY ${PANDORA_GIT}
	BUILD_IN_SOURCE 1
	CONFIGURE_COMMAND ${RAKE_EXECUTABLE} pandora:setup
	INSTALL_COMMAND ""
	BUILD_COMMAND ""
	)

    else (PANDORA_GIT)
      
      ExternalProject_Add (pandora
	PREFIX ${PROJECT_BINARY_DIR}
	DOWNLOAD_DIR download
	SOURCE_DIR source
	SVN_REPOSITORY ${PANDORA_SVN}
	BUILD_IN_SOURCE 1
	CONFIGURE_COMMAND ${RAKE_EXECUTABLE} pandora:setup
	INSTALL_COMMAND ""
	BUILD_COMMAND ""
	)
      
    endif (PANDORA_GIT)
    
  else (PANDORA_FROM_REPOS)
    
    ExternalProject_Add (pandora
      PREFIX ${PROJECT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      URL ${PANDORA_SOURCE}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ${RAKE_EXECUTABLE} pandora:setup
      INSTALL_COMMAND ""
      BUILD_COMMAND ""
      )
    
  endif (PANDORA_FROM_REPOS)
  
else (NOT PANDORA_FOUND OR PANDORA_FORCE_BUILD)
  
  add_custom_target (pandora
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "[pandora] Found system-wide installation; skipping rebuild!"
    )
  
endif (NOT PANDORA_FOUND OR PANDORA_FORCE_BUILD)
