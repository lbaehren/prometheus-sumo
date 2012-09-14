
## ==============================================================================
##
##  CMake project settings
##
## ==============================================================================

##  Package information
set (CLAMAV_VERSION        "0.97.4" )
set (CLAMAV_SOURCE_ARCHIVE "clamav-${CLAMAV_VERSION}.tar.gz" )
set (CLAMAV_URL            "http://downloads.sourceforge.net/project/clamav/clamav/${CLAMAV_VERSION}/${CLAMAV_SOURCE_ARCHIVE}" )
set (CLAMAV_GIT            "https://github.com/vrtadmin/clamav-devel" )

## ==============================================================================
##
##  Options
##
## ==============================================================================

option (CLAMAV_FORCE_BUILD    "Force build and installation of package?" NO  )
option (CLAMAV_FROM_REPOS     "Install package from repository?"         YES )

## ==============================================================================
##
##  System inspection
##
## ==============================================================================

find_package (ClamAV)
find_package (ZLIB)

if (NOT ZLIB_FOUND)
  message (WARNING "Unable to build ClamAV - missing ZLIB.")
endif (NOT ZLIB_FOUND)

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
    PATHS ${CMAKE_CURRENT_SOURCE_DIR}
    )

  if (NOT CLAMAV_SOURCE)
    set (CLAMAV_SOURCE ${CLAMAV_URL})
  endif (NOT CLAMAV_SOURCE)

  ##________________________________________________________
  ## Configuration files for the installed tools

  configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/clamd.conf.in
    ${CMAKE_CURRENT_BINARY_DIR}/clamd.conf
    )

  configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/freshclam.conf.in
    ${CMAKE_CURRENT_BINARY_DIR}/freshclam.conf
    )

  ##________________________________________________________
  ## Build package from source

  if (CLAMAV_FROM_REPOS)

    ExternalProject_Add (clamav
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      GIT_REPOSITORY ${CLAMAV_GIT}
      BUILD_IN_SOURCE 1
      PATCH_COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/freshclam.conf ${CMAKE_CURRENT_BINARY_DIR}/source/etc
      CONFIGURE_COMMAND ${CMAKE_CURRENT_BINARY_DIR}/source/configure --prefix=${CMAKE_INSTALL_PREFIX} --disable-clamav
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )

  else (CLAMAV_FROM_REPOS)

    ExternalProject_Add (clamav
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      URL ${CLAMAV_SOURCE}
      BUILD_IN_SOURCE 1
      PATCH_COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/freshclam.conf ${CMAKE_CURRENT_BINARY_DIR}/source/etc
      CONFIGURE_COMMAND ${CMAKE_CURRENT_BINARY_DIR}/source/configure --prefix=${CMAKE_INSTALL_PREFIX} --disable-clamav
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )

  endif (CLAMAV_FROM_REPOS)

  ##________________________________________________________
  ## Patch LLVM sub-module

  ExternalProject_Add_Step (clamav create_llvm_projects
    COMMAND ${CMAKE_COMMAND} -E make_directory libclamav/c++/llvm/projects
    COMMENT "Creating LLVM projects sub-directory"
    DEPENDEES patch
    DEPENDERS configure
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/source
    )

  ##________________________________________________________
  ## Set up database

  ExternalProject_Add_Step (clamav create_share_clamav
    COMMAND ${CMAKE_COMMAND} -E make_directory share/clamav
    COMMENT "Updating databases with virus signatures"
    DEPENDEES build
    DEPENDERS install
    WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}
    )

  ExternalProject_Add_Step (clamav download_databases
    COMMAND ${CMAKE_INSTALL_PREFIX}/bin/freshclam
    COMMENT "Updating databases with virus signatures"
    DEPENDEES install
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )

else (NOT CLAMAV_FOUND OR CLAMAV_FORCE_BUILD)

  add_custom_target (clamav
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "[clamav] Found system-wide installation; skipping rebuild!"
    )

endif (NOT CLAMAV_FOUND OR CLAMAV_FORCE_BUILD)

## ==============================================================================
##
##  Install support scripts
##
## ==============================================================================

configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/scanImages.bash.in
  ${CMAKE_INSTALL_PREFIX}/bin/scanImages.bash
  )
