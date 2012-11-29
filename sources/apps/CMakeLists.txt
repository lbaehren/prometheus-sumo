
## ==============================================================================
##
##  Build instructions
##
## ==============================================================================

file (GLOB apps_sources *.cc)

foreach (_app ${apps_sources})

  ## strip suffix from filename
  get_filename_component (_program ${_app} NAME_WE)
  ## compiler
  add_executable(${_program} ${_app})
  ## linker
  target_link_libraries (${_program} libprometheus)
  ## installation
  install (
    TARGETS ${_program}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    )

endforeach ()

## Testing

add_test (promManagePackages promManagePackages)
add_test (promManagePackages_config promManagePackages --config)
