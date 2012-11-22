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
set (PROJECT_VERSION_MAJOR 0 )
set (PROJECT_VERSION_MINOR 1 )
set (PROJECT_VERSION_PATCH 0 )
set (PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

## Commonly used variables

set (REQUIRED_VERSION_RUBY    1.8  )
set (REQUIRED_VERSION_DOXYGEN "100800000")
set (NOF_SKIPPED_TESTS      0    )

## ==============================================================================
##
##  Configuration/Build options
##
## ==============================================================================

option (ENABLE_TESTING       "Enable CTest test driver?"                     NO )
option (CONFIGURE_VERBOSE    "Increase verbosity during configuration?"      NO )
option (GIT_REPOSITORIES_RW  "Check out Github repositories for r/w access?" NO )

option (WITH_CLAMAV       "Enable ClamAV antivirus software tool-kit?"      YES )
option (WITH_PANDORA_DOCS "Enable documentation of pandora source code?"    NO  )
option (WITH_LATEX_DOC    "Enable generation of LaTeX output from Doxygen?" NO  )

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
  set (MAGIC_FIND_QUIETLY     YES )
  set (RUBYGEMS_FIND_QUIETLY  YES )
endif (NOT CONFIGURE_VERBOSE)

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

## Expose the installation prefix as location to inspect when searching for
## package header files, libraries and programs.

list (INSERT CMAKE_PREFIX_PATH  0 ${CMAKE_INSTALL_PREFIX}         )
list (INSERT CMAKE_INCLUDE_PATH 0 ${CMAKE_INSTALL_PREFIX}/include )
list (INSERT CMAKE_LIBRARY_PATH 0 ${CMAKE_INSTALL_PREFIX}/lib )
list (INSERT CMAKE_PROGRAM_PATH 0 ${CMAKE_INSTALL_PREFIX}/bin     )

## ==============================================================================
##
##  System inspection
##
## ==============================================================================

## Augment module path

set (CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/config/cmake" CACHE PATH
  "CMake module path"
  FORCE
  )

## Load extra modules

include (ExternalProject)
include (DetectOS)

## Find installed packages

find_package (Boost COMPONENTS program_options regex)

foreach (_cmakeModule
  ClamAV
  Doxygen
  Gem
  Git
  Iconv
  ImageMagick
  KWSys
  LATEX
  LibXml2
  MagicLib
  MySQL
  RDoc
  Rails
  Rake
  Rant
  Ruby
  Subversion
  TinyXML
  UnixCommands
  VirtualBox
  Xercesc
  Yaml
  Yard
  YAZ
  YAZPP
  ZLIB
  )
  ## Verbosity of module
  if (NOT CONFIGURE_VERBOSE)
    ## Convert module name to upper-case
    string (TOUPPER ${_cmakeModule} _varModule)
    ##
    set (${_varModule}_FIND_QUIETLY YES )
  endif (NOT CONFIGURE_VERBOSE)
  ## load the module
  find_package (${_cmakeModule})
endforeach (_cmakeModule)

## Decomposition of Ruby version number - this is not done by the standard module

if (RUBY_VERSION)
  ## Convert string to list of numbers
  string (REGEX REPLACE "\\." ";" RUBY_VERSION_LIST ${RUBY_VERSION})
  ## Retrieve individual elements in the list
  list(GET RUBY_VERSION_LIST 0 RUBY_VERSION_MAJOR)
  list(GET RUBY_VERSION_LIST 1 RUBY_VERSION_MINOR)
  list(GET RUBY_VERSION_LIST 2 RUBY_VERSION_PATCH)
  ## Ruby release series
  set (RUBY_VERSION_SERIES "${RUBY_VERSION_MAJOR}.${RUBY_VERSION_MAJOR}")
endif (RUBY_VERSION)

## ==============================================================================
##
##  Project sub-directories
##
## ==============================================================================

add_subdirectory (config)
add_subdirectory (data)
add_subdirectory (packages)
add_subdirectory (sources)
add_subdirectory (documentation)

## ==============================================================================
##
##  Configuration summary
##
## ==============================================================================

include (ConfigurationSummary)
