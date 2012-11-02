
add_custom_target (InstallGems
  COMMENT "Installing required system packages..."
  )

find_package (RubyGems)

## Specific version
set (FERRET_REQUIRED_VERSION  "0.11.8.1" )
set (UNICODE_REQUIRED_VERSION "0.1.1"    )

##_______________________________________________________________________________
## Installation of the individual packages

if (GEM_EXECUTABLE)

  if (config_gems_yml)

    message (STATUS "Checking Ruby Gems")

    ## Read configuration file with the list of required gems
    file (STRINGS ${config_gems_yml} _configGems
      REGEX "name:"
      )

    ## Initialize counters
    set (NOF_GEMS       0 )
    set (NOF_GEMS_FOUND 0 )

    foreach (varPackage ${_configGems})

      ## Extract the name of the gems from the line in the configuration file
      string (REGEX REPLACE "- name: " "" varPackage ${varPackage})

      ## increment counter
      math (EXPR NOF_GEMS "${NOF_GEMS}+1")

      ##______________________________________________________
      ## In order to unnecessary installation processes, we
      ## first check if the Gem is installed already; if this
      ## this is the case, we skip over the package, otherwise
      ## it is added to the list available through the
      ## 'InstallGems' target.

      execute_process (
        COMMAND ${GEM_EXECUTABLE} list ${varPackage}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        RESULT_VARIABLE GEM_RESULT_VARIABLE
        OUTPUT_VARIABLE GEM_OUTPUT_VARIABLE
        ERROR_VARIABLE GEM_ERROR_VARIABLE
        OUTPUT_STRIP_TRAILING_WHITESPACE
      )

      if (GEM_OUTPUT_VARIABLE)

        ## Feedback
        if (CONFIGURE_VERBOSE)
          message ("   [OK] ${varPackage}")
        endif (CONFIGURE_VERBOSE)
        ## Counter update
        math (EXPR NOF_GEMS_FOUND "${NOF_GEMS_FOUND}+1")

      else (GEM_OUTPUT_VARIABLE)

        ## Feedback
        message ("   [--] ${varPackage}")
        ## Installation instructions
        add_custom_command (
          TARGET InstallGems
          POST_BUILD
          COMMAND export GEM_HOME=${CMAKE_INSTALL_PREFIX}/lib/ruby/gems/${RUBY_VERSION_SERIES}
          COMMAND ${GEM_EXECUTABLE} install ${varPackage}
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMENT "Installing Ruby Gem ${varPackage} ..."
        )

      endif (GEM_OUTPUT_VARIABLE)

    endforeach (varPackage)

  else (config_gems_yml)

    message (STATUS "Missing gems.yml configuration file!")

  endif (config_gems_yml)

  ##________________________________________________________
  ## Gems for which a specific version is required
  ## (see 'pandora/config/environment.rb')
  ##
  ## 'ferret'      => '= 0.11.8.1',
  ## 'libxml-ruby' => '>= 1.1.3',
  ## 'unicode'     => '>= 0.1.1'


  execute_process (
    COMMAND ${GEM_EXECUTABLE} list -i ferret -v ${FERRET_REQUIRED_VERSION}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    RESULT_VARIABLE GEM_RESULT_VARIABLE
    OUTPUT_VARIABLE GEM_OUTPUT_VARIABLE
    ERROR_VARIABLE GEM_ERROR_VARIABLE
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )

  if (${GEM_OUTPUT_VARIABLE} STREQUAL "false")
    add_custom_command (
      TARGET InstallGems
      POST_BUILD
      COMMAND ${GEM_EXECUTABLE} install ferret -v ${FERRET_REQUIRED_VERSION} --source http://prometheus-app.uni-koeln.de/rubygems
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Installing Ruby Gem ferret (${FERRET_REQUIRED_VERSION}) ..."
    )
  endif ()

  ## Summary of Gem check

  message (STATUS "Checking Ruby Gems - found ${NOF_GEMS_FOUND} of ${NOF_GEMS} packages")

endif (GEM_EXECUTABLE)
