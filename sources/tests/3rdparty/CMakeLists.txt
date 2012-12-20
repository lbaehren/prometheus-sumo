
## ==============================================================================
##
##  Test working with KWSys library
##
## ==============================================================================

add_executable (testKWSys testKWSys.cc)
add_dependencies (testKWSys kwsys)

if (KWSYS_LIBRARIES)
  target_link_libraries (testKWSys ${KWSYS_LIBRARIES})
endif (KWSYS_LIBRARIES)

## --- Testing ---

add_test (testKWSys testKWSys)

## ==============================================================================
##
##  Test working with libXML2 library
##
## ==============================================================================

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
##  Test working with OpenCV library
##
## ==============================================================================

if (OPENCV_FOUND)

  add_executable (testOpenCV testOpenCV.cc)
  include_directories (${OPENCV_INCLUDES})
  target_link_libraries (testOpenCV ${OPENCV_LIBRARIES})

endif (OPENCV_FOUND)

## ==============================================================================
##
##  Test working with PoDoFo library
##
## ==============================================================================

if (PODOFO_FOUND)
  ## compiler
  add_executable (testPoDoFo testPoDoFo.cc)
  ## linker
  target_link_libraries (testPoDoFo ${PODOFO_LIBRARIES})
endif (PODOFO_FOUND)

## ==============================================================================
##
##  Test working with TinyXML library
##
## ==============================================================================

add_executable (testXML testXML.cc)

if (TINYXML_LIBRARIES)
  target_link_libraries (testXML ${TINYXML_LIBRARIES})
endif (TINYXML_LIBRARIES)

if (xml_dump_beeskow)
  add_test (testXML testXML ${xml_dump_beeskow})
endif (xml_dump_beeskow)

## ==============================================================================
##
##  Test working with YAML-C++ library
##
## ==============================================================================

add_executable (testYAML testYAML.cc)
add_dependencies (testYAML yaml-cpp)

if (YAML_LIBRARIES)
  target_link_libraries (testYAML ${YAML_LIBRARIES})
endif (YAML_LIBRARIES)

## --- Testing ---

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

if (config_packages_redhat_yml)
  add_test (testYAML_packages_redhat testYAML --packages ${config_packages_redhat_yml})
endif (config_packages_redhat_yml)

## ==============================================================================
##
##  Test working with YAZ++ library
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
