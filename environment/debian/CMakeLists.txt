

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
  
  foreach (varPackage
      ruby
      ruby1.8-dev
      rubygems
      rdoc
      ri
      irb
      rails-ruby1.8
      libmysql-ruby
      libtermios-ruby
      libopenssl-ruby
      librmagick-ruby
      mysql-server
      mysql-client
      libmysqlclient-dev
      apache2
      libapache2-mod-ruby
      libapache2-mod-proxy-html
      subversion
      libxml2-dev
      libmagic-dev
      libmagickwand-dev
      )
    
    ## Check if the package is installed already ___________
    execute_process (
      COMMAND ${DPKG_EXECUTABLE} --get-selections
      COMMAND grep ${varPackage}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      RESULT_VARIABLE DPKG_RESULT_VARIABLE
      OUTPUT_VARIABLE DPKG_OUTPUT_VARIABLE
      ERROR_VARIABLE DPKG_ERROR_VARIABLE
      )
    
    ## Installation instructions for the package ___________
    add_custom_command (
      TARGET InstallPackages
      PRE_BUILD
      COMMAND ${APT_EXECUTABLE} install ${varPackage}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Installing Debian package ${varPackage} ..."
      )
    
#    ExternalProject_Add (InstallPackage_${varPackage}
#      PREFIX ${CMAKE_CURRENT_BINARY_DIR}
#      DOWNLOAD_COMMAND ""
#      CONFIGURE_COMMAND ""
#      BUILD_COMMAND ""
#      INSTALL_COMMAND ${APT_EXECUTABLE} install ${varPackage}
#      COMMENT "Installing Debian package ${varPackage} ..."
#      )
#   
#    ## Connection with collective target
#    add_dependencies (InstallPackages InstallPackage_${varPackage})
    
  endforeach (varPackage)
  
endif (APT_EXECUTABLE AND DPKG_EXECUTABLE)
