
## ==============================================================================
##
##  CMake project settings
##
## ==============================================================================

set (TINYXML2_VERSION        "" )
set (TINYXML2_SOURCE_ARCHIVE "" )
set (TINYXML2_URL            "" )
set (TINYXML2_GIT            "git://github.com/leethomason/tinyxml2.git" )

## ==============================================================================
##
##  Options
##
## ==============================================================================

option (TINYXML2_FORCE_BUILD    "Force build and installation of package?" NO  )
option (TINYXML2_FROM_REPOS     "Install package from repository?"         YES )

## ==============================================================================
##
##  Build instructions
##
## ==============================================================================

if (NOT TINYXML_FOUND OR TINYXML2_FORCE_BUILD)

  ## Locate source file to build from

  find_file (TINYXML2_SOURCE ${TINYXML2_SOURCE_ARCHIVE}
    PATHS ${PROJECT_SOURCE_DIR}
    )

  if (NOT TINYXML2_SOURCE)
    set (TINYXML2_SOURCE ${TINYXML2_URL})
  endif (NOT TINYXML2_SOURCE)

  ## Build package from source

  if (TINYXML2_FROM_REPOS)

    ExternalProject_Add (tinyxml2
      PREFIX ${PROJECT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      GIT_REPOSITORY ${TINYXML2_GIT}
      CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )

  else (TINYXML2_FROM_REPOS)

    ExternalProject_Add (tinyxml2
      PREFIX ${PROJECT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      URL ${TINYXML2_SOURCE}
      CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )

  endif (TINYXML2_FROM_REPOS)

  ## Update top-level project configuration
  ExternalProject_Add_Step (tinyxml2 update_configuration
    COMMAND ${CMAKE_COMMAND} -E remove CMakeCache.txt
    COMMAND ${CMAKE_COMMAND} ..
    COMMENT "Updating top-level configuration ..."
    DEPENDEES install
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
  )

else (NOT TINYXML_FOUND OR TINYXML2_FORCE_BUILD)

  add_custom_target (tinyxml2
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "[tinyxml2] Found system-wide installation; skipping rebuild!"
    )

endif (NOT TINYXML_FOUND OR TINYXML2_FORCE_BUILD)
