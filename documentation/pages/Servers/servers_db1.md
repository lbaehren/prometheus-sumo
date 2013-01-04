prometheus-db1.uni-koeln.de    {#servers_db1}
===========================

\tableofcontents

\section servers_db1_data Hosted data

~~~~
/var/local/prometheus
 ├── db
 │   └── backup
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

\section servers_db1_apps Hosted applications

~~~~
/var/local/prometheus
 └── app
    └── pandora
        ├── current -> /var/local/prometheus/app/pandora/releases/20121102164126
        ├── releases
        │   ├── 20120301102337
        │   ├── 20120323220813
        │   ├── 20120416143435
        │   ├── 20120531084421
        │   ├── 20120614220048
        │   ├── 20120614224217
        │   ├── 20120702105857
        │   ├── 20120723122405
        │   ├── 20120817124830
        │   └── 20121102164126
        └── shared
            ├── cache
            ├── codes
            ├── config
            ├── doc
            ├── index
            ├── log
            ├── pids
            └── system
~~~~