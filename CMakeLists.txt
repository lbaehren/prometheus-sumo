## ==============================================================================
##
##  CMake project settings
##
## ==============================================================================

## Name of the project handled by CMake
project (prometheus-sumo)

## Minimum required version of CMake to configure the project
cmake_minimum_required (VERSION 2.8.3)

## Enforced CMake policy
cmake_policy (VERSION 2.8.3)

## Project release version (major.minor.patch)
set (${CMAKE_PROJECT_NAME}_VERSION_MAJOR 0 )
set (${CMAKE_PROJECT_NAME}_VERSION_MINOR 1 )
set (${CMAKE_PROJECT_NAME}_VERSION_PATCH 0 )
set (${CMAKE_PROJECT_NAME}_VERSION "${${CMAKE_PROJECT_NAME}_VERSION_MAJOR}.${${CMAKE_PROJECT_NAME}_VERSION_MINOR}.${${CMAKE_PROJECT_NAME}_VERSION_PATCH}")

## Commonly used variables

set (REQUIRED_VERSION_RUBY  1.8  )
set (NOF_SKIPPED_TESTS      0    )

## ==============================================================================
##
##  Configuration/Build options
##
## ==============================================================================

option (ENABLE_TESTING        "Enable CTest test driver?"                     YES )
option (CONFIGURE_VERBOSE     "Increase verbosity during configuration?"      NO  )
option (GIT_REPOSITORIES_RW   "Check out Github repositories for r/w access?" NO  )

option (WITH_CLAMAV       "Enable ClamAV antivirus software tool-kit?"     YES )
option (WITH_PANDORA_DOCS "Enable documentation of pandora source code?"   NO  )

##__________________________________________________________
## Handle option: Enable CTest test driver?

if (ENABLE_TESTING)
  include (CTest)
  enable_testing()
endif (ENABLE_TESTING)

##__________________________________________________________
## Handle option: Check out Github repositories for r/w access?

if (GIT_REPOSITORIES_RW)
  set (GIT_REPOSITORY_BASE    "git@github.com:prometheus-ev" )
else (GIT_REPOSITORIES_RW)
  set (GIT_REPOSITORY_BASE    "git://github.com/prometheus-ev" )
endif (GIT_REPOSITORIES_RW)

##__________________________________________________________
## Handle option: Increase verbosity during configuration?

if (NOT CONFIGURE_VERBOSE)
  set (CLAMAV_FIND_QUIETLY   YES )
  set (DOXYGEN_FIND_QUIETLY  YES )
  set (GEM_FIND_QUIETLY      YES )
  set (GIT_FIND_QUIETLY      YES )
  set (ICONV_FIND_QUIETLY    YES )
  set (LATEX_FIND_QUIETLY    YES )
  set (MAGIC_FIND_QUIETLY    YES )
  set (MYSQL_FIND_QUIETLY    YES )
  set (RAILS_FIND_QUIETLY    YES )
  set (RAKE_FIND_QUIETLY     YES )
  set (RDOC_FIND_QUIETLY     YES )
  set (RUBY_FIND_QUIETLY     YES )
  set (RUBYGEMS_FIND_QUIETLY YES )
  set (_RUBY_DEBUG_OUTPUT    NO  )
  set (XERCESC_FIND_QUIETLY  YES )
  set (YAML_FIND_QUIETLY     YES )
  set (YARD_FIND_QUIETLY     YES )
endif (NOT CONFIGURE_VERBOSE)

## ==============================================================================
##
##  System inspection
##
## ==============================================================================

##__________________________________________________________
## Register local additions to collection of modules

set (CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/config/cmake" CACHE PATH
  "CMake module path"
  FORCE
  )

##__________________________________________________________
## Standard CMake modules

include(ExternalProject)
find_package (Git)
find_package (Doxygen)
find_package (Ruby)

##__________________________________________________________
## Custom inspection

find_package (RDoc)
find_package (Rails)
find_package (Rake)
find_package (Gem)
find_package (Iconv)
find_package (MagicLib)
find_package (MySQL)
find_package (Xercesc)
find_package (Yaml)
find_package (Yard)

## Extract Doxygen version number - this is not done by the standard module
if (DOXYGEN_EXECUTABLE)
  
  execute_process(
    COMMAND ${DOXYGEN_EXECUTABLE} --version
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    RESULT_VARIABLE DOXYGEN_RESULT_VARIABLE
    OUTPUT_VARIABLE DOXYGEN_VERSION
    ERROR_VARIABLE DOXYGEN_ERROR_VARIABLE
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
  
  if (DOXYGEN_VERSION)
    ## Convert string to list of numbers
    string (REGEX REPLACE "\\." ";" DOXYGEN_VERSION_LIST ${DOXYGEN_VERSION})
    ## Retrieve individual elements in the list
    list(GET DOXYGEN_VERSION_LIST 0 DOXYGEN_VERSION_MAJOR)
    list(GET DOXYGEN_VERSION_LIST 1 DOXYGEN_VERSION_MINOR)
    list(GET DOXYGEN_VERSION_LIST 2 DOXYGEN_VERSION_PATCH)
  endif (DOXYGEN_VERSION)  
  
endif (DOXYGEN_EXECUTABLE)

## Decomposition of Ruby version number - this is not done by the standard module

if (RUBY_VERSION)
  ## Convert string to list of numbers
  string (REGEX REPLACE "\\." ";" RUBY_VERSION_LIST ${RUBY_VERSION})
  ## Retrieve individual elements in the list
  list(GET RUBY_VERSION_LIST 0 RUBY_VERSION_MAJOR)
  list(GET RUBY_VERSION_LIST 1 RUBY_VERSION_MINOR)
  list(GET RUBY_VERSION_LIST 2 RUBY_VERSION_PATCH)
endif (RUBY_VERSION)

## ==============================================================================
##
##  Installation location
##
## ==============================================================================

## For a production and development system on one of the server machines the
## installation is done into "/var/local/prometheus". If however development
## (or even just test installation) is carried out on a different system with
## the user/developer not having write permissions to "/var/local" we need to
## move to the installation root to a different point.

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

  set (CMAKE_INSTALL_PREFIX
    "${PROJECT_SOURCE_DIR}/release" CACHE PATH "prometheus install prefix" FORCE
    )
endif (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

## ==============================================================================
##
##  Project sub-directories
##
## ==============================================================================

add_subdirectory (data)
add_subdirectory (packages)
add_subdirectory (sources)
add_subdirectory (documentation)

## ==============================================================================
##
##  Configuration summary
##
## ==============================================================================

## Generate file with project version number

file (WRITE ${CMAKE_CURRENT_BINARY_DIR}/VERSION "${${CMAKE_PROJECT_NAME}_VERSION}")

## Display summary of configuration settings

message (STATUS "------------------------------------------------------------"   )
message (STATUS "[prometheus-sumo] Configuration summary."                       )
message (STATUS "------------------------------------------------------------ "  )
message (STATUS " System configuration:"                                         )
message (STATUS " .. Processor type .............. = ${CMAKE_SYSTEM_PROCESSOR}"  )
message (STATUS " .. CMake executable ............ = ${CMAKE_COMMAND}"           )
message (STATUS " .. CMake version ............... = ${CMAKE_VERSION}"           )
message (STATUS " .. System name ................. = ${CMAKE_SYSTEM}"            )
message (STATUS " .. Operating system name ....... = ${CMAKE_OS_NAME}"           )
message (STATUS " .. C++ compiler ................ = ${CMAKE_CXX_COMPILER}"      )
message (STATUS " .. C compiler .................. = ${CMAKE_C_COMPILER}"        )
message (STATUS " .. size(void*) ................. = ${CMAKE_SIZEOF_VOID_P}"     )
message (STATUS " Project configuration:"                                       )
message (STATUS " .. Version number .............. = ${${CMAKE_PROJECT_NAME}_VERSION}")
message (STATUS " .. Installation prefix ......... = ${CMAKE_INSTALL_PREFIX}"    )
message (STATUS " .. Git repository base URL ..... = ${GIT_REPOSITORY_BASE}"     )
message (STATUS " .. Clone Github repositories r/w = ${GIT_REPOSITORIES_RW}"     )
message (STATUS " .. Enable CTest test driver? ... = ${ENABLE_TESTING}"          )
message (STATUS " .. Verbose configure? .......... = ${CONFIGURE_VERBOSE}"       )
message (STATUS " .. pandora database dumps ...... = ${PANDORA_DATA_DIR}"        )
message (STATUS " Ruby configuration:"                                           )
message (STATUS " .. Required version ............ = ${REQUIRED_VERSION_RUBY}"   )
message (STATUS " .. Ruby executable ............. = ${RUBY_EXECUTABLE}"         )
message (STATUS " .. Ruby version ................ = ${RUBY_VERSION}"            )
message (STATUS " .. Path to Ruby library ........ = ${RUBY_LIBRARY}"            )
message (STATUS " .. Include directory ........... = ${RUBY_INCLUDE_DIRS}"       )
message (STATUS " .. Gem executable .............. = ${GEM_EXECUTABLE}"          )
message (STATUS " .. Gem executable version ...... = ${GEM_VERSION}"             )
message (STATUS " .. Rake executable ............. = ${RAKE_EXECUTABLE}"         )
message (STATUS " .. Rake executable version ..... = ${RAKE_VERSION}"            )
message (STATUS " .. Rails executable ............ = ${RAILS_EXECUTABLE}"        )
message (STATUS " .. Rails executable version .... = ${RAILS_VERSION}"           )
message (STATUS " Documentation tools:"                                          )
message (STATUS " .. Doxygen executable .......... = ${DOXYGEN_EXECUTABLE}"      )
message (STATUS " .. Doxygen executable version .. = ${DOXYGEN_VERSION}"         )
message (STATUS " .. RDoc executable ............. = ${RDOC_EXECUTABLE}"         )
message (STATUS " .. RDoc executable version ..... = ${RDOC_VERSION}"            )
message (STATUS " .. YARD executable ............. = ${YARD_EXECUTABLE}"         )
message (STATUS " .. YARD executable version ..... = ${YARD_VERSION}"            )
message (STATUS " Database:"                                                     )
message (STATUS " .. MySQL include directory ..... = ${MYSQL_INCLUDES}"          )
message (STATUS " .. MySQL client libraries ...... = ${MYSQL_LIBRARIES}"         )
message (STATUS " .. Yaml include directory ...... = ${YAML_INCLUDES}"           )
message (STATUS " .. Yaml libraries .............. = ${YAML_LIBRARIES}"          )
message (STATUS " Processing tools & libraries:"                                 )
message (STATUS " .. Magic include directory ..... = ${MAGIC_INCLUDES}"          )
message (STATUS " .. Magic library ............... = ${MAGIC_LIBRARIES}"         )
message (STATUS " .. Xercesc include directory ... = ${XERCESC_INCLUDES}"        )
message (STATUS " .. Xercesc library ............. = ${XERCESC_LIBRARIES}"       )
message (STATUS "------------------------------------------------------------ "  )
