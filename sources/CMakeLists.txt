
## Include directories

include_directories (
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
  ${CMAKE_CURRENT_BINARY_DIR}/lib
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/libcsv_parser++/include
  )

if (Boost_FOUND)
  ## Compiler flag(s)
  set (WITH_BOOST TRUE)
  ## Boost header files
  include_directories(${Boost_INCLUDE_DIRS})
  ## Linker instructions
  list (APPEND libprometheus_link_libraries ${Boost_LIBRARIES})
endif (Boost_FOUND)

if (MYSQL_FOUND)
  set (WITH_MYSQL TRUE)
endif (MYSQL_FOUND)

if (TINYXML_FOUND)
  set (WITH_TINYXML TRUE)
endif (TINYXML_FOUND)

if (YAML_FOUND)
  ## Compiler flag(s)
  set (WITH_YAML TRUE)
  ## YAML header files
  include_directories (${YAML_INCLUDES})
  ## Linker instructions
  list (APPEND libprometheus_link_libraries ${YAML_LIBRARIES})
endif (YAML_FOUND)

if (YAZPP_FOUND)
  ## Compiler flag(s)
  set (WITH_YAZPP TRUE)
  ## YAZ++ header files
  include_directories (${YAZPP_INCLUDES})
  ## Linker instructions
  list (APPEND libprometheus_link_libraries ${YAZPP_LIBRARIES})
endif (YAZPP_FOUND)

##_______________________________________________________________________________
## Sub-directories

add_subdirectory (lib)
add_subdirectory (apps)

if (ENABLE_TESTING)
  add_subdirectory (tests)
endif (ENABLE_TESTING)
