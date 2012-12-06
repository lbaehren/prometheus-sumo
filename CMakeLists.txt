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

set (Ruby_FIND_VERSION_MAJOR  1 )
set (Ruby_FIND_VERSION_MINOR  8 )
set (REQUIRED_VERSION_RUBY    "${Ruby_FIND_VERSION_MAJOR}.${Ruby_FIND_VERSION_MINOR}" )
set (REQUIRED_VERSION_DOXYGEN "100800000")
set (NOF_SKIPPED_TESTS        0    )

## ==============================================================================
##
##  Configuration/Build options
##
## ==============================================================================

option (ENABLE_TESTING       "Enable CTest test driver?"                     YES )
option (CONFIGURE_VERBOSE    "Increase verbosity during configuration?"      NO  )
option (GIT_REPOSITORIES_RW  "Check out Github repositories for r/w access?" NO  )

option (WITH_DOXYGEN        "Build Doxygen documention generator?"             NO )
option (WITH_PACKAGE_CLAMAV "Build ClamAV antivirus software tool-kit?"        NO )
option (WITH_PACKAGE_SPHINX "Build Sphinx search server?"                      NO )
option (WITH_PACKAGE_YAZ    "Build YAZ programmers' toolkit?"                  NO )
option (WITH_PANDORA_DOCS   "Enable documentation of pandora source code?"     NO )
option (WITH_LATEX_DOC      "Enable generation of LaTeX output from Doxygen?"  NO )

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
  PoDoFo
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

message (STATUS " Project configuration:"                                        )
message (STATUS " .. Version number .............. = ${PROJECT_VERSION}"         )
message (STATUS " .. Installation prefix ......... = ${CMAKE_INSTALL_PREFIX}"    )
message (STATUS " .. Git repository base URL ..... = ${GIT_REPOSITORY_BASE}"     )
message (STATUS " .. Clone Github repositories r/w = ${GIT_REPOSITORIES_RW}"     )
message (STATUS " .. Enable CTest test driver? ... = ${ENABLE_TESTING}"          )
message (STATUS " .. Verbose configure? .......... = ${CONFIGURE_VERBOSE}"       )
message (STATUS " .. pandora database dumps ...... = ${PANDORA_DATA_DIR}"        )

message (STATUS " Ruby configuration:"                                           )
message (STATUS " .. Required version ............ = ${REQUIRED_VERSION_RUBY}"   )
message (STATUS " .. Ruby executable ............. = ${RUBY_EXECUTABLE} (${RUBY_VERSION})" )
message (STATUS " .. Path to Ruby library ........ = ${RUBY_LIBRARY}"            )
message (STATUS " .. Include directory ........... = ${RUBY_INCLUDE_DIRS}"       )
message (STATUS " .. Gem executable .............. = ${GEM_FOUND} (${GEM_VERSION})" )
message (STATUS " .. Rails executable ............ = ${RAILS_FOUND} (${RAILS_VERSION})" )
message (STATUS " .. Rake executable ............. = ${RAKE_FOUND} (${RAKE_VERSION})" )
message (STATUS " .. Rant executable ............. = ${RANT_FOUND} (${RANT_VERSION})" )
message (STATUS " .. RDoc ........................ = ${RDOC_FOUND} (${RDOC_VERSION})"            )
message (STATUS " .. YARD executable ............. = ${YARD_FOUND} (${YARD_VERSION})" )

message (STATUS " Processing tools & libraries:"                                 )
message (STATUS " .. Boost ....................... = ${Boost_FOUND}"             )
message (STATUS " .. Doxygen ..................... = ${DOXYGEN_FOUND} (${DOXYGEN_VERSION})" )
message (STATUS " .. ImageMagick ................. = ${ImageMagick_FOUND} (${ImageMagick_VERSION_STRING})" )
message (STATUS " .. KWSys ....................... = ${KWSYS_FOUND}"             )
message (STATUS " .. Magic ....................... = ${MAGIC_FOUND}"             )
message (STATUS " .. MySQL ....................... = ${MYSQL_FOUND}"             )
message (STATUS " .. PoDoFo ...................... = ${PODOFO_FOUND}")
message (STATUS " .. TinyXML ..................... = ${TINYXML_FOUND}"           )
message (STATUS " .. VirtualBox .................. = ${VIRTUALBOX_FOUND}"        )
message (STATUS " .. Yaml ........................ = ${YAML_FOUND}"              )
message (STATUS " .. YAZ ......................... = ${YAZ_FOUND} (${YAZ_VERSION})"     )
message (STATUS " .. YAZ++ ....................... = ${YAZPP_FOUND} (${YAZPP_VERSION})" )

message (STATUS "------------------------------------------------------------ "  )
