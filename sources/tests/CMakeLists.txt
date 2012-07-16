
## ==============================================================================
##
##  C++ test programs
##
## ==============================================================================

file (GLOB varTestsCpp Test*.cc)

foreach (varTest ${varTestsCpp})
  ## remove file extension
  get_filename_component (varFilename ${varTest} NAME_WE)
  ## build executable of test program
  add_executable (${varFilename} ${varTest})
endforeach (varTest)

## ==============================================================================
##
##  Ruby test programs
##
## ==============================================================================

file (GLOB varTestsRuby Test*.rb)

foreach (varTest ${varTestsRuby})
  ## remove file extension
  get_filename_component (varFilename ${varTest} NAME_WE)
  ## register the test
  add_test (${varFilename} ${RUBY_EXECUTABLE} ${varTest})
endforeach (varTest)

## ==============================================================================
##
##  YAML test programs
##
## ==============================================================================

if (YAML_FOUND)

  ## location of header files
  include_directories (${YAML_INCLUDES})

  ## List of source files
  set (tests_yaml_sources
    tEmitting.cc
    tParseFixtures.cc
    )

  foreach (test_yaml ${tests_yaml_sources})

    ## Strip extension from filename
    get_filename_component (varFilename ${test_yaml} NAME_WE)

    ## compiler instructions
    add_executable (${varFilename} ${varFilename}.cc)

    ## linker instructions
    target_link_libraries (${varFilename} ${YAML_LIBRARIES})

    ## Default test setup
    add_test (${varFilename} ${varFilename})
    
  endforeach (test_yaml)
  
  ##_____________________________________________________________________________
  ## Additional tests requiring extra parameters
  
  add_test (tParseFixtures_roles tParseFixtures roles.yml)
  
endif (YAML_FOUND)