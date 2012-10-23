##
##  Configuration files
##

find_file (ruby_gems_yml
  NAMES ruby_gems.yml
  PATHS ${PROJECT_SOURCE_DIR}
  PATH_SUFFIXES config
  )

find_file (config_roles_yml
  NAMES roles.yml
  PATHS ${PROJECT_SOURCE_DIR}
  PATH_SUFFIXES config
  )

find_file (config_trusted_proxies_yml
  NAMES trusted_proxies.yml
  PATHS ${PROJECT_SOURCE_DIR}
  PATH_SUFFIXES config
  )

