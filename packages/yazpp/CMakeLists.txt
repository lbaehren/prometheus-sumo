
## ==============================================================================
##
##  CMake project settings
##
## ==============================================================================

# YAZ++ is an application programming interface (API) to YAZ which supports
# the development of Z39.50/SRW/SRU client and server applications using C++.
# Like YAZ, it supports Z39.50-2003 (version 3) as well as SRW/SRU version 1.1
# in both the client and server roles. YAZ++ includes an implementation of the
# ZOOM C++ binding and a generic client/server API based on the Observer/Observable
# design pattern.

##  Package information
set (YAZPP_VERSION        "1.3.2" )
set (YAZPP_SOURCE_ARCHIVE "yazpp-${YAZPP_VERSION}.tar.gz" )
set (YAZPP_URL            "http://ftp.indexdata.dk/pub/yazpp/${YAZPP_SOURCE_ARCHIVE}" )
set (YAZPP_SVN            "" )

## ==============================================================================
##
##  Options
##
## ==============================================================================

option (YAZPP_FORCE_BUILD    "Force build and installation of package?" NO )
option (YAZPP_FROM_REPOS     "Install package from repository?"         NO )
option (YAZPP_ENABLE_TESTING "Enable testing and experimental builds?"  YES )

## Handle options

if (YAZPP_ENABLE_TESTING)
  include (CTest)
  enable_testing()
endif (YAZPP_ENABLE_TESTING)

## ==============================================================================
##
##  Build instructions
##
## ==============================================================================

if (NOT YAZPP_FOUND OR YAZPP_FORCE_BUILD)

  ## Locate source file to build from

  find_file (YAZPP_SOURCE ${YAZPP_SOURCE_ARCHIVE}
    PATHS ${CMAKE_CURRENT_SOURCE_DIR}
    )

  if (NOT YAZPP_SOURCE)
    set (YAZPP_SOURCE ${YAZPP_URL})
  endif (NOT YAZPP_SOURCE)

  ## Settings to build against YAZ library

  if (YAZ_CONFIG_EXECUTABLE)
    get_filename_component(YAZ_CONFIG ${YAZ_CONFIG_EXECUTABLE} PATH)
  else (YAZ_CONFIG_EXECUTABLE)
    set (YAZ_CONFIG ${CMAKE_INSTALL_PREFIX}/bin)
  endif (YAZ_CONFIG_EXECUTABLE)

  ## Build package from source

  if (YAZPP_FROM_REPOS)

    ExternalProject_Add (yazpp
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      SVN_REPOSITORY ${YAZPP_SVN}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ${CMAKE_CURRENT_BINARY_DIR}/source/configure --prefix=${CMAKE_INSTALL_PREFIX} --with-yaz=${YAZ_CONFIG}
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )

  else (YAZPP_FROM_REPOS)

    ExternalProject_Add (yazpp
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      URL ${YAZPP_SOURCE}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ${CMAKE_CURRENT_BINARY_DIR}/source/configure --prefix=${CMAKE_INSTALL_PREFIX} --with-yaz=${YAZ_CONFIG}
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )

  endif (YAZPP_FROM_REPOS)

  ExternalProject_Add_Step (yazpp update_configuration
    COMMAND ${CMAKE_COMMAND} -E remove CMake*
    COMMAND ${CMAKE_COMMAND} ..
    COMMENT "Updating top-level configuration ..."
    DEPENDEES install
    DEPENDERS build
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
  )

else (NOT YAZPP_FOUND OR YAZPP_FORCE_BUILD)

  add_custom_target (yazpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "[yazpp] Found system-wide installation; skipping rebuild!"
    )

endif (NOT YAZPP_FOUND OR YAZPP_FORCE_BUILD)
