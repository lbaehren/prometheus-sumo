

##_______________________________________________________________________________
## Check for required tools

find_program (PORT_EXECUTABLE port
  HINTS ${PORT_ROOT_DIR} ${CMAKE_INSTALL_PREFIX}
  PATH_SUFFIXES bin
  )

##_______________________________________________________________________________
## Installation of the individual packages

if (PORT_EXECUTABLE)

  if (config_packages_osx_yml)

    message (STATUS "Checking MacPorts installation ...")

    ## Initialize counters
    set (NOF_PACKAGES       0 )
    set (NOF_PACKAGES_FOUND 0 )

    ## Read configuration file with the list of required gems
    file (STRINGS ${config_packages_osx_yml} _configPackages
      REGEX "name:"
      )

    foreach (varPackage ${_configPackages})

      ## Extract the name of the gems from the line in the configuration file
      string (REGEX REPLACE "- name: " "" varPackage ${varPackage})

      ## Check if package if installed already _______________

      execute_process (
	COMMAND ${PORT_EXECUTABLE} list ${varPackage}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	RESULT_VARIABLE PORT_RESULT_VARIABLE
	OUTPUT_VARIABLE PORT_OUTPUT_VARIABLE
	ERROR_VARIABLE PORT_ERROR_VARIABLE
	OUTPUT_STRIP_TRAILING_WHITESPACE
	)

      ## Installation instructions for the package ___________

      if (PORT_OUTPUT_VARIABLE)
	message ("   [OK] ${varPackage}")
      else (PORT_OUTPUT_VARIABLE)
	message ("   [--] ${varPackage}")
	add_custom_command (
	  TARGET InstallPackages
	  POST_BUILD
	  COMMAND ${PORT_EXECUTABLE} install ${varPackage}
	  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	  COMMENT "Installing MacPorts package ${varPackage} ..."
	  )
      endif (PORT_OUTPUT_VARIABLE)

    endforeach (varPackage)

  else (config_packages_osx_yml)

    message (STATUS "Missing packages_osx.yml configuration file!")

  endif (config_packages_osx_yml)

endif (PORT_EXECUTABLE)
