
##____________________________________________________________________
## Check if an archive file with the database dumps is available

find_file (HAVE_DATA_PANDORA
  NAMES pandora.tgz pandora.tar.gz
  PATHS ${PROJECT_SOURCE_DIR} ${CMAKE_INSTALL_PREFIX}
  PATH_SUFFIXES pandora data/pandora app/pandora/data
)

##____________________________________________________________________
## Check of a directory with the database dumps exists

find_path (PANDORA_DATA_DIR
  NAMES arachne.xml dresden.xml heidicon.xml kassel.xml
  PATHS ${PROJECT_SOURCE_DIR} ${CMAKE_INSTALL_PREFIX}
  PATH_SUFFIXES pandora data/pandora app/pandora/data
  )

##____________________________________________________________________
## Set up path to directory with the database dumps

if (PANDORA_DATA_DIR)
  set (PANDORA_SOURCE_DUMPS ${PANDORA_DATA_DIR})
else (PANDORA_DATA_DIR)
  set (PANDORA_SOURCE_DUMPS "${CMAKE_INSTALL_PREFIX}/app/pandora/data")
endif (PANDORA_DATA_DIR)

configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/source.yml.in
  ${CMAKE_CURRENT_BINARY_DIR}/source.yml
  )

## ==============================================================================
##
##  Sub-directories
##
## ==============================================================================

add_subdirectory (repositories)
add_subdirectory (vm)

