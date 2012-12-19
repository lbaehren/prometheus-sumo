
## ==============================================================================
##
##  Package information
##
## ==============================================================================

set (YAML_CPP_VERSION        "0.3.0" )
set (YAML_CPP_SOURCE_ARCHIVE "yaml-cpp-${YAML_CPP_VERSION}.tar.gz" )
set (YAML_CPP_URL            "http://yaml-cpp.googlecode.com/files/${YAML_CPP_SOURCE_ARCHIVE}" )
set (YAML_CPP_SVN            "" )

## ==============================================================================
##
##  Options
##
## ==============================================================================

option (YAML_CPP_FORCE_BUILD    "Force build and installation of package?" NO )
option (YAML_CPP_FROM_REPOS     "Install package from repository?"         NO )
option (YAML_CPP_ENABLE_TESTING "Enable testing and experimental builds?"  YES )

## Handle options

if (YAML_CPP_ENABLE_TESTING)
  include (CTest)
  enable_testing()
endif (YAML_CPP_ENABLE_TESTING)

## ==============================================================================
##
##  Build instructions
##
## ==============================================================================

if (YAML_CPP_FROM_REPOS)
  set (YAML_CPP_FORCE_BUILD TRUE)
endif (YAML_CPP_FROM_REPOS)

if (NOT YAML_CPP_FOUND OR YAML_CPP_FORCE_BUILD)

  ## Locate source file to build from

  find_file (YAML_CPP_SOURCE ${YAML_CPP_SOURCE_ARCHIVE}
    PATHS ${CMAKE_CURRENT_SOURCE_DIR}
    )

  if (NOT YAML_CPP_SOURCE)
    set (YAML_CPP_SOURCE ${YAML_CPP_URL})
  endif (NOT YAML_CPP_SOURCE)

  ## Build package from source

  if (YAML_CPP_FROM_REPOS)

    ExternalProject_Add (yaml-cpp
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      SVN_REPOSITORY ${YAML_CPP_SVN}
      CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )

  else (YAML_CPP_FROM_REPOS)

    ExternalProject_Add (yaml-cpp
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      URL ${YAML_CPP_SOURCE}
      CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )

  endif (YAML_CPP_FROM_REPOS)

  ## Update top-level project configuration
  ExternalProject_Add_Step (yaml-cpp update_configuration
    COMMAND ${CMAKE_COMMAND} -E remove CMake* sources
    COMMAND ${CMAKE_COMMAND} ..
    COMMENT "Updating top-level configuration ..."
    DEPENDEES install
    DEPENDERS build
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
  )

else (NOT YAML_CPP_FOUND OR YAML_CPP_FORCE_BUILD)

  add_custom_target (yaml-cpp
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "[yaml-cpp] Found system-wide installation; skipping rebuild!"
    )

endif (NOT YAML_CPP_FOUND OR YAML_CPP_FORCE_BUILD)
