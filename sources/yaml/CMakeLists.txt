
if (YAML_FOUND)

  ## location of header files
  include_directories (${YAML_INCLUDES})

  ##_____________________________________________________________________________
  ## Tests

  foreach (testYaml
      tEmitting
      tParseAccount
      )

    ## compiler instructions
    add_executable (${testYaml} ${testYaml}.cc)

    ## linker instructions
    target_link_libraries (${testYaml} ${YAML_LIBRARIES})

    ## test registration
    add_test (${testYaml} ${testYaml})

  endforeach (testYaml)
  
endif (YAML_FOUND)