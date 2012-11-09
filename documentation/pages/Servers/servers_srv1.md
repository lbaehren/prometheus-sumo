prometheus-srv1.uni-koeln.de    {#servers_srv1}
============================

\tableofcontents

\section servers_srv1_data Hosted data

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

\section servers_srv1_services Hosted services

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

\section servers_srv1_nfs NFS mounts

\verbatim
prometheus1.uni-koeln.de:/var/local/prometheus/app/pandora/shared/index/production /var/local/prometheus/app/perseus-a/pandora_index/production nfs rsize=8192,ro,bg 0 0
prometheus2.uni-koeln.de:/var/local/prometheus/app/pandora/trunk/index/development /var/local/prometheus/app/perseus-a/pandora_index/development nfs rsize=8192,ro,bg 0 0
prometheus-web1.uni-koeln.de:/var/local/prometheus/data/images /var/local/prometheus/data/images nfs rsize=8192,ro,bg 0 0
\endverbatim

\section servers_srv1_cron Cronjobs

* \ref logwatch

~~~~
/etc
 ├── cron.d
 │   ├── apticron
 │   ├── atsar
 │   ├── php5
 │   ├── prometheus
 │   └── sysstat
 ├── cron.daily
 │   ├── 00logwatch
 │   ├── apache2
 │   ├── apt
 │   ├── apticron
 │   ├── aptitude
 │   ├── bsdmainutils
 │   ├── dpkg
 │   ├── gem_outdated -> /var/local/prometheus/bin/gem_outdated
 │   ├── logrotate
 │   ├── man-db
 │   ├── mlocate
 │   ├── ntp
 │   ├── passwd
 │   ├── samba
 │   ├── standard
 │   └── sysstat
 ├── cron.hourly
 ├── cron.monthly
 ├── crontab
 └── cron.weekly
     ├── apt-xapian-index
     ├── man-db
     ├── mysql_backup -> /var/local/prometheus/bin/mysql_backup
     └── pg_backup -> /var/local/prometheus/bin/pg_backup
~~~~
