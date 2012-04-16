

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
      ruby${REQUIRED_VERSION_RUBY}
      ruby${REQUIRED_VERSION_RUBY}-dev
      rubygems
      rdoc
      ri
      irb
      libmysql-ruby${REQUIRED_VERSION_RUBY}
      libtermios-ruby${REQUIRED_VERSION_RUBY}
      libopenssl-ruby${${REQUIRED_VERSION_RUBY}}
      librmagick-ruby${REQUIRED_VERSION_RUBY}
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
      POST_BUILD
      COMMAND ${APT_EXECUTABLE} install ${varPackage}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Installing Debian package ${varPackage} ..."
      )

  endforeach (varPackage)
  
endif (APT_EXECUTABLE AND DPKG_EXECUTABLE)
