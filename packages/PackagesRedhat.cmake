
##_______________________________________________________________________________
## Check for required tools

find_program (YUM_EXECUTABLE yum
  HINTS ${YARD_ROOT_DIR}  ${CMAKE_INSTALL_PREFIX}
  PATH_SUFFIXES bin
  )

##_______________________________________________________________________________
## Installation of the individual packages

if (YUM_EXECUTABLE)

  if (config_packages_redhat_yml)

    message (STATUS "Checking Redhat packages")

    ## Initialize counters
    set (NOF_PACKAGES       0 )
    set (NOF_PACKAGES_FOUND 0 )

    ## Read configuration file with the list of required gems
    file (STRINGS ${config_packages_redhat_yml} _configPackages
      REGEX "name:"
      )

    foreach (varPackage ${config_packages_redhat_yml})

      ## Extract the name of the gems from the line in the configuration file
      string (REGEX REPLACE "- name: " "" varPackage ${varPackage})

      ## Installation instructions for the package
      add_custom_command (
	TARGET InstallPackages
	POST_BUILD
	COMMAND ${YUM_EXECUTABLE} install ${varPackage}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Installing Redhat package ${varPackage} ..."
	)
      
    endforeach (varPackage)

    else (config_packages_redhat_yml)

      message (STATUS "Missing packages_redhat.yml configuration file!")
    
    endif (config_packages_redhat_yml)

endif (YUM_EXECUTABLE)
