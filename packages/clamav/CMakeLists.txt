
## ==============================================================================
##
##  CMake project settings
##
## ==============================================================================

## Name of the project handled by CMake
project (CLAMAV)

## Minimum required version of CMake to configure the project
cmake_minimum_required (VERSION 2.8)

## Enforced CMake policy 
cmake_policy (VERSION 2.8)

##  Package information
set (CLAMAV_VERSION        "0.97.4" )
set (CLAMAV_SOURCE_ARCHIVE "clamav-${CLAMAV_VERSION}.tar.gz" )
set (CLAMAV_URL            "http://downloads.sourceforge.net/project/clamav/clamav/${CLAMAV_VERSION}/${CLAMAV_SOURCE_ARCHIVE}" )
set (CLAMAV_GIT            "git://git.clamav.net/git/clamav-devel" )

## ==============================================================================
##
##  Options
##
## ==============================================================================

option (CLAMAV_FORCE_BUILD    "Force build and installation of package?" NO )
option (CLAMAV_FROM_REPOS     "Install package from repository?"         NO )
option (CLAMAV_ENABLE_TESTING "Enable testing and experimental builds?"  YES )

## Handle options

if (CLAMAV_ENABLE_TESTING)
  include (CTest)
  enable_testing()
endif (CLAMAV_ENABLE_TESTING)

## ==============================================================================
##
##  System inspection
##
## ==============================================================================

find_package (ClamAV)

## ==============================================================================
##
##  Build instructions
##
## ==============================================================================

if (CLAMAV_FROM_REPOS)
  set (CLAMAV_FORCE_BUILD TRUE)
endif (CLAMAV_FROM_REPOS)

if (NOT CLAMAV_FOUND OR CLAMAV_FORCE_BUILD)
  
  ##________________________________________________________
  ## Locate source file to build from
  
  find_file (CLAMAV_SOURCE ${CLAMAV_SOURCE_ARCHIVE}
    PATHS ${PROJECT_SOURCE_DIR}
    )
  
  if (NOT CLAMAV_SOURCE)
    set (CLAMAV_SOURCE ${CLAMAV_URL})
  endif (NOT CLAMAV_SOURCE)

  ##________________________________________________________
  ## Configuration files for the installed tools

  configure_file (
    ${PROJECT_SOURCE_DIR}/clamd.conf.in
    ${PROJECT_BINARY_DIR}/clamd.conf
    )

  configure_file (
    ${PROJECT_SOURCE_DIR}/freshclam.conf.in
    ${PROJECT_BINARY_DIR}/freshclam.conf
    )

  ##________________________________________________________
  ## Build package from source
  
  if (CLAMAV_FROM_REPOS)
    
    ExternalProject_Add (clamav
      PREFIX ${PROJECT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      GIT_REPOSITORY ${CLAMAV_GIT}
      BUILD_IN_SOURCE 1
      PATCH_COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/freshclam.conf ${PROJECT_BINARY_DIR}/source/etc
      CONFIGURE_COMMAND ${PROJECT_BINARY_DIR}/source/configure --prefix=${CMAKE_INSTALL_PREFIX} --disable-clamav
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )
  
  else (CLAMAV_FROM_REPOS)
    
    ExternalProject_Add (clamav
      PREFIX ${PROJECT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      URL ${CLAMAV_SOURCE}
      BUILD_IN_SOURCE 1
      PATCH_COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BINARY_DIR}/freshclam.conf ${PROJECT_BINARY_DIR}/source/etc
      CONFIGURE_COMMAND ${PROJECT_BINARY_DIR}/source/configure --prefix=${CMAKE_INSTALL_PREFIX} --disable-clamav
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )
    
  endif (CLAMAV_FROM_REPOS)

  ##________________________________________________________
  ## Set up database
  
  ExternalProject_Add_Step (clamav download_databases
    COMMAND ${CMAKE_INSTALL_PREFIX}/bin/freshclam
    COMMENT "Updating databases with virus signatures"
    DEPENDEES install
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )

else (NOT CLAMAV_FOUND OR CLAMAV_FORCE_BUILD)
  
  add_custom_target (clamav
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "[clamav] Found system-wide installation; skipping rebuild!"
    )
  
endif (NOT CLAMAV_FOUND OR CLAMAV_FORCE_BUILD)

## ==============================================================================
##
##  Install support scripts
##
## ==============================================================================

configure_file (
  ${PROJECT_SOURCE_DIR}/scanImages.bash.in
  ${CMAKE_INSTALL_PREFIX}/bin/scanImages.bash
  )
