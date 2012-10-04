
Installation procedure    {#pandora_install}
======================

\tableofcontents

\section pandora_install_production ... for a production system

\subsection pandora_production_layout Directory layout

\verbatim
/var/local/prometheus
|-- app/pandora
|   |-- current -> ../releases/20120416143435        ...  Pointer to the current version
|   |-- data
|   |   `-- change_pids
|   |-- log                                          ...  Releases
|   |-- releases
|   |   |-- 20120323220813
|   |   `-- 20120416143435
|   |-- shared
|   |   |-- codes
|   |   |-- config
|   |   |-- doc
|   |   |-- index                                    ... Search index
|   |   |   `-- production
|   |   |       |-- 0_11_8
|   |   |       |   |-- image
|   |   |       |   |   |-- 1334932732
|   |   |       |   |   |-- 1336407501
|   |   |       |   |   `-- 1336491043
|   |   |       |   `-- resource
|   |   |       |       |-- 1327917072
|   |   |       |       |-- 1330708669
|   |   |       |       `-- 1331304781
|   |   |       `-- 0_11_8_1 -> 0_11_8
|   |   |-- log -> /var/log/prometheus
|   |   |-- pids
|   |   `-- system
|   `-- stats
`-- data
      |-- images
      `-- pandora -> ../app/pandora/data
\endverbatim

\section pandora_install_devel ... for a development system

The installation/configuration of a new development system/environment entails
a number of steps:

\li Install required system packages
\li Install Ruby gems
\li Check out working copy of the source code
\li Start up pandora

The sections below explain in further detail what needs do be done at each of the
steps along the way. If you are more interesting in learning about
\ref refman_pandora_testing, please skip to the section below.

\subsection pandora_configure_scripts Configuration scripts

Though the later \a setup script will take care of most of the required
configuration tasks -- most important of all the initial migration of the
database --

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

  \li \c database.yml defines the location of the underlying database, as well as
  the access rights to it:
  \verbatim
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
  \endverbatim

  \li \c app/source.yml defines the layout of the tables, storing information on an
  external database, of which images (and their associated metadata) are available
  through prometheus.
  \verbatim
    :dumps: /var/local/prometheus/app/pandora/data
    :paths: /var/local/prometheus/app/pandora/shared/paths_%s.marshal
    :change_pids: /var/local/prometheus/app/pandora/data/change_pids

    :kinds:
      - Institutional database
      - Research database
      - Museum database
  \endverbatim
  The first entry in the file (``:dumps:``) describes the path to the directory
  containing database dumps; if no dumps can be found on your system, dummy
  entries will be generated.

\subsection pandora_initialize_install Initialize the installation

In order to initialize your pandora installation, run the following from the
top-level directory of the \ref refman_rails application

\verbatim
rake pandora:setup
\endverbatim

For a list of all available rake tasks type

\verbatim
rake -T
\endverbatim

\subsection pandora_server_startup Starting up the server

Start up the server

\verbatim
./scripts/server
\endverbatim

If everything went fine, you should be getting a status message like this

\verbatim
** Signals ready.  TERM => stop.  USR2 => restart.  INT => stop (no restart).
** Rails signals registered.  HUP => reload (without restart).  It might not work well.
** Mongrel 1.1.5 available at 0.0.0.0:3000
** Use CTRL-C to stop.
\endverbatim