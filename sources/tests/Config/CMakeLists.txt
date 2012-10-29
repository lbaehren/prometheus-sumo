
## === Macro definitions ========================================================

macro (run_test_config _testName )

  message (STATUS "macro(run_test_config) : ARGC  = ${ARGC}")

  if (${ARGC} GREATER 1)
    add_test (${_testName} ${_testName} ${ARGV1})
  else (${ARGC} GREATER 1)
    add_test (${_testName} ${_testName})
  endif (${ARGC} GREATER 1)

endmacro(run_test_config)

## === Build instructions for the test programs =================================

file (GLOB test_lib_config *.cc)

foreach (test_yaml ${test_lib_config})

  ## Strip extension from filename
  get_filename_component (varFilename ${test_yaml} NAME_WE)

  ## compiler instructions
  add_executable (${varFilename} ${varFilename}.cc)

  ## linker instructions
  target_link_libraries (${varFilename} libprometheus)

endforeach (test_yaml)

## === Execution of the tests ===================================================

run_test_config (testConfigAccount        ${config_account_yml}         )
run_test_config (testConfigInstitution    ${config_institution_yml}     )
run_test_config (testConfigGems           ${config_gems_yml}            )
run_test_config (testConfigUserRoles      ${config_roles_yml}           )
run_test_config (testConfigTrustedProxies ${config_trusted_proxies_yml} )
run_test_config (testConfigColumnsFor )