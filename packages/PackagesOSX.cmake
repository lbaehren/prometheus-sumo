

##_______________________________________________________________________________
## Check for required tools

find_program (PORT_EXECUTABLE port
  HINTS ${PORT_ROOT_DIR} ${CMAKE_INSTALL_PREFIX}
  PATH_SUFFIXES bin
  )

##_______________________________________________________________________________
## Installation of the individual packages

if (PORT_EXECUTABLE)
  
  ## List of packages ______________________________________

  foreach (varPackage
      mod_ruby
      mysql5-devel
      rb-rubygems
      ruby
      )

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
      message (STATUS "Checking whether port ${varPackage} is installed - yes")
    else (PORT_OUTPUT_VARIABLE)
      message (STATUS "Checking whether port ${varPackage} is installed - no")
      add_custom_command (
	TARGET InstallPackages
	POST_BUILD
	COMMAND ${PORT_EXECUTABLE} install ${varPackage}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Installing MacPorts package ${varPackage} ..."
	)
    endif (PORT_OUTPUT_VARIABLE)
    
  endforeach (varPackage)
  
endif (PORT_EXECUTABLE)
