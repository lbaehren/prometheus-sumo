
## ==============================================================================
##
##  Package information
##
## ==============================================================================

# YAZ is a programmers’ toolkit supporting the development of Z39.50/SRW/SRU
# clients and servers. Z39.50-2003 (version 3) as well as SRW/SRU version 1.1
# are supported in both the client and server roles. The SOLR webservice is
# supported in the client role through the ZOOM API.

set (YAZ_VERSION          "4.2.38" )
set (YAZ_VERSION_REQUIRED "40020038" )
set (YAZ_SOURCE_ARCHIVE   "yaz-${YAZ_VERSION}.tar.gz" )
set (YAZ_URL              "http://ftp.indexdata.dk/pub/yaz/${YAZ_SOURCE_ARCHIVE}" )
set (YAZ_SVN              "" )

## ==============================================================================
##
##  Options
##
## ==============================================================================

option (YAZ_FORCE_BUILD    "Force build and installation of package?" NO )
option (YAZ_FROM_REPOS     "Install package from repository?"         NO )

## If YAZ is installed as system package, check of the version is ok

if (YAZ_VERSION_STRING)

  message (STATUS "Checking whether YAZ version is ok")

  if (${YAZ_VERSION_STRING} LESS ${YAZ_VERSION_REQUIRED})
    set (YAZ_FOUND FALSE)
    message (STATUS "Checking whether YAZ version is ok - no")
  else ()
    message (STATUS "Checking whether YAZ version is ok - yes")
  endif()

endif ()

## ==============================================================================
##
##  Build instructions
##
## ==============================================================================

if (NOT YAZ_FOUND OR YAZ_FORCE_BUILD)

  ## Clear existing variables from configuration cache
  unset (YAZ_INCLUDES           CACHE )
  unset (YAZ_LIBRARIES          CACHE )
  unset (YAZ_YAZ_LIBRARY        CACHE )
  unset (YAZ_YAZ_ICU_LIBRARY    CACHE )
  unset (YAZ_YAZ_SERVER_LIBRARY CACHE )
  unset (YAZ_CLIENT_EXECUTABLE  CACHE )
  unset (YAZ_CONFIG_EXECUTABLE  CACHE )

  ## Locate source file to build from

  find_file (YAZ_SOURCE ${YAZ_SOURCE_ARCHIVE}
    PATHS ${CMAKE_CURRENT_SOURCE_DIR}
    )

  if (NOT YAZ_SOURCE)
    set (YAZ_SOURCE ${YAZ_URL})
  endif (NOT YAZ_SOURCE)

  ## Build package from source

  if (YAZ_FROM_REPOS)

    ExternalProject_Add (yaz
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      SVN_REPOSITORY ${YAZ_SVN}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ${CMAKE_CURRENT_BINARY_DIR}/source/configure --prefix=${CMAKE_INSTALL_PREFIX}
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )

  else (YAZ_FROM_REPOS)

    ExternalProject_Add (yaz
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      URL ${YAZ_SOURCE}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ${CMAKE_CURRENT_BINARY_DIR}/source/configure --prefix=${CMAKE_INSTALL_PREFIX}
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )

  endif (YAZ_FROM_REPOS)

  ## Update top-level project configuration
  ExternalProject_Add_Step (yaz update_configuration
    COMMAND ${CMAKE_COMMAND} -E remove CMake*
    COMMAND ${CMAKE_COMMAND} -E remove_directory sources
    COMMAND ${CMAKE_COMMAND} ..
    COMMENT "Updating top-level configuration ..."
    DEPENDEES install
    DEPENDERS build
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
  )

else (NOT YAZ_FOUND OR YAZ_FORCE_BUILD)

  add_custom_target (yaz
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "[yaz] Found system-wide installation; skipping rebuild!"
    )

endif (NOT YAZ_FOUND OR YAZ_FORCE_BUILD)
