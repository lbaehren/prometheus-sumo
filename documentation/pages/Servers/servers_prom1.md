prometheus1.uni-koeln.de    {#servers_prom1}
========================

\tableofcontents

\section servers_prom1_data Hosted data

\verbatim
/var/local/prometheus
 |-- app
 |   |-- lost+found
 |   `-- pandora
 |       |-- current -> releases/...         ...  Pointer to the current release
 |       |-- data                            ...  Dumps from the image databases
 |       |-- log
 |       |-- releases                        ...  Released versions of pandora
 |       |   |-- 20121102164126
 |       |   `-- 20121211141003
 |       |-- shared
 |       `-- stats
 |-- bin
 |   `-- kleio
 |-- data
 |   |-- images
 |   `-- pandora -> ../app/pandora/data
 |-- etc
 |   |-- mongrel_cluster
 |   `-- web
 |-- tmp
 |   |-- mod_proxy_balancer_by_busyness
 |   `-- pandora                        ...  Zip archives for download of images
 `-- web
     |-- etc -> ../etc/web
     |-- log
     `-- www
\endverbatim

\section servers_prom1_services Hosted services

* Production system of the \ref pandora application

\section servers_prom1_nfs NFS mounts

\verbatim
prometheus-web1.uni-koeln.de:/var/local/prometheus/data/images /var/local/prometheus/data/images nfs rsize=8192,ro,bg 0 0
 \endverbatim

