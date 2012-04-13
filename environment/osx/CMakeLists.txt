

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
      mysql5-devel
      )
    
    ## Installation instructions for the package ___________
    
    ExternalProject_Add (InstallPackage_${varPackage}
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}
      DOWNLOAD_COMMAND ""
      CONFIGURE_COMMAND ""
      BUILD_COMMAND ""
      INSTALL_COMMAND ${PORT_EXECUTABLE} install ${varPackage}
      COMMENT "Installing MacPorts package ${varPackage} ..."
      )
   
    ## Connection with collective target ___________________
    
    add_dependencies (InstallPackages InstallPackage_${varPackage})
    
  endforeach (varPackage)
  
endif (PORT_EXECUTABLE)
