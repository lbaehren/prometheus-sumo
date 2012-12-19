
## ==============================================================================
##
##  CMake project settings
##
## ==============================================================================

##  Package information
set (KWSYS_VERSION        "" )
set (KWSYS_SOURCE_ARCHIVE "" )
set (KWSYS_URL            "" )
set (KWSYS_GIT            "git://public.kitware.com/KWSys.git" )

## ==============================================================================
##
##  Options
##
## ==============================================================================

option (KWSYS_FORCE_BUILD    "Force build and installation of package?" NO  )
option (KWSYS_FROM_REPOS     "Install package from repository?"         YES )
option (KWSYS_ENABLE_TESTING "Enable testing and experimental builds?"  YES )

## Handle options

if (KWSYS_ENABLE_TESTING)
  include (CTest)
  enable_testing()
endif (KWSYS_ENABLE_TESTING)

## ==============================================================================
##
##  System inspection
##
## ==============================================================================

find_package (KWSys)

## ==============================================================================
##
##  Build instructions
##
## ==============================================================================

if (NOT KWSYS_FOUND OR KWSYS_FORCE_BUILD)

  ## Locate source file to build from

  find_file (KWSYS_SOURCE ${KWSYS_SOURCE_ARCHIVE}
    PATHS ${CMAKE_CURRENT_SOURCE_DIR}
    )

  if (NOT KWSYS_SOURCE)
    set (KWSYS_SOURCE ${KWSYS_URL})
  endif (NOT KWSYS_SOURCE)

  ## Build package from source

  if (KWSYS_FROM_REPOS)

    ExternalProject_Add (kwsys
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      GIT_REPOSITORY ${KWSYS_GIT}
      CMAKE_ARGS -DKWSYS_INSTALL_BIN_DIR=${CMAKE_INSTALL_PREFIX}/bin -DKWSYS_INSTALL_LIB_DIR=${CMAKE_INSTALL_PREFIX}/lib -DKWSYS_INSTALL_INCLUDE_DIR=${CMAKE_INSTALL_PREFIX}/include
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )

  else (KWSYS_FROM_REPOS)

    ExternalProject_Add (kwsys
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      URL ${KWSYS_SOURCE}
      CMAKE_ARGS -DKWSYS_INSTALL_BIN_DIR=${CMAKE_INSTALL_PREFIX}/bin -DKWSYS_INSTALL_LIB_DIR=${CMAKE_INSTALL_PREFIX}/lib -DKWSYS_INSTALL_INCLUDE_DIR=${CMAKE_INSTALL_PREFIX}/include
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )

  endif (KWSYS_FROM_REPOS)

  ExternalProject_Add_Step (kwsys update_configuration
    COMMAND ${CMAKE_COMMAND} -E remove CMake*
    COMMAND ${CMAKE_COMMAND} -E remove_directory sources
    COMMAND ${CMAKE_COMMAND} ..
    COMMENT "Updating top-level configuration ..."
    DEPENDEES install
    DEPENDERS build
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
  )

else (NOT KWSYS_FOUND OR KWSYS_FORCE_BUILD)

  add_custom_target (kwsys
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "[KWSys] Found system-wide installation; skipping rebuild!"
    )

endif (NOT KWSYS_FOUND OR KWSYS_FORCE_BUILD)
