

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

  message (STATUS "Checking Debian packages")

  ## Initialize counters
  set (NOF_PACKAGES       0 )
  set (NOF_PACKAGES_FOUND 0 )

  foreach (varPackage
      ruby${REQUIRED_VERSION_RUBY}
      ruby${REQUIRED_VERSION_RUBY}-dev
      rubygems
      ri
      rake
      libmysql-ruby${REQUIRED_VERSION_RUBY}
      libtermios-ruby${REQUIRED_VERSION_RUBY}
      librmagick-ruby${REQUIRED_VERSION_RUBY}
      libruby${REQUIRED_VERSION_RUBY}
      mysql-server
      mysql-client
      libmysqlclient-dev
      apache2
      libapache2-mod-ruby
      libapache2-mod-proxy-html
      subversion
      doxygen
      libboost-dev
      libxml2-dev
      libmagic-dev
      libmagickwand-dev
      )
    
    ## Inrement package counter
    math (EXPR NOF_PACKAGES "${NOF_PACKAGES}+1")

    ## Installation instructions for the package; check
    ## first, if the package is installed already __________

    execute_process (
      COMMAND ${DPKG_EXECUTABLE} --get-selections ${varPackage}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      RESULT_VARIABLE DPKG_RESULT_VARIABLE
      OUTPUT_VARIABLE DPKG_OUTPUT_VARIABLE
      ERROR_VARIABLE DPKG_ERROR_VARIABLE
      )
    
    if (DPKG_OUTPUT_VARIABLE)
      if (CONFIGURE_VERBOSE)
	message ("   [OK] ${varPackage}")
      endif (CONFIGURE_VERBOSE)
      math (EXPR NOF_PACKAGES_FOUND "${NOF_PACKAGES_FOUND}+1")
    else (DPKG_OUTPUT_VARIABLE)
      message ("   [--] ${varPackage}")
      add_custom_command (
	TARGET InstallPackages
	POST_BUILD
	COMMAND ${APT_EXECUTABLE} install ${varPackage}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Installing Debian package ${varPackage} ..."
	)
    endif (DPKG_OUTPUT_VARIABLE)
    
  endforeach (varPackage)

  ## Summary of package check

  message (STATUS "Checking Debian packages - found ${NOF_PACKAGES_FOUND} of ${NOF_PACKAGES} packages")
  
  ## Update the Ruby Gems
  
  add_custom_command (
    TARGET InstallPackages
    POST_BUILD
    COMMAND env REALLY_GEM_UPDATE_SYSTEM=1 gem update --system
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Updating Ruby gems ..."
    )
  
endif (APT_EXECUTABLE AND DPKG_EXECUTABLE)

