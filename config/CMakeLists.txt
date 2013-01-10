
##_______________________________________________________________________________
##                                          Pre-processing of configuration files

foreach (_configIN
    packages_debian.yml
    repositories.yml
    )
  configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/${_configIN}.in
    ${CMAKE_CURRENT_BINARY_DIR}/${_configIN}
    )
endforeach ()

##_______________________________________________________________________________
##                                                            Configuration files

file (GLOB config_yaml ${CMAKE_CURRENT_SOURCE_DIR}/*.yml ${CMAKE_CURRENT_BINARY_DIR}/*.yml)

foreach (_file ${config_yaml})

  ## Disect the filename ...
  get_filename_component (_path      ${_file} PATH)
  get_filename_component (_name      ${_file} NAME)
  get_filename_component (_filename  ${_file} NAME_WE)
  ## ... to define cache variable
  set (_fileVar "config_${_filename}_yml")

  ## Store path to configuration file in cache variable
  find_file (${_fileVar}
    NAMES ${_name}
    PATHS ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
    PATH_SUFFIXES config
    )

  ## Installation instructions
  install (
    FILES ${_file}
    DESTINATION etc/prometheus
    )

endforeach (_file)
