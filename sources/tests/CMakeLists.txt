
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

## ==============================================================================
##
##  Ruby test programs
##
## ==============================================================================

##____________________________________________________________________
##                                                  Build instructions

file (GLOB varTestsRuby Test*.rb)

foreach (varTest ${varTestsRuby})
  ## remove file extension
  get_filename_component (varFilename ${varTest} NAME_WE)
  ## register the test
  add_test (${varFilename} ${RUBY_EXECUTABLE} ${varTest})
endforeach (varTest)

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
      testSourceDump.cc
      testSourcesBeeskow.cc
      testSourcesKassel.cc
      testSourcesRobertinum.cc
      testSourcesTheolEik.cc
      testSourcesPPO.cc
      testApacheLogs.cc
      )
    ## remove file extension
    get_filename_component (varFilename ${test_with_boost} NAME_WE)
    ## compiler instructions
    add_executable (${varFilename} ${test_with_boost})
    ## linker instructions
    target_link_libraries (${varFilename} libprometheus ${Boost_LIBRARIES})
  endforeach (test_with_boost)

  if (xml_dump_beeskow)
    add_test (testSourcesBeeskow testSourcesBeeskow ${xml_dump_beeskow})
  endif (xml_dump_beeskow)

  if (xml_dump_kassel)
    add_test (testSourcesKassel testSourcesKassel ${xml_dump_kassel})
  endif (xml_dump_kassel)

  if (xml_dump_robertinum)
    add_test (testSourcesRobertinum testSourcesRobertinum ${xml_dump_robertinum})
  endif (xml_dump_robertinum)

  if (xml_dump_theoleik)
    add_test (testSourcesTheolEik testSourcesTheolEik ${xml_dump_theoleik})
  endif (xml_dump_theoleik)

  add_test (testSourcesPPO_db testSourcesPPO -db)

  if (xml_dump_ppo)
    add_test (testSourcesPPO_xml testSourcesPPO -xml ${xml_dump_ppo})
  endif (xml_dump_ppo)

  if (id_ppo)
    add_test (testSourcesPPO_idppo testSourcesPPO -idppo ${id_ppo})
    add_test (testSourcesPPO_db testSourcesPPO -db ${id_ppo})
  else (id_ppo)
    add_test (testSourcesPPO_db testSourcesPPO -db)
  endif (id_ppo)

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

  add_test (testXML testXML ${xml_dump_beeskow})

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
  add_test (testXMLTree testXMLTree ${xml_dump_beeskow})
endif (LIBXML2_FOUND)

## ==============================================================================
##
##  YAML test programs
##
## ==============================================================================

if (YAML_FOUND)

  ##__________________________________________________________________
  ## Build test programs

  foreach (test_yaml
      tEmitting.cc
      testConfigGems.cc
      testConfigTrustedProxies.cc
      testConfigUserRoles.cc
      testYamlReading.cc
      )

    ## Strip extension from filename
    get_filename_component (varFilename ${test_yaml} NAME_WE)

    ## compiler instructions
    add_executable (${varFilename} ${varFilename}.cc)

    ## linker instructions
    target_link_libraries (${varFilename} libprometheus)

  endforeach (test_yaml)

  ##__________________________________________________________________
  ## Testing

  add_test (tEmitting tEmitting)
  add_test (TestYamlReading TestYamlReading ${PROJECT_SOURCE_DIR}/data/tests)

  if (config_gems_yml)
    add_test (testConfigGems testConfigGems ${config_gems_yml})
  else (config_gems_yml)
    add_test (testConfigGems testConfigGems)
  endif (config_gems_yml)

  if (config_roles_yml)
    add_test (testConfigUserRoles testConfigUserRoles ${config_roles_yml})
  else (config_roles_yml)
    add_test (testConfigUserRoles testConfigUserRoles)
  endif (config_roles_yml)

  if (config_trusted_proxies_yml)
    add_test (testConfigTrustedProxies testConfigTrustedProxies ${config_trusted_proxies_yml})
  else (config_trusted_proxies_yml)
    add_test (testConfigTrustedProxies testConfigTrustedProxies)
  endif (config_trusted_proxies_yml)

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
