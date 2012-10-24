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

| IP address      | Hostname                     | Hosted service                       |
|-----------------|------------------------------|--------------------------------------|
| 134.95.19.39    | www.prometheus-bildarchiv.de | \ref manual_image_archive            |
| 134.95.80.11    | prometheus1.uni-koeln.de     | Production system                    |
| 134.95.80.12    | prometheus2.uni-koeln.de     | Development system                   |
| 134.95.80.13    | prometheus-test.uni-koeln.de | [pandora-devel](http://prometheus-test.uni-koeln.de/pandora-devel) |
| 134.95.80.95    | prometheus-db1.uni-koeln.de  | Database server                      |
| 134.95.80.96    | prometheus-web1.uni-koeln.de | Web server                           |
| 134.95.80.160   | \ref servers_srv1 | SVN server, Trac, \ref issue_tracker |
| 134.95.80.161   | \ref servers_srv2 | prometheus-app.uni-koeln.de          |
| 134.95.80.162   | \ref servers_srv3 | \ref homepage, \ref JekyllCommander, Documentation |
| 134.95.80.163   | \ref servers_srv4 |  |
| 134.95.167.124  | prometheus.khi.uni-koeln.de  |  |
| 134.95.167.125  | prometheus2.khi.uni-koeln.de |  |


\subsection servers_srv1 prometheus-srv1.uni-koeln.de

NFS mounts:

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
 - \ref JekyllCommander

Online documentation for various software projects:

 - [Capistrano](http://prometheus-srv3.uni-koeln.de/ruby-doc/capistrano)
 - [Ferret Search Library Documentation](http://prometheus-srv3.uni-koeln.de/ruby-doc/ferret)
 - [Ruby Core](http://prometheus-srv3.uni-koeln.de/ruby-doc/core)
 - [Ruby Standard Library Documentation](http://prometheus-srv3.uni-koeln.de/ruby-doc/core)

\subsection servers_srv4 prometheus-srv4.uni-koeln.de

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

\section nfs_mounts NFS mounts

 - prometheus1
 \verbatim
prometheus-web1.uni-koeln.de:/var/local/prometheus/data/images /var/local/prometheus/data/images nfs rsize=8192,ro,bg 0 0
 \endverbatim

 - prometheus2
 \verbatim
prometheus1.uni-koeln.de:/var/local/prometheus/app/pandora/data /var/local/prometheus/app/pandora/data nfs rsize=8192,ro,bg 0 0
prometheus-web1.uni-koeln.de:/var/local/prometheus/data/images /var/local/prometheus/data/images-ro nfs rsize=8192,ro,bg 0 0
 \endverbatim

