
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

if (RUBY_EXECUTABLE)
  add_subdirectory (test)
endif (RUBY_EXECUTABLE)
