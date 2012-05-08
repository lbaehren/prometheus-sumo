
add_custom_target (InstallGems
  COMMENT "Installing required system packages..."
  )

##_______________________________________________________________________________
## Installation of the individual packages

if (GEM_EXECUTABLE)
  
  foreach (varPackage
      apache_image_resizer
      apache_secure_download
      ar_mailer
      blackwinter-gnuplot
      capistrano
      exifr
      fastercsv
      gruff
      highline
      hpricot
      jekyll
      jekyll-localization
      jekyll-pagination
      jekyll-tagging
      json
      libxml-ext 
      libxml-ruby
      lockfile
      mail
      mime-types
      mongrel
      mongrel_cluster
      mysql
      oauth
      pdf-reader
      piston
      rake
      redcarpet
      ruby-backports
      ruby-debug
      ruby-filemagic
      ruby-hmac
      ruby-nuggets
      unicode
      wadl 
      yard
      )

    add_custom_command (
      TARGET InstallGems
      POST_BUILD
      COMMAND ${GEM_EXECUTABLE} install ${varPackage}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Installing Ruby Gem ${varPackage} ..."
      )
    
  endforeach (varPackage)

  ##________________________________________________________
  ## Gems for which a specific version is required
  ## (see 'pandora/config/environment.rb')
  ## 
  ## 'ferret'      => '= 0.11.8.1',
  ## 'libxml-ruby' => '>= 1.1.3',
  ## 'unicode'     => '>= 0.1.1'
  
  add_custom_command (
    TARGET InstallGems
    POST_BUILD
    COMMAND ${GEM_EXECUTABLE} install ferret -v 0.11.8.1 --source http://prometheus-app.uni-koeln.de/rubygems
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Installing Ruby Gem ferret ..."
    )
  
endif (GEM_EXECUTABLE)
