
# Development

## Installation of a development system

The installation/configuration of a new development system/environment entails
a number of steps:

- Install required system packages
- Install Ruby gems
- Check out working copy of the source code
- Start up pandora

The sections below explain in further detail what needs do be done at each of the
steps along the way. If you are more interesting in learning about
{file:Testing Testing}, please visit the separate page on that topic.

### Required system packages

If you are using the ``prometheus-sumo`` package_ you can run the following
commands, in order to handle the installation of the required packages

    make InstallPackages

#### ... on Debian GNU/Linux

  * ruby``<REQUIRED_VERSION_RUBY>``
  * ruby``<REQUIRED_VERSION_RUBY>``-dev
  * rubygems
  * rdoc
  * ri
  * irb
  * libmysql-ruby``<REQUIRED_VERSION_RUBY>``
  * libtermios-ruby``<REQUIRED_VERSION_RUBY>``
  * libopenssl-ruby``<REQUIRED_VERSION_RUBY>``
  * librmagick-ruby``<REQUIRED_VERSION_RUBY>``
  * mysql-server
  * mysql-client
  * libmysqlclient-dev
  * apache2
  * libapache2-mod-ruby
  * libapache2-mod-proxy-html
  * subversion
  * libxml2-dev
  * libmagic-dev
  * libmagickwand-dev

#### ... on RedHat

  * ruby
  * rubygems
  * rdoc
  * ri
  * irb
  * eruby
  * libxml2-devel
  * mysql-server
  * mysql-client
  * mysql-devel
  * apache2
  * postfix
  * subversion
  * subversion-tools
  * libapache2-svn
  * ImageMagick
  * ImageMagick-devel

## References 

* [Git SCM](http://git-scm.com)
* [Subversion](http://subversion.apache.org)
* [Doxygen](http://www.doxygen.org)
* [Markdown support with Doxygen](http://www.stack.nl/~dimitri/doxygen/markdown.html)
