
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
      ferret
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
  
endif (GEM_EXECUTABLE)
