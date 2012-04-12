

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
      ruby
      ruby1.8-dev
      rubygems
      rdoc
      ri
      irb
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
    
    ## Installation instructions for the package
    ExternalProject_Add (InstallPackage_${varPackage}
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}
      CONFIGURE_COMMAND ""
      BUILD_COMMAND ""
      INSTALL_COMMAND ${APT_EXECUTABLE} install ${varPackage}
      COMMENT "Installing Debian package ${varPackage} ..."
      )
    
    ## Connection with collective target
    add_dependencies (InstallPackages InstallPackage_${varPackage})
    
  endforeach (varPackage)
  
endif (APT_EXECUTABLE)
