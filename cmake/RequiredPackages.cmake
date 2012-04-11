
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
    libapache2-mod-proxy-html
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

## Packages required on Mac OS X

if (APPLE)

  set (required_packages
    mysql5-devel
    )

endif (APPLE)

## ==============================================================================
##
##  Apache configuration
##
## ==============================================================================

add_custom_target (apache_enable_modes
  COMMAND a2enmod rewrite
  COMMAND a2enmod proxy_balancer
  COMMAND a2enmod proxy_http
  COMMAND /etc/init.d/apache2 restart
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Enabling Apache modes ..."
  )

## ==============================================================================
##
##  Ruby Gems
##
## ==============================================================================

if (GEM_EXECUTABLE)

  add_custom_target (install_gems
    COMMAND gem install yard
    COMMAND gem install rake
    COMMAND gem install libxml-ruby
    COMMAND gem install hpricot
    COMMAND gem install json
    COMMAND gem install mongrel
    COMMAND gem install mongrel_cluster
    COMMAND gem install piston
    COMMAND gem install capistrano
    COMMAND gem install ruby-debug
    COMMAND gem install pdf-reader
    COMMAND gem install apache_secure_download
    COMMAND gem install apache_image_resizer
    COMMAND gem install ruby-nuggets
    COMMAND gem install libxml-ext 
    COMMAND gem install gruff
    COMMAND gem install blackwinter-gnuplot
    COMMAND gem install fastercsv
    COMMAND gem install highline
    COMMAND gem install ruby-backports
    COMMAND gem install ferret
    COMMAND gem install unicode
    COMMAND gem install mime-types
    COMMAND gem install ruby-filemagic
    COMMAND gem install mail
    COMMAND gem install ar_mailer
    COMMAND gem install lockfile
    COMMAND gem install oauth
    COMMAND gem install ruby-hmac
    COMMAND gem install wadl 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Installing Ruby Gems ..."
    )
  
endif (GEM_EXECUTABLE)
