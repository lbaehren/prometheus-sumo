
## ==============================================================================
##
##  CMake project settings
##
## ==============================================================================

##  Package information
set (YAZ_VERSION          "4.2.38" )
set (YAZ_VERSION_REQUIRED "400200380" )
set (YAZ_SOURCE_ARCHIVE "yaz-${YAZ_VERSION}.tar.gz" )
set (YAZ_URL            "http://ftp.indexdata.dk/pub/yaz/${YAZ_SOURCE_ARCHIVE}" )
set (YAZ_SVN            "" )

## ==============================================================================
##
##  Options
##
## ==============================================================================

option (YAZ_FORCE_BUILD    "Force build and installation of package?" NO )
option (YAZ_FROM_REPOS     "Install package from repository?"         NO )
option (YAZ_ENABLE_TESTING "Enable testing and experimental builds?"  YES )

## Handle options

if (YAZ_ENABLE_TESTING)
  include (CTest)
  enable_testing()
endif (YAZ_ENABLE_TESTING)

## If YAZ is installed as system package, check of the version is ok

if (YAZ_VERSION_STRING)

  message (STATUS "Checking whether YAZ version is ok")

  if (${YAZ_VERSION_STRING} LESS ${YAZ_VERSION_REQUIRED})
    ## Mark package as not found
    set (YAZ_FOUND FALSE)
    ## Clear existing variables from configuration cache
    unset (YAZ_INCLUDES          CACHE)
    unset (YAZ_LIBRARIES         CACHE)
    unset (YAZ_CLIENT_EXECUTABLE CACHE)
    unset (YAZ_CONFIG_EXECUTABLE CACHE)
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

  ExternalProject_Add_Step (yaz update_configuration
    COMMAND ${CMAKE_COMMAND} -E remove CMake*
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
