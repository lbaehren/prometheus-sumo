
## ==============================================================================
##
##  Generic C++ tst programs
##
## ==============================================================================

foreach (test_cpp
    TestBoxes.cc
    TestCommon.cc
    )
  get_filename_component (varFilename ${test_cpp} NAME_WE)
  add_executable (${varFilename} ${test_cpp})
  add_test (${varFilename} ${varFilename})
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

if (TINYXML_FOUND)

  ## Header files
  include_directories (${TINYXML_INCLUDES})
  ## Compiler instructions
  add_executable (TestXML TestXML.cc)
  ## Linker instructions
  target_link_libraries (TestXML ${TINYXML_LIBRARIES})
  ## Testing
  add_test (TestXML TestXML)

endif (TINYXML_FOUND)

## ==============================================================================
##
##  YAML test programs
##
## ==============================================================================

if (YAML_FOUND)

  ## location of header files
  include_directories (${YAML_INCLUDES})

  ##__________________________________________________________________
  ## Build test programs

  foreach (test_yaml
      tEmitting.cc
      TestYamlReading.cc
      )
    
    ## Strip extension from filename
    get_filename_component (varFilename ${test_yaml} NAME_WE)

    ## compiler instructions
    add_executable (${varFilename} ${varFilename}.cc)

    ## linker instructions
    target_link_libraries (${varFilename} ${YAML_LIBRARIES})

  endforeach (test_yaml)

  ##_____________________________________________________________________________
  ## Testing

  add_test (tEmitting tEmitting)
  add_test (TestYamlReading TestYamlReading ${PROJECT_SOURCE_DIR}/data/tests)

endif (YAML_FOUND)
