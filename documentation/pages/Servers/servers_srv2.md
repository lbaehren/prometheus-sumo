prometheus-srv2.uni-koeln.de    {#servers_srv2}
============================

\tableofcontents

\section servers_srv2_data Hosted data

~~~~
/var/local/prometheus
 ├── bin
 ├── etc
 ├── opt
 ├── srv
 │   ├── ftp                            ...  FTP upload directory
 │   └── svn
 ├── tmp
 └── web
     └── www
~~~~

\section servers_srv2_services Hosted services

\section servers_srv2_nfs NFS mounts

\verbatim
prometheus-web1.uni-koeln.de:/var/local/prometheus/web/log /var/local/prometheus/web/log nfs rsize=8192,ro,bg 0 0
prometheus-srv3.uni-koeln.de:/var/local/prometheus/web/log /var/local/prometheus/web/log-prometheus-web nfs rsize=8192,ro,bg 0 0
\endverbatim

