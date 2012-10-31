Servers    {#servers}
=======

\tableofcontents

\section network_configuration Network configuration

|  |  |
|------------------|------------------|
| CIDR             | 134.95.11.128/27 |
| Subnet mask      | 255.255.255.224  |
| Standard Gateway | 134.95.11.129    |
| Nameserver       | 134.95.127.1, 134.95.129.23, 134.95.19.48, 134.95.167.20 |


\section server_machines Server names and hosted services

| IP address      | Hostname                     | Hosted service             |
|-----------------|------------------------------|----------------------------|
| 134.95.19.39    | www.prometheus-bildarchiv.de | \ref image_archive         |
| 134.95.80.11    | \ref servers_prom1 | Production system                    |
| 134.95.80.12    | \ref servers_prom2 | Development system                   |
| 134.95.80.13    | prometheus-test.uni-koeln.de | [pandora-devel](http://prometheus-test.uni-koeln.de/pandora-devel) |
| 134.95.80.95    | \ref servers_db1  | Database server                      |
| 134.95.80.96    | \ref servers_web1 | Web server                           |
| 134.95.80.160   | \ref servers_srv1 | \ref subversion server, Trac, \ref redmine \ref issue_tracker |
| 134.95.80.161   | \ref servers_srv2 | prometheus-app.uni-koeln.de          |
| 134.95.80.162   | \ref servers_srv3 | \ref homepage, \ref JekyllCommander, Documentation |
| 134.95.80.163   | \ref servers_srv4 | \ref dilps databases |
| 134.95.167.124  | prometheus.khi.uni-koeln.de  |  |
| 134.95.167.125  | prometheus2.khi.uni-koeln.de |  |


\subsection servers_prom1 prometheus1.uni-koeln.de

* Hosting the production system of the \ref pandora application

\subsubsection servers_prom1_nfs NFS mounts

\verbatim
prometheus-web1.uni-koeln.de:/var/local/prometheus/data/images /var/local/prometheus/data/images nfs rsize=8192,ro,bg 0 0
 \endverbatim

\subsection servers_prom2 prometheus2.uni-koeln.de

\subsubsection servers_prom2_nfs NFS mounts

\verbatim
prometheus1.uni-koeln.de:/var/local/prometheus/app/pandora/data /var/local/prometheus/app/pandora/data nfs rsize=8192,ro,bg 0 0
prometheus-web1.uni-koeln.de:/var/local/prometheus/data/images /var/local/prometheus/data/images-ro nfs rsize=8192,ro,bg 0 0
\endverbatim

\subsection servers_db1 prometheus-db1.uni-koeln.de

\subsubsection servers_db1_data Hosted data

~~~~
/var/local/prometheus
 └── etc
     └── web
         ├── common
         │   ├── htpasswd
         │   ├── htpasswd-svn
         │   ├── httpd.conf
         │   ├── images.conf
         │   ├── modules.conf
         │   ├── prometheus.conf
         │   └── svn.conf
	 ├── prometheus-test.www
         │   ├── httpd.conf
         │   ├── modules.conf
         │   └── prometheus.conf
	 └── prometheus.www
             ├── httpd.conf
             ├── modules.conf
             └── prometheus.conf
~~~~

\subsection servers_web1 prometheus-web1.uni-koeln.de

\subsection servers_srv1 prometheus-srv1.uni-koeln.de

\subsubsection servers_srv1_data Hosted data

* prometheus access statistics
* Images for the \ref pandora application
* Database backups
* \ref virtual_machines

~~~~
/var/local/prometheus
 ├── app
 │   └── promstats             ...  prometheus access statistics
 ├── data
 │   └── images                ...  Images for the pandora application
 ├── db
 │   └── backup                ...  Database backups
 │       ├── mysql
 │       └── postgresql
 ├── tmp
 │   └── redesign2009          ...  Graphics assets for Redesign 2009
 └── web
     └── www
	 └── virtualbox        ...  VirtualBox VM images
~~~~

\subsubsection servers_srv1_services Hosted services

* \ref redmine issue tracker
* \ref pandora \ref subversion repository
* Trac issue tracker

~~~~
/var/local/prometheus
 ├── srv
 │   ├── git
 │   ├── redmine               ...  Redmine issue tracker
 │   ├── svn                   ...  Subversion repositories
 │   │   ├── athena
 │   │   ├── lingo
 │   │   ├── medusa
 │   │   ├── pandora           ...  pandora Subversion repository
 │   │   └── scratch
 │   └── trac                  ...  Trac issue tracker
 └── web
     └── www
	 └── redmine -> /var/local/prometheus/srv/redmine/public
~~~~

\subsubsection servers_srv1_nfs NFS mounts

\verbatim
prometheus1.uni-koeln.de:/var/local/prometheus/app/pandora/shared/index/production /var/local/prometheus/app/perseus-a/pandora_index/production nfs rsize=8192,ro,bg 0 0
prometheus2.uni-koeln.de:/var/local/prometheus/app/pandora/trunk/index/development /var/local/prometheus/app/perseus-a/pandora_index/development nfs rsize=8192,ro,bg 0 0
prometheus-web1.uni-koeln.de:/var/local/prometheus/data/images /var/local/prometheus/data/images nfs rsize=8192,ro,bg 0 0
\endverbatim

\subsection servers_srv2 prometheus-srv2.uni-koeln.de

NFS mounts:

\verbatim
prometheus-web1.uni-koeln.de:/var/local/prometheus/web/log /var/local/prometheus/web/log nfs rsize=8192,ro,bg 0 0
prometheus-srv3.uni-koeln.de:/var/local/prometheus/web/log /var/local/prometheus/web/log-prometheus-web nfs rsize=8192,ro,bg 0 0
\endverbatim

\subsection servers_srv3 prometheus-srv3.uni-koeln.de

Web-Applications:

 - \ref homepage
 - \ref wiki
 - \ref JekyllCommander

\subsubsection servers_srv3_doc Hosted documentation

 - [Capistrano](http://prometheus-srv3.uni-koeln.de/ruby-doc/capistrano)
 - [Ferret Search Library Documentation](http://prometheus-srv3.uni-koeln.de/ruby-doc/ferret)
 - [Ruby Core](http://prometheus-srv3.uni-koeln.de/ruby-doc/core)
 - [Ruby Standard Library Documentation](http://prometheus-srv3.uni-koeln.de/ruby-doc/core)

~~~~
/var/local/prometheus/web
└── www
    └── ruby-doc
        ├── capistrano        ...  Capistrano utility and framework
        ├── core              ...  Ruby Core
        ├── ferret            ...  Ferret Search Library Documentation
        ├── globalize
        └── stdlib            ...  Ruby Standard Library Documentation
~~~~

\subsection servers_srv4 prometheus-srv4.uni-koeln.de

 - \ref dilps databases

~~~~
/var/local/prometheus
└── web
    └── www
        └── dilps                  ...  Root directory of promDILPS installation
            ├── _base
            │   ├── admin
            │   ├── cache
            │   ├── export
            │   ├── images
            │   ├── include
            │   ├── skin
            │   ├── upload
            │   └── viewer
            ├── bern_iaw
            │   ├── admin
            │   ├── cache
            │   ├── export
            │   ├── images
            │   ├── include
            │   ├── skin
            │   ├── upload
            │   └── viewer
~~~~

\section virtual_hosts Virtual Hosts

Support for VM-Environment: vmqware@uni-koeln.de

\verbatim
    prometheus.khi.uni-koeln.de
        pandora
        pandora-devel
        pandora-test
        assets0.pandora
        assets1.pandora
        assets2.pandora
        assets3.pandora
        assets0.pandora-devel
        assets1.pandora-devel
        assets2.pandora-devel
        assets3.pandora-devel
        assets0.pandora-test
        assets1.pandora-test
        assets2.pandora-test
        assets3.pandora-test
        rlv
        foo
        bar
    prometheus.uni-koeln.de
        pandora
        pandora-devel
        pandora-test
        assets0.pandora
        assets1.pandora
        assets2.pandora
        assets3.pandora
    prometheus-test.uni-koeln.de
        pandora
        pandora-devel
        pandora-test
        assets0.pandora-devel
        assets1.pandora-devel
        assets2.pandora-devel
        assets3.pandora-devel
        assets0.pandora-test
        assets1.pandora-test
        assets2.pandora-test
        assets3.pandora-test
\endverbatim

\image html VMware_vSphere.png
