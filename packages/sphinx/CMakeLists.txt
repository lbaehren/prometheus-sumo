
## ==============================================================================
##
##  Package information
##
## ==============================================================================

set (SPHINX_VERSION        "2.0.4" )
set (SPHINX_SOURCE_ARCHIVE "sphinx-${SPHINX_VERSION}-release.tar.gz" )
set (SPHINX_URL            "http://sphinxsearch.com/files/${SPHINX_SOURCE_ARCHIVE}" )
set (SPHINX_SVN            "http://sphinxsearch.googlecode.com/svn" )

## ==============================================================================
##
##  Options
##
## ==============================================================================

option (SPHINX_FORCE_BUILD    "Force build and installation of package?" NO )
option (SPHINX_FROM_REPOS     "Install package from repository?"         NO )

## ==============================================================================
##
##  System inspection
##
## ==============================================================================

#include (FindSPHINX)

## ==============================================================================
##
##  Build instructions
##
## ==============================================================================

if (SPHINX_FROM_REPOS)
  set (SPHINX_FORCE_BUILD TRUE)
endif (SPHINX_FROM_REPOS)

if (NOT SPHINX_FOUND OR SPHINX_FORCE_BUILD)

  ## Locate source file to build from

  find_file (SPHINX_SOURCE ${SPHINX_SOURCE_ARCHIVE}
    PATHS ${CMAKE_CURRENT_SOURCE_DIR}
    )

  if (NOT SPHINX_SOURCE)
    set (SPHINX_SOURCE ${SPHINX_URL})
  endif (NOT SPHINX_SOURCE)

  ## Configure patch file: due to a hack in the original configure file,
  ## the Autotools-based search for the iconv library tends to end up
  ## pointing to an inclomplete version.

  if (ICONV_INCLUDES)
    set (CONFIGURE_ICONV_INCLUDES ${ICONV_INCLUDES})
  else (ICONV_INCLUDES)
    set (CONFIGURE_ICONV_INCLUDES /usr/include)
  endif (ICONV_INCLUDES)

  if (ICONV_LIBRARY_PATH)
    set (CONFIGURE_ICONV_LIBRARY_PATH ${ICONV_LIBRARY_PATH})
  else (ICONV_LIBRARY_PATH)
    set (CONFIGURE_ICONV_LIBRARY_PATH /usr/lib)
  endif (ICONV_LIBRARY_PATH)

  configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/configure.patch.in
    ${CMAKE_CURRENT_BINARY_DIR}/configure.patch
    )

  ## Build package from source

  if (SPHINX_FROM_REPOS)

    ExternalProject_Add (sphinx
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      SVN_REPOSITORY ${SPHINX_SVN}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ${CMAKE_CURRENT_BINARY_DIR}/source/configure --prefix=${CMAKE_INSTALL_PREFIX}
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )

  else (SPHINX_FROM_REPOS)

    ExternalProject_Add (sphinx
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      URL ${SPHINX_SOURCE}
      BUILD_IN_SOURCE 1
      PATCH_COMMAND patch < ${CMAKE_CURRENT_BINARY_DIR}/configure.patch
      CONFIGURE_COMMAND ${CMAKE_CURRENT_BINARY_DIR}/source/configure --prefix=${CMAKE_INSTALL_PREFIX} --with-mysql-includes=${MYSQL_INCLUDES} --with-mysql-libs=${MYSQL_LIBRARY_PATH}
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )

  endif (SPHINX_FROM_REPOS)

  ## Update top-level project configuration
  ExternalProject_Add_Step (sphinx update_configuration
    COMMAND ${CMAKE_COMMAND} -E remove CMake*
    COMMAND ${CMAKE_COMMAND} ..
    COMMENT "Updating top-level configuration ..."
    DEPENDEES install
    DEPENDERS build
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
  )

else (NOT SPHINX_FOUND OR SPHINX_FORCE_BUILD)

  add_custom_target (sphinx
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "[sphinx] Found system-wide installation; skipping rebuild!"
    )

endif (NOT SPHINX_FOUND OR SPHINX_FORCE_BUILD)

