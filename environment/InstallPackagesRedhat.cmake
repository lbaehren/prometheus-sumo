
##_______________________________________________________________________________
## Check for required tools

find_program (YUM_EXECUTABLE yum
  HINTS ${YARD_ROOT_DIR}  ${CMAKE_INSTALL_PREFIX}
  PATH_SUFFIXES bin
  )

##_______________________________________________________________________________
## 

foreach (package_redhat
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
  ExternalProject_Add (install_package_${package_redhat}
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ${YUM_EXECUTABLE} install ${package_redhat}
    COMMENT "Installing Redhat package ${package_redhat} ..."
    )

  ## Connection with collective target
  add_dependencies (InstallPackages install_package_${package_redhat})
  
endforeach (package_redhat)
