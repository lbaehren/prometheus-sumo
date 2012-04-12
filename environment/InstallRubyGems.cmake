
add_custom_target (InstallGems
  COMMENT "Installing required system packages..."
  )

##_______________________________________________________________________________
## Installation of the individual packages

if (GEM_EXECUTABLE)
  
  foreach (varPackage
      yard
      rake
      libxml-ruby
      hpricot
      json
      mongrel
      mongrel_cluster
      piston
      capistrano
      ruby-debug
      pdf-reader
      apache_secure_download
      apache_image_resizer
      ruby-nuggets
      libxml-ext 
      gruff
      blackwinter-gnuplot
      fastercsv
      highline
      ruby-backports
      unicode
      mime-types
      ruby-filemagic
      mail
      ar_mailer
      lockfile
      oauth
      ruby-hmac
      wadl 
      )
    
    ## Installation instructions for the package
    ExternalProject_Add (InstallGem_${varPackage}
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}
      DOWNLOAD_COMMAND ""
      CONFIGURE_COMMAND ""
      BUILD_COMMAND ""
      INSTALL_COMMAND ${GEM_EXECUTABLE} install ${varPackage}
      COMMENT "Installing Ruby Gem ${varPackage} ..."
      )
    
    ## Connection with collective target
    add_dependencies (InstallGems InstallGem_${varPackage})
    
  endforeach (varPackage)

  ##________________________________________________________
  ## Gems for which a specific version is required
  ## (see 'pandora/config/environment.rb')
  ## 
  ## 'ferret'      => '= 0.11.8.1',
  ## 'libxml-ruby' => '>= 1.1.3',
  ## 'unicode'     => '>= 0.1.1'

  ExternalProject_Add (InstallGem_ferret
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}
    DOWNLOAD_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ${GEM_EXECUTABLE} install ferret -v 0.11.8.1 --source http://prometheus-app.uni-koeln.de/rubygems
    COMMENT "Installing Ruby Gem ${varPackage} ..."
    )
  add_dependencies (InstallGems InstallGem_ferret)

endif (GEM_EXECUTABLE)
