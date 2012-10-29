
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
