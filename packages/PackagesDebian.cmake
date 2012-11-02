
##_______________________________________________________________________________
## Check for required tools

find_program (APT_EXECUTABLE apt-get
  HINTS ${APT_ROOT_DIR} ${CMAKE_INSTALL_PREFIX}
  PATH_SUFFIXES bin
  )

find_program (DPKG_EXECUTABLE dpkg
  HINTS ${APT_ROOT_DIR} ${CMAKE_INSTALL_PREFIX}
  PATH_SUFFIXES bin
  )

##_______________________________________________________________________________
## Installation of the individual packages

if (APT_EXECUTABLE AND DPKG_EXECUTABLE)

  if (config_packages_debian_yml)

    message (STATUS "Checking Debian packages")

    ## Initialize counters
    set (NOF_PACKAGES       0 )
    set (NOF_PACKAGES_FOUND 0 )

    ## Read configuration file with the list of required gems
    file (STRINGS ${config_packages_debian_yml} _configPackages
      REGEX "name:"
      )

    foreach (varPackage ${_configPackages})

      ## Inrement package counter
      math (EXPR NOF_PACKAGES "${NOF_PACKAGES}+1")

      ## Extract the name of the gems from the line in the configuration file
      string (REGEX REPLACE "- name: " "" varPackage ${varPackage})

      ## Installation instructions for the package; check
      ## first, if the package is installed already __________

      execute_process (
        COMMAND ${DPKG_EXECUTABLE} --get-selections ${varPackage}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        RESULT_VARIABLE DPKG_RESULT_VARIABLE
        OUTPUT_VARIABLE DPKG_OUTPUT_VARIABLE
        ERROR_VARIABLE DPKG_ERROR_VARIABLE
      )

      if (DPKG_OUTPUT_VARIABLE)

        ## Feedback
        if (CONFIGURE_VERBOSE)
          message ("   [OK] ${varPackage}")
        endif (CONFIGURE_VERBOSE)
        ## Increment counter
        math (EXPR NOF_PACKAGES_FOUND "${NOF_PACKAGES_FOUND}+1")

      else (DPKG_OUTPUT_VARIABLE)
        message ("   [--] ${varPackage}")
        add_custom_command (
          TARGET InstallPackages
          POST_BUILD
          COMMAND ${APT_EXECUTABLE} install ${varPackage}
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMENT "Installing Debian package ${varPackage} ..."
        )

      endif (DPKG_OUTPUT_VARIABLE)

    endforeach (varPackage)

  else (config_packages_debian_yml)

    message (STATUS "Missing packages_debian.yml configuration file!")

  endif (config_packages_debian_yml)

  ## Summary of package check

  message (STATUS "Checking Debian packages - found ${NOF_PACKAGES_FOUND} of ${NOF_PACKAGES} packages")

  ## Update the Ruby Gems

  add_custom_command (
    TARGET InstallPackages
    POST_BUILD
    COMMAND env REALLY_GEM_UPDATE_SYSTEM=1 gem update --system
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Updating Ruby gems ..."
    )

endif (APT_EXECUTABLE AND DPKG_EXECUTABLE)
