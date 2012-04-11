
## Packages required on Debian GNU/Linux

if (DEBIAN_FOUND)
  
  set (required_packages_debian
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

## Packages required on RedHat

set (required_packages_redhat
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