
## ==============================================================================
##
##  CMake project settings
##
## ==============================================================================

## Name of the project handled by CMake
project (FERRET)

## Minimum required version of CMake to configure the project
cmake_minimum_required (VERSION 2.8)

## Enforced CMake policy 
cmake_policy (VERSION 2.8)

##  Package information
set (FERRET_VERSION        "0.11.6" )
set (FERRET_SOURCE_ARCHIVE "ferret-${FERRET_VERSION}.tgz" )
set (FERRET_URL            "http://rubyforge.org/frs/download.php/28550/${FERRET_SOURCE_ARCHIVE}")

## ==============================================================================
##
##  System inspection
##
## ==============================================================================

find_package (Ferret)

## ==============================================================================
##
##  Build instructions
##
## ==============================================================================

if (FERRET_FROM_REPOS)
  set (FERRET_FORCE_BUILD TRUE)
endif (FERRET_FROM_REPOS)

if (NOT FERRET_FOUND OR FERRET_FORCE_BUILD)

  ## Locate source file to build from
  
  find_file (FERRET_SOURCE ${FERRET_SOURCE_ARCHIVE}
    PATHS ${PROJECT_SOURCE_DIR}
    )
  
  if (NOT FERRET_SOURCE)
    set (FERRET_SOURCE ${FERRET_URL})
  endif (NOT FERRET_SOURCE)

  ## Build package from source
  
  if (FERRET_FROM_REPOS)
    
    ExternalProject_Add (ferret
      PREFIX ${PROJECT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      SVN_REPOSITORY ${FERRET_SVN}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ${RUBY_EXECUTABLE} setup.rb config --prefix=${CMAKE_INSTALL_PREFIX}
      BUILD_COMMAND ${RUBY_EXECUTABLE} setup.rb setup
      INSTALL_COMMAND ${RUBY_EXECUTABLE} setup.rb install --prefix=${CMAKE_INSTALL_PREFIX}
      )
  
  else (FERRET_FROM_REPOS)
    
    ExternalProject_Add (ferret
      PREFIX ${PROJECT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      URL ${FERRET_SOURCE}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ${RUBY_EXECUTABLE} setup.rb config --prefix=${CMAKE_INSTALL_PREFIX}
      BUILD_COMMAND ${RUBY_EXECUTABLE} setup.rb setup
      INSTALL_COMMAND ${RUBY_EXECUTABLE} setup.rb install --prefix=${CMAKE_INSTALL_PREFIX}
      )
    
  endif (FERRET_FROM_REPOS)
else (NOT FERRET_FOUND OR FERRET_FORCE_BUILD)
  
  add_custom_target (ferret
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "[Ferret] Found system-wide installation; skipping rebuild!"
    )
  
endif (NOT FERRET_FOUND OR FERRET_FORCE_BUILD)
