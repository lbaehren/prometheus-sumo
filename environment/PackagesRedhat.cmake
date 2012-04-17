
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

    add_custom_command (
      TARGET InstallPackages
      POST_BUILD
      COMMAND ${YUM_EXECUTABLE} install ${varPackage}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Installing Redhat package ${varPackage} ..."
      )

  endforeach (varPackage)
  
endif (YUM_EXECUTABLE)
