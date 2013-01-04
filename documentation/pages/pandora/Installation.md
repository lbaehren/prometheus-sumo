
Installation instructions    {#pandora_install}
=========================

\tableofcontents

\section pandora_install_overview Overview

The installation and configuration of a new \ref pandora system -- whether it is
for development or as a production environment -- entails a number of steps:

1. \ref pandora_install_packages
2. \ref pandora_install_gems
3. \ref pandora_install_checkout
4. \ref pandora_install_setup
5. \ref pandora_install_startup

The sections below explain in further detail what needs do be done at each of the
steps along the way.

\section pandora_install_steps Installation steps

\subsection pandora_install_packages Installation of system packages

Update systen Ruby gems

\verbatim
sudo gem update --system
\endverbatim

On Debian:

\verbatim
sudo env REALLY_GEM_UPDATE_SYSTEM=1 gem update --system
\endverbatim

Enable Apache modules using the \c a2enmod command - in order to actually activate
them, the web server needs to be restarted.

\verbatim
sudo a2enmod rewrite
sudo a2enmod proxy_balancer
sudo a2enmod proxy_http
sudo invoke-rc.d apache2 restart
\endverbatim

\subsection pandora_install_gems Installation of Ruby Gems

A list of the required Ruby gems is maintained in `./config/gems.yml`:

\include gems.yml

Notes:

\li If MySQL development files are not found automatically, specify them as command
line parameters:
\verbatim
sudo gem install mysql -- --with-mysql-include=/usr/include/mysql --with-mysql-lib=/usr/lib64/mysql
\endverbatim

\li On RHEL5 (ImageMagick < 6.3):
\verbatim
sudo gem install rmagick -v 1.15.13 -- --enable-allow-example-errors
\endverbatim
and remove
\code
<include file="type-windows.xml" />
\endcode
from `/usr/lib{,64}/ImageMagick-6.2.8/config/type.xml)`. 

\subsection pandora_install_checkout Checkout out the source code

Depending on what your personal/local choice for a version controll system is,
run one of the following commands:

\li **using Subversion**
\verbatim
svn co http://prometheus-srv.uni-koeln.de/svn/pandora pandora
\endverbatim

\li **using Git**
\verbatim
git svn clone -s http://prometheus-srv.uni-koeln.de/svn/pandora pandora
\endverbatim

A separate page \ref pandora_checkout provides additional information on other
checkout options, as well as a description of the resulting footprint of your
working copy.

\subsection pandora_install_setup Run the setup scripts

In order to initialize your \ref pandora installation, run the following from the
top-level directory of the \ref rails application

    rake pandora:setup

For a list of all available rake tasks type

    rake -T

\subsection pandora_install_startup Start up the server

In order to start up the application, simply run

    ./scripts/server

If everything went fine, you should be getting a status message like this

    ** Signals ready.  TERM => stop.  USR2 => restart.  INT => stop (no restart).
    ** Rails signals registered.  HUP => reload (without restart).  It might not work well.
    ** Mongrel 1.1.5 available at 0.0.0.0:3000
    ** Use CTRL-C to stop.

\section pandora_configuration Configuration scripts

Configuration scripts can be found in the standard location, i.e. within
the `config` directory:

\verbatim
pandora
`-- config
    |-- apache2.conf               ...  Configuration for Apache Web Server
    |-- database.yml               ...  Location of and access to database
    |-- environment.rb             ...  Inspection of the environment (checks dependencies)
    |-- secrets.yml                ...  Access secrets
    |-- app
    |   `-- source.yml             ...  Parameters for a database source
    |-- deploy
    |-- environments
    |-- initializers
    `-- src
\endverbatim

\subsection pandora_configuration_database Database

`./config/database.yml` defines the location of the underlying database, as well as the
access rights to it:

\code
    common: &common
      adapter:  <%= database_adapter %>
      encoding: <%= database_encoding %>
      host:     <%= database_host %>
      socket:   <%= database_socket %>
      username: <%= database_user %>
      password: <%= database_pass %>

    development: &development
      database: <%= database_name %>_development
      <<: *common
\endcode

\subsection pandora_configuration_sources Image archive sources

`./config/app/source.yml` defines the layout of the tables, storing information on an
external database, of which images (and their associated metadata) are available
through prometheus.

\code
    :dumps: /var/local/prometheus/app/pandora/data
    :paths: /var/local/prometheus/app/pandora/shared/paths_%s.marshal
    :change_pids: /var/local/prometheus/app/pandora/data/change_pids

    :kinds:
      - Institutional database
      - Research database
      - Museum database
\endcode

The first entry in the file (``:dumps:``) describes the path to the directory
containing database dumps; if no dumps can be found on your system, dummy
entries will be generated.
