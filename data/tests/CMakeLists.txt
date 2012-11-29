message (STATUS "Processing directory data/tests")

## === XML dumps from databases =================================================

find_file (xml_dump_beeskow beeskow_kunstarchiv.xml
  HINTS ${PANDORA_DATA_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
  PATHS ${PROJECT_SOURCE_DIR}/data
  PATH_SUFFIXES tests pandora pandora/data pandora/dumps
  )

find_file (xml_dump_theoleik theoleik.xml
  HINTS ${PANDORA_DATA_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
  PATHS ${PROJECT_SOURCE_DIR}/data
  PATH_SUFFIXES tests pandora pandora/data pandora/dumps
  )

find_file (xml_dump_kassel kassel.xml
  HINTS ${PANDORA_DATA_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
  PATHS ${PROJECT_SOURCE_DIR}/data
  PATH_SUFFIXES tests pandora pandora/data pandora/dumps
  )

find_file (xml_dump_robertinum robertin.xml
  HINTS ${PANDORA_DATA_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
  PATHS ${PROJECT_SOURCE_DIR}/data
  PATH_SUFFIXES tests pandora pandora/data pandora/dumps
  )

find_file (xml_dump_ppo ppo.xml
  HINTS ${PANDORA_DATA_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
  PATHS ${PROJECT_SOURCE_DIR}/data
  PATH_SUFFIXES tests pandora pandora/data pandora/dumps
  )

find_file (id_ppo idppo.txt
  HINTS ${PANDORA_DATA_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
  PATHS ${PROJECT_SOURCE_DIR}/data
  PATH_SUFFIXES tests pandora pandora/data pandora/dumps
)

## === Log files ================================================================

find_file (apache_access_log apache_access.log
  PATHS ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}
  PATH_SUFFIXES data data/tests
  )

message (STATUS "Processing directory data/tests - done")

