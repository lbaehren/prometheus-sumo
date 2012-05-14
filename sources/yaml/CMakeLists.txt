
if (YAML_FOUND)

  ## location of header files
  include_directories (${YAML_INCLUDES})

  ##_____________________________________________________________________________
  ## Tests

  file (GLOB testsYAML t*.cc)

  foreach (testYAML ${testsYAML})

    ## Strip extension from filename
    get_filename_component (varFilename ${testYAML} NAME_WE)

    ## compiler instructions
    add_executable (${varFilename} ${varFilename}.cc)

    ## linker instructions
    target_link_libraries (${varFilename} ${YAML_LIBRARIES})

    ## test registration
    add_test (${varFilename} ${varFilename})

  endforeach (testYAML)
  
endif (YAML_FOUND)