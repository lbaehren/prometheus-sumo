
## ==============================================================================
##
##  Required packages to be installed through the package manager
##
## ==============================================================================

##____________________________________________________________________
## Packages required on Debian GNU/Linux

if (DEBIAN_FOUND)
  
  set (required_packages
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
    subversion
    libxml2-dev
    libmagic-dev
    libmagickwand-dev
    )
  
endif (DEBIAN_FOUND)

##____________________________________________________________________
## Packages required on RedHat

if (REDHAT_FOUND)
  
  set (required_packages
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

endif (REDHAT_FOUND)

## ==============================================================================
##
##  Ruby Gems
##
## ==============================================================================

if (GEM_EXECUTABLE)

  add_custom_target (install_gems
    COMMAND gem install rake
    COMMAND gem install libxml-ruby
    COMMAND gem install hpricot
    COMMAND gem install json
    COMMAND gem install mongrel
    COMMAND gem install mongrel_cluster
    COMMAND gem install piston
    COMMAND gem install capistrano
    COMMAND gem install ruby-debug 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
  
endif (GEM_EXECUTABLE)
