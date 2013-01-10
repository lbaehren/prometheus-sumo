prometheus-srv3.uni-koeln.de    {#servers_srv3}
============================

\tableofcontents

\section servers_srv3_services Hosted services

 - \ref homepage
 - \ref wiki
 - \ref JekyllCommander

\section servers_srv3_data Hosted data

\verbatim
/var/local/prometheus
 ├── app
 │   ├── promhp
 │   │   ├── config.yaml           ...  Configuration for the Application
 │   │   └── tmp                   ...  Temporary for individual users
 │   └── vimtips
 ├── bin
 │   └── kleio
 ├── etc
 │   ├── nagios
 │   ├── tsm
 │   └── web
 ├── lost+found
 ├── srv
 │   └── promhp                    ...  prometheus homepage
 │       ├── live                  ...  Live version of the website
 │       ├── promhp.git            ...  Git repository
 │       └── staging               ...  Staging version of website
 ├── tmp
 ├── usr
 │   ├── bin
 │   ├── lib
 │   └── share
 └── web
\endverbatim

\section servers_srv3_doc Hosted documentation

 - [prometheus-sumo](http://prometheus-srv3.uni-koeln.de/doc/prometheus-sumo)
 - [Capistrano](http://prometheus-srv3.uni-koeln.de/ruby-doc/capistrano)
 - [Ferret Search Library Documentation](http://prometheus-srv3.uni-koeln.de/ruby-doc/ferret)
 - [Ruby Core](http://prometheus-srv3.uni-koeln.de/ruby-doc/core)
 - [Ruby Standard Library Documentation](http://prometheus-srv3.uni-koeln.de/ruby-doc/core)

\verbatim
/var/local/prometheus
 └── web
     └── www
         └── ruby-doc
             ├── capistrano        ...  Capistrano utility and framework
             ├── core              ...  Ruby Core
             ├── ferret            ...  Ferret Search Library Documentation
             ├── globalize
             └── stdlib            ...  Ruby Standard Library Documentation
\endverbatim

