
## === Build instructions for the test programs =================================

add_custom_target (testSources)

file (GLOB test_lib_sources *.cc)

foreach (_test ${test_lib_sources})

  ## Strip extension from filename
  get_filename_component (varFilename ${_test} NAME_WE)

  ## compiler instructions
  add_executable (${varFilename} ${varFilename}.cc)

  ## linker instructions
  target_link_libraries (${varFilename} libprometheus)

  ## Top-level target
  add_dependencies (testSources ${varFilename})

endforeach (_test)

## === Execution of the tests ===================================================

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

