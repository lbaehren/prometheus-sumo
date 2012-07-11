
## ==============================================================================
##
##  CVS dataset test programs
##
## ==============================================================================

## Parse CSV file with Boost Tokenizer

if (Boost_FOUND)

  ## Boost header files
  include_directories(${Boost_INCLUDE_DIRS})
  ## Compiler instructions
  add_executable(TestBoostTokenizerCSV TestBoostTokenizerCSV.cc)
  ## Linker instructions
  target_link_libraries (TestBoostTokenizerCSV prometheus)

endif ()

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
