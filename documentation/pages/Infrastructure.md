Infrastructure    {#infrastructure}
==============

\tableofcontents

  - \subpage homepage
  - \subpage wiki
  - \subpage issue_tracker
  - \subpage repositories for software packages and documents
  - \subpage virtual_machines
  - \subpage pandora_deployment
  - \subpage pwsafe

\section network_configuration Network configuration

|  |  |
|------------------|------------------|
| CIDR             | 134.95.11.128/27 |
| Subnet mask      | 255.255.255.224  |
| Standard Gateway | 134.95.11.129    |
| Nameserver       | 134.95.127.1, 134.95.129.23, 134.95.19.48, 134.95.167.20 |


\section servers Servers

| Name                         | IP address    | Hosted service              |
|------------------------------|---------------|-----------------------------|
| www.prometheus-bildarchiv.de | 134.95.19.39  | [Image archive](http://www.prometheus-bildarchiv.de) |
| prometheus1.uni-koeln.de     | 134.95.80.11  | Production system               |
| prometheus2.uni-koeln.de     | 134.95.80.12  | Development system              |
| prometheus-test.uni-koeln.de | 134.95.80.13  |                                 |
| prometheus-db1               | 134.95.80.95  | Database server                 |
| prometheus-web1              | 134.95.80.96  | Web server                      |
| prometheus-srv1.uni-koeln.de | 134.95.80.160 | SVN server, Trac                |
| prometheus-srv2.uni-koeln.de | 134.95.80.161 | prometheus-app.uni-koeln.de     |
| prometheus-srv3.uni-koeln.de | 134.95.80.162 | Jekyll Commander, Documentation |
| prometheus-srv4.uni-koeln.de | 134.95.80.164 |                                 |

http://prometheus-test.uni-koeln.de/pandora-devel

\subsection servers_srv1 prometheus-srv1

NFS mounts:

\verbatim
prometheus1.uni-koeln.de:/var/local/prometheus/app/pandora/shared/index/production /var/local/prometheus/app/perseus-a/pandora_index/production nfs rsize=8192,ro,bg 0 0
prometheus2.uni-koeln.de:/var/local/prometheus/app/pandora/trunk/index/development /var/local/prometheus/app/perseus-a/pandora_index/development nfs rsize=8192,ro,bg 0 0
prometheus-web1.uni-koeln.de:/var/local/prometheus/data/images /var/local/prometheus/data/images nfs rsize=8192,ro,bg 0 0
\endverbatim

\subsection servers_srv2 prometheus-srv2

NFS mounts:

\verbatim
prometheus-web1.uni-koeln.de:/var/local/prometheus/web/log /var/local/prometheus/web/log nfs rsize=8192,ro,bg 0 0
prometheus-srv3.uni-koeln.de:/var/local/prometheus/web/log /var/local/prometheus/web/log-prometheus-web nfs rsize=8192,ro,bg 0 0
\endverbatim

\subsection servers_srv3 prometheus-srv3

 - [Capistrano](http://prometheus-srv3.uni-koeln.de/ruby-doc/capistrano)
 - [Ferret Search Library Documentation](http://prometheus-srv3.uni-koeln.de/ruby-doc/ferret)
 - [Ruby Core](http://prometheus-srv3.uni-koeln.de/ruby-doc/core)
 - [Ruby Standard Library Documentation](http://prometheus-srv3.uni-koeln.de/ruby-doc/core)

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

