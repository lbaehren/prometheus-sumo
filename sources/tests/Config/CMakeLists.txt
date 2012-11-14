
## === Macro definitions ========================================================

macro (run_test_config _testName )

  if (${ARGC} GREATER 1)
    add_test (${_testName} ${_testName} ${ARGV1})
  else (${ARGC} GREATER 1)
    add_test (${_testName} ${_testName})
  endif (${ARGC} GREATER 1)

endmacro(run_test_config)

## === Build instructions for the test programs =================================

add_custom_target (testConfig)

file (GLOB test_lib_config *.cc)

foreach (_test ${test_lib_config})

  ## Strip extension from filename
  get_filename_component (varFilename ${_test} NAME_WE)

  ## compiler instructions
  add_executable (${varFilename} ${varFilename}.cc)

  ## linker instructions
  target_link_libraries (${varFilename} libprometheus)

  ## Top-level target
  add_dependencies (testConfig ${varFilename})

endforeach (_test)

## === Execution of the tests ===================================================

run_test_config (testConfigAccount          ${config_account_yml}           )
run_test_config (testConfigInstitution      ${config_institution_yml}       )
run_test_config (testConfigPackages         ${config_gems_yml}              )
run_test_config (testConfigUserRoles        ${config_roles_yml}             )
run_test_config (testConfigTrustedProxies   ${config_trusted_proxies_yml}   )
run_test_config (testConfigColumnsFor       ${config_source_yml}            )
run_test_config (testConfigRepositories     ${config_repositories_yml}      )
run_test_config (testConfigSource           ${config_source_yml}            )
run_test_config (testConfigVirtualMachines  ${config_virtual_machines_yml}  )

add_test (testConfigPackagesDebian testConfigPackages ${config_packages_debian_yml} )
add_test (testConfigPackagesOSX    testConfigPackages ${config_packages_osx_yml}    )
add_test (testConfigPackagesRedhat testConfigPackages ${config_packages_redhat_yml} )
