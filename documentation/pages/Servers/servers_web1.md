prometheus-web1.uni-koeln.de    {#servers_web1}
============================

\tableofcontents

\section servers_web1_services Hosted services

\section servers_web1_data Hosted data

\verbatim
/
|-- etc
|   `-- inid.d
|       |-- apache.init                      ...  Startup script for the Apache Web Server
|       |-- prometheus-test.www
|       `-- prometheus.www
`-- var/local/prometheus
    |-- app
    |   `-- pandora
    |       |-- current -> releases/20121211141003
    |       |-- releases
    |       |   |-- 20121102164126
    |       |   `-- 20121211141003
    |       `-- shared
    |-- bin
    |   `-- kleio
    |-- data
    |   |-- images
    |   `-- lost+found
    |-- etc
    |   `-- web                              ...  Apache configuration files
    |       |-- prometheus-test.www
    |       `-- prometheus.www
    |-- opt
    |-- tmp
    |   |-- mod_proxy_balancer_by_busyness
    |   `-- pandora_image_cache
    `-- web
        |-- etc -> ../etc/web
        |-- log
        `-- www
            |-- prometheus-test.www
            `-- prometheus.www
\endverbatim

\section servers_web1_partitions Partitions

\verbatim
LABEL=/                 /                           ext3    defaults        1 1
/dev/lvr_vg/lv_service  /service                    ext3    defaults        1 2
/dev/lvr_vg/lv_tmp      /tmp                        ext3    defaults        1 2
/dev/lvr_vg/lv_var      /var                        ext3    defaults        1 2
/dev/lvr_vg/lv_afsc     /usr/vice/cache             ext2    defaults        1 2
tmpfs                   /dev/shm                    tmpfs   defaults        0 0
devpts                  /dev/pts                    devpts  gid=5,mode=620  0 0
sysfs                   /sys                        sysfs   defaults        0 0
proc                    /proc                       proc    defaults        0 0
LABEL=SWAP-sda2         swap                        swap    defaults        0 0
LABEL=prom-web1_base    /var/local/prometheus       ext3    defaults,acl    1 2
LABEL=prom-web1_data    /var/local/prometheus/data  ext3    defaults,acl    1 2
\endverbatim

