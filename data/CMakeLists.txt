
## Check if an archive file with the database dumps is available

find_file (HAVE_DATA_PANDORA
  NAMES pandora.tgz pandora.tar.gz
)

## Check of a directory with the databas dumps exists

find_path (PANDORA_DATA_DIR
  NAMES arachne.xml dresden.xml heidicon.xml kassel.xml
  PATHS ${PROJECT_SOURCE_DIR} ${CMAKE_INSTALL_PREFIX}
  PATH_SUFFIXES pandora data/pandora app/pandora/data
  )

## 

if (PANDORA_DATA_DIR)
  set (PANDORA_SOURCE_DUMPS ${PANDORA_DATA_DIR})
else (PANDORA_DATA_DIR)
  set (PANDORA_SOURCE_DUMPS "${CMAKE_INSTALL_PREFIX}/app/pandora/data")
endif (PANDORA_DATA_DIR)

configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/source.yml.in
  ${CMAKE_CURRENT_BINARY_DIR}/source.yml
  )
