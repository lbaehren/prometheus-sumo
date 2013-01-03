
## ==============================================================================
##
##  Package information
##
## ==============================================================================

set (FERRET_VERSION        "0.11.8.1" )
set (FERRET_SOURCE_ARCHIVE "" )
set (FERRET_URL            "http://prometheus-app.uni-koeln.de/rubygems/${FERRET_SOURCE_ARCHIVE}" )
set (FERRET_GIT            "git://github.com/blackwinter/ferret.git" )

## ==============================================================================
##
##  Options
##
## ==============================================================================

option (FERRET_FORCE_BUILD    "Force build and installation of package?" NO  )
option (FERRET_FROM_REPOS     "Install package from repository?"         YES )

## ==============================================================================
##
##  Build instructions
##
## ==============================================================================

if (NOT FERRET_FOUND OR FERRET_FORCE_BUILD)

  ## Locate source file to build from

  find_file (FERRET_SOURCE ${FERRET_SOURCE_ARCHIVE}
    PATHS ${CMAKE_CURRENT_SOURCE_DIR}
    )

  if (NOT FERRET_SOURCE)
    set (FERRET_SOURCE ${FERRET_URL})
  endif (NOT FERRET_SOURCE)

  ## Build package from source

  if (FERRET_FROM_REPOS)

    ExternalProject_Add (ferret
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      GIT_REPOSITORY ${FERRET_GIT}
      CONFIGURE_COMMAND "" #rake ${CMAKE_CURRENT_BINARY_DIR}/source/ruby
      BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/source/ruby
      BUILD_COMMAND rake gem
      INSTALL_COMMAND sudo gem install ${CMAKE_CURRENT_BINARY_DIR}/source/ruby/pkg/ferret-${FERRET_VERSION}.gem
      )

  else (FERRET_FROM_REPOS)

    ExternalProject_Add (ferret
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      URL ${FERRET_SOURCE}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ${CMAKE_CURRENT_BINARY_DIR}/source/configure --prefix=${CMAKE_INSTALL_PREFIX}
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )

  endif (FERRET_FROM_REPOS)

else (NOT FERRET_FOUND OR FERRET_FORCE_BUILD)

  add_custom_target (ferret
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "[Ferret] Found system-wide installation; skipping rebuild!"
    )

endif (NOT FERRET_FOUND OR FERRET_FORCE_BUILD)
