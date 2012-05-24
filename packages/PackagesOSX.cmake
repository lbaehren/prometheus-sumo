

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
    
    ## Installation instructions for the package ___________
    
    add_custom_command (
      TARGET InstallPackages
      POST_BUILD
      COMMAND ${PORT_EXECUTABLE} install ${varPackage}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Installing MacPorts package ${varPackage} ..."
      )

  endforeach (varPackage)
  
endif (PORT_EXECUTABLE)
