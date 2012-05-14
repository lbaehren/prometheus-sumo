
if (YAML_FOUND)

  ## location of header files
  include_directories (${YAML_INCLUDES})

  ## List of source files
  file (GLOB testsYAML t*.cc)

  foreach (testYAML ${testsYAML})

    ## Strip extension from filename
    get_filename_component (varFilename ${testYAML} NAME_WE)

    ## compiler instructions
    add_executable (${varFilename} ${varFilename}.cc)

    ## linker instructions
    target_link_libraries (${varFilename} ${YAML_LIBRARIES})

    ## Default test setup
    add_test (${varFilename} ${varFilename})
    
  endforeach (testYAML)
  
  ##_____________________________________________________________________________
  ## Additional tests requiring extra parameters
  
  add_test (tParseFixtures_roles tParseFixtures roles.yml)
  
endif (YAML_FOUND)
