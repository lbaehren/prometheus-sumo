##
##  Pre-processing of configuration files
##

configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/packages_debian.yml.in
  ${CMAKE_CURRENT_SOURCE_DIR}/packages_debian.yml
)

##
##  Configuration files
##

file (GLOB config_yaml *.yml)

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
    PATHS ${PROJECT_SOURCE_DIR}
    PATH_SUFFIXES config
    )

endforeach (_file)
