

##_______________________________________________________________________________
## Check for required tools

find_program (APT_EXECUTABLE apt-get
  HINTS ${APT_ROOT_DIR} ${CMAKE_INSTALL_PREFIX}
  PATH_SUFFIXES bin
  )

##_______________________________________________________________________________
## Installation of the individual packages

if (APT_EXECUTABLE)
  
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
    
    ## Installation instructions for the package
    add_custom_command (
      TARGET InstallPackages
      POST_BUILD
      COMMAND ${APT_EXECUTABLE} install ${varPackage}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Installing Ubuntu package ${varPackage} ..."
      )
    
  endforeach (varPackage)
  
endif (APT_EXECUTABLE)
