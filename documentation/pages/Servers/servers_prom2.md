prometheus2.uni-koeln.de    {#servers_prom2}
========================

\tableofcontents

\section servers_prom2_data Hosted data

\verbatim
/var/local/prometheus
 |-- app
 |   |-- lost+found
 |   `-- pandora
 |-- backup
 |   |-- prometheus.khi
 |   `-- prometheus2.khi
 |-- bin
 |   `-- kleio
 |-- data
 |   |-- images
 |   |-- images-ro
 |   `-- pandora -> ../app/pandora/data
 |-- etc
 |   |-- khi
 |   |-- mongrel_cluster
 |   `-- web
 |-- lost+found
 |-- opt
 |-- srv
 |   `-- svn
 |       `-- pandora                         ...  Subversion repository for pandora
 |-- tmp
 |   |-- data
 |   `-- mod_proxy_balancer_by_busyness
 `-- web
     |-- etc -> ../etc/web
     |-- log
     `-- www
\endverbatim

\section servers_prom2_services Hosted services

* \ref subversion repository for \ref pandora

\verbatim
/
|-- etc
|   |-- inid.d
|   |   `-- mongrel_cluster             ...  Init script for the Mongrel cluster
|   `-- mongrel_cluster
|       |-- pandora_stable.conf
|       `-- pandora_staging.conf
`-- var
    `-- local
        `-- prometheus
            `-- app
                `-- pandora
                    |--stable           ...  Stable version of pandora application
                    `-- trunk           ...  Staging version of pandora application
\endverbatim

Related notes:

* \ref pandora_release_staging

\section servers_prom2_partitions Partitions

\subsection servers_prom2_partitions_local ... local

\verbatim
LABEL=/                 /                           ext3    defaults        1 1
/dev/lvr_vg/lv_tmp      /tmp                        ext3    defaults        1 2
/dev/lvr_vg/lv_afsc     /usr/vice/cache             ext2    defaults        1 2
/dev/lvr_vg/lv_var      /var                        ext3    defaults        1 2
/dev/lvr_vg/lv_service  /service                    ext3    defaults        1 2
tmpfs                   /dev/shm                    tmpfs   defaults        0 0
devpts                  /dev/pts                    devpts  gid=5,mode=620  0 0
sysfs                   /sys                        sysfs   defaults        0 0
proc                    /proc                       proc    defaults        0 0
LABEL=SWAP-sda2         swap                        swap    defaults        0 0
/dev/prom_vg/lv_mysql   /var/lib/mysql              ext3    defaults,acl    1 2
/dev/prom_vg/lv_base    /var/local/prometheus       ext3    defaults,acl    1 2
/dev/prom_vg/lv_app     /var/local/prometheus/app   ext3    defaults,acl    1 2
\endverbatim

\subsection servers_prom2_partitions_nfs ... NFS

\verbatim
prometheus1.uni-koeln.de:/var/local/prometheus/app/pandora/data /var/local/prometheus/app/pandora/data nfs rsize=8192,ro,bg 0 0
prometheus-web1.uni-koeln.de:/var/local/prometheus/data/images  /var/local/prometheus/data/images-ro   nfs rsize=8192,ro,bg 0 0
\endverbatim
