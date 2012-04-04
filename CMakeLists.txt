## ==============================================================================
##
##  CMake project settings
##
## ==============================================================================

## Name of the project handled by CMake
project (prometheus-sumo)

## Minimum required version of CMake to configure the project
cmake_minimum_required (VERSION 2.8)

## Enforced CMake policy
cmake_policy (VERSION 2.8)

## Project release version (major.minor.patch)
set (${CMAKE_PROJECT_NAME}_VERSION_MAJOR 0 )
set (${CMAKE_PROJECT_NAME}_VERSION_MINOR 1 )
set (${CMAKE_PROJECT_NAME}_VERSION_PATCH 0 )
set (${CMAKE_PROJECT_NAME}_VERSION "${${CMAKE_PROJECT_NAME}_VERSION_MAJOR}.${${CMAKE_PROJECT_NAME}_VERSION_MINOR}.${${CMAKE_PROJECT_NAME}_VERSION_PATCH}")

## ==============================================================================
##
##  Configuration/Build options
##
## ==============================================================================

option (ENABLE_TESTING    "Enable CTest test driver?"                YES )
option (VERBOSE_CONFIGURE "Increase verbosity during configuration?" NO  )

set (GIT_REPOSITORY_BASE "git@github.com:prometheus-ev")

##__________________________________________________________
## Handle option: Enable CTest test driver?

if (ENABLE_TESTING)
  include (CTest)
  enable_testing()
endif (ENABLE_TESTING)

##__________________________________________________________
## Handle option: Increase verbosity during configuration?

if (NOT VERBOSE_CONFIGURE)
  set (GIT_FIND_QUIETLY     YES )
  set (DOXYGEN_FIND_QUIETLY YES )
  set (RDOC_FIND_QUIETLY    YES )
  set (RUBY_FIND_QUIETLY    YES )
  set (_RUBY_DEBUG_OUTPUT   NO  )
  set (YARD_FIND_QUIETLY    YES )
endif (NOT VERBOSE_CONFIGURE)

## ==============================================================================
##
##  System inspection
##
## ==============================================================================

## Standard CMake modules

find_package (Git)
find_package (Doxygen)
find_package (Ruby)

## Custom inspection

include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindYard.cmake)
include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindRDoc.cmake)

## ==============================================================================
##
##  Project sub-directories
##
## ==============================================================================

add_subdirectory (sources)
add_subdirectory (doc)

## ==============================================================================
##
##  Configuration summary
##
## ==============================================================================

message (STATUS "------------------------------------------------------------"  )
message (STATUS "[prometheus-sumo] Configuration summary."                      )
message (STATUS "------------------------------------------------------------ " )
message (STATUS " System configuration:"                                        )
message (STATUS " .. Processor type ............. = ${CMAKE_SYSTEM_PROCESSOR}"  )
message (STATUS " .. CMake executable ........... = ${CMAKE_COMMAND}"           )
message (STATUS " .. CMake version .............. = ${CMAKE_VERSION}"           )
message (STATUS " .. System name ................ = ${CMAKE_SYSTEM}"            )
message (STATUS " .. C++ compiler ............... = ${CMAKE_CXX_COMPILER}"      )
message (STATUS " .. C compiler ................. = ${CMAKE_C_COMPILER}"        )
message (STATUS " .. size(void*) ................ = ${CMAKE_SIZEOF_VOID_P}"     )
message (STATUS " Project configuration:"                                       )
message (STATUS " .. Version number ............. = ${${CMAKE_PROJECT_NAME}_VERSION}")
message (STATUS " .. Git repository base URL .... = ${GIT_REPOSITORY_BASE}"     )
message (STATUS " .. Enable CTest test driver?    = ${ENABLE_TESTING}"          )
message (STATUS " .. Verbose configure?           = ${VERBOSE_CONFIGURE}"       )
message (STATUS " Ruby configuration:"                                          )
message (STATUS " .. Ruby executable ............ = ${RUBY_EXECUTABLE}"         )
message (STATUS " .. Ruby version ............... = ${RUBY_VERSION}"            )
message (STATUS " .. Path to Ruby library ....... = ${RUBY_LIBRARY}"            )
message (STATUS " .. Include directory .......... = ${RUBY_INCLUDE_DIRS}"       )
message (STATUS " Tools:"                                                       )
message (STATUS " .. RDoc executable ............ = ${RDOC_EXECUTABLE}"         )
message (STATUS " .. RDoc executable version .... = ${RDOC_VERSION}"            )
message (STATUS " .. YARD executable ............ = ${YARD_EXECUTABLE}"         )
message (STATUS " .. YARD executable version .... = ${YARD_VERSION}"            )
message (STATUS "------------------------------------------------------------ " )
