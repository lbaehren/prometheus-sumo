
message (STATUS "Processing directory source/tests")

## ==============================================================================
##
##  Generic C++ test programs
##
## ==============================================================================

foreach (test_cpp
  testCommon
  testImage
  )
  ## Compiler instructions
  add_executable (${test_cpp} ${test_cpp}.cc)
  ## Linker instructions
  target_link_libraries (${test_cpp} libprometheus)
  ## Testing
  add_test (${test_cpp} ${test_cpp})
endforeach (test_cpp)

##____________________________________________________________________
##                                              PoDoFo test program(s)

if (PODOFO_FOUND)
  ## compiler
  add_executable (testPoDoFo testPoDoFo.cc)
  ## linker
  target_link_libraries (testPoDoFo ${PODOFO_LIBRARIES})
endif (PODOFO_FOUND)

##____________________________________________________________________
##                                               KWsys test program(s)

if (KWSYS_FOUND)
  ## compiler
  add_executable (testKWSys testKWSys.cc)
  ## linker
  target_link_libraries (testKWSys ${KWSYS_LIBRARIES})
  ## testing
  add_test (testKWSys testKWSys)
endif (KWSYS_FOUND)

## ==============================================================================
##
##  XML test programs
##
## ==============================================================================

##__________________________________________________________
## Parsing via Boost library

if(Boost_FOUND)

  ## Header files
  include_directories(${Boost_INCLUDE_DIRS})

  foreach (test_with_boost
      testApacheLogs.cc
      )
    ## remove file extension
    get_filename_component (varFilename ${test_with_boost} NAME_WE)
    ## compiler instructions
    add_executable (${varFilename} ${test_with_boost})
    ## linker instructions
    target_link_libraries (${varFilename} libprometheus ${Boost_LIBRARIES})
  endforeach (test_with_boost)

  if (apache_access_log)
    add_test (testApacheLogs testApacheLogs ${apache_access_log})
  endif (apache_access_log)

endif()

##__________________________________________________________
## Parsing via TinyXML library

if (TINYXML_FOUND)

  ## Header files
  include_directories (${TINYXML_INCLUDES})
  ## Compiler instructions
  add_executable (testXML testXML.cc)
  ## Linker instructions
  target_link_libraries (testXML ${TINYXML_LIBRARIES})
  ## Test instructions
  if (xml_dump_beeskow)
    add_test (testXML testXML ${xml_dump_beeskow})
  endif (xml_dump_beeskow)
  
endif (TINYXML_FOUND)

##__________________________________________________________
## Parsing via libxml2 library

if (LIBXML2_FOUND)
  ## Header files
  include_directories (${LIBXML2_INCLUDE_DIR})
  ## Compiler instructions
  add_executable (testXMLTree testXMLTree.c)
  ## Linker instructions
  target_link_libraries (testXMLTree ${LIBXML2_LIBRARIES})
  ## Testing
  if (xml_dump_beeskow)
    add_test (testXMLTree testXMLTree ${xml_dump_beeskow})
  endif (xml_dump_beeskow)
endif (LIBXML2_FOUND)

## ==============================================================================
##
##  YAML test programs
##
## ==============================================================================

if (YAML_FOUND)

  ## compiler
  add_executable (testYAML testYAML.cc)
  ## linker
  target_link_libraries (testYAML libprometheus)
  ## testing
  add_test (testYAML_list  testYAML)
  add_test (testYAML_list  testYAML --list  ${PROJECT_SOURCE_DIR}/data/tests/yaml_List.yml)
  add_test (testYAML_array testYAML --array ${PROJECT_SOURCE_DIR}/data/tests/yaml_AssociativeArray.yml)
  add_test (testYAML_sequence testYAML --sequence ${PROJECT_SOURCE_DIR}/data/tests/yaml_ScalarsToSequences.yml)

  if (config_gems_yml)
    add_test (testYAML_packages_gems testYAML --packages ${config_gems_yml})
  endif (config_gems_yml)

  if (config_packages_debian_yml)
    add_test (testYAML_packages_debian testYAML --packages ${config_packages_debian_yml})
  endif (config_packages_debian_yml)

endif (YAML_FOUND)

## ==============================================================================
##
##  YAZ/YAZ++ test programs
##
## ==============================================================================

if (YAZPP_FOUND)

  ## Test data
  find_file (testYAZPP_data ppo.dump-mab
    PATHS ${PROJECT_SOURCE_DIR}
    PATH_SUFFIXES data data/tests
    )

  ## Compiler instructions
  add_executable (testYAZPP testYAZPP.cc)
  ## Linker instructions
  target_link_libraries (testYAZPP libprometheus)

  ## Testing
  if (testYAZPP_data)
    add_test (testYAZPP_convert testYAZPP ${testYAZPP_data})
  else (testYAZPP_data)
    add_test (testYAZPP testYAZPP)
  endif (testYAZPP_data)

endif (YAZPP_FOUND)

message (STATUS "Processing directory source/tests - done")

## === Project sub-directories ==================================================

add_subdirectory (Config)
add_subdirectory (Sources)
