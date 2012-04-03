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
set (${CMAKE_PROJECT_NAME}_VERSION "${Pandora_VERSION_MAJOR}.${Pandora_VERSION_MINOR}.${Pandora_VERSION_PATCH}")

## ==============================================================================
##
##  Configuration/Build options
##
## ==============================================================================

option (ENABLE_TESTING "Enable CTest test driver?" YES )

##__________________________________________________________
## Handle option: Enable CTest test driver?

if (ENABLE_TESTING)
  include (CTest)
  enable_testing()
endif (ENABLE_TESTING)

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

find_program (RDOC_EXECUTABLE rdoc)

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
message (STATUS " Ruby configuration:"                                          )
message (STATUS " .. Ruby executable ............ = ${RUBY_EXECUTABLE}"         )
message (STATUS " .. Ruby version ............... = ${RUBY_VERSION}"            )
message (STATUS " .. Path to Ruby library ....... = ${RUBY_LIBRARY}"            )
message (STATUS " .. Include directory .......... = ${RUBY_INCLUDE_DIRS}"       )
message (STATUS " Tools:"                                                       )
message (STATUS " .. RDoc executable ............ = ${RDOC_EXECUTABLE}"         )
message (STATUS " .. YARD executable ............ = ${YARD_EXECUTABLE}"         )
message (STATUS " .. YARD executable version .... = ${YARD_VERSION}"            )
message (STATUS "------------------------------------------------------------ " )
