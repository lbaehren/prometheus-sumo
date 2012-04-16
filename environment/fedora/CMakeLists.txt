
##_______________________________________________________________________________
## Check for required tools

find_program (YUM_EXECUTABLE yum
  HINTS ${YARD_ROOT_DIR}  ${CMAKE_INSTALL_PREFIX}
  PATH_SUFFIXES bin
  )

##_______________________________________________________________________________
## Installation of the individual packages

if (YUM_EXECUTABLE)
  
  foreach (varPackage
      ruby
      rubygems
      rdoc
      ri
      irb
      eruby
      libxml2-devel
      mysql-server
      mysql-client
      mysql-devel
      apache2
      #  (mod_ruby???)
      postfix
      subversion
      subversion-tools
      libapache2-svn
      ImageMagick
      ImageMagick-devel 
      )
    
    ## Installation instructions for the package
    ExternalProject_Add (InstallPackage_${varPackage}
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}
      DOWNLOAD_COMMAND ""
      CONFIGURE_COMMAND ""
      BUILD_COMMAND ""
      INSTALL_COMMAND ${YUM_EXECUTABLE} install ${varPackage}
      COMMENT "Installing Fedorax package ${varPackage} ..."
      )
    
    ## Connection with collective target
    add_dependencies (InstallPackages InstallPackage_${varPackage})
    
  endforeach (varPackage)
  
endif (YUM_EXECUTABLE)
