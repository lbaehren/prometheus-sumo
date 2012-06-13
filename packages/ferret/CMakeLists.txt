
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


## ==============================================================================
##
##  Project sub-directories
##
## ==============================================================================

set (FERRET_VERSION        "0.11.6" )
set (FERRET_SOURCE_ARCHIVE "ferret-${FERRET_VERSION}.tgz" )
set (FERRET_URL            "http://rubyforge.org/frs/download.php/28550/${FERRET_SOURCE_ARCHIVE}")

if (RUBY_EXECUTABLE)
  add_subdirectory (test)
endif (RUBY_EXECUTABLE)
