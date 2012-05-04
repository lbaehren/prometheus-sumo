# MySQL

## About

### Deployment

MySQL can be built and installed manually from source code, but this can be tedious so it is more commonly installed from a binary package unless special customizations are required. On most Linux distributions the package management system can download and install MySQL with minimal effort, though further configuration is often required to adjust security and optimization settings.

Though MySQL began as a low-end alternative to more powerful proprietary databases, it has gradually evolved to support higher-scale needs as well. It is still most commonly used in small to medium scale single-server deployments, either as a component in a LAMP-based web application or as a standalone database server. Much of MySQL's appeal originates in its relative simplicity and ease of use, which is enabled by an ecosystem of open source tools such as phpMyAdmin. In the medium range, MySQL can be scaled by deploying it on more powerful hardware, such as a multi-processor server with gigabytes of memory.

### Forks

* {http://drizzle.org Drizzle} – a fork targeted at the web-infrastructure and cloud computing markets. The developers of the product describe it as a "smaller, slimmer and (hopefully) faster version of MySQL". As such is planned to have many common MySQL features stripped out, including stored procedures, query cache, prepared statements, views, and triggers. This is a complete rewrite of the server that does not maintain compatibility with MySQL.
* {http://mariadb.org MariaDB} – a community-developed branch of the MySQL database, the impetus being the community maintenance of its free status under GPL as opposed to any uncertainty of MySQL license status under its current ownership by Oracle. The intent also being to maintain high fidelity with MySQL, ensuring a "drop-in" replacement capability with library binary equivalency and exacting matching with MySQL APIs and commands. It includes the XtraDB storage engine as a replacement for InnoDB.
* {http://www.percona.com/software/percona-server Percona Server} – a fork that includes the XtraDB storage engine. It is an enhanced version of MySQL that is fully compatible, and deviates as little as possible from it, while still providing beneficial new features, better performance, and improved instrumentation for analysis of performance and usage.
* {http://ourdelta.org OurDelta} – a fork compiled with various patches, including patches from MariaDB, Percona, and Google.

## Usage

### Editing tables

Editing the attributes associated with an account also can be done from within MySQL directly:

    UPDATE `pandora_development`.`accounts` SET `addressline` = '<addressline>',
      `postalcode` = '<postalcode>',
      `city` = '<city>',
      `country` = '<country>',
      `status` = 'active' WHERE `accounts`.`id` =5;

For __Source__ entries:

    UPDATE `pandora_development`.`sources` SET `description` = '<text>' WHERE `sources`.`id` =1;

## Installation

### ... on Mac OS X

If you ar using {http://www.macports.org MacPorts}, you can retrieve and install
the server package via

    $ sudo port install mysql5-server

If this is a new install, in order to setup the database you might want to run:

    $ sudo -u _mysql mysql_install_db5

To start ``mysqld`` at boot time you have to copy ``support-files/mysql.server`` to
the right place for your system

PLEASE REMEMBER TO SET A PASSWORD FOR THE MySQL root USER !
To do so, start the server, then issue the following commands:

    $ /opt/local/lib/mysql5/bin/mysqladmin -u root password 'new-password'
    $ /opt/local/lib/mysql5/bin/mysqladmin -u root -h MacBook15inch.local password 'new-password'

Alternatively you can run:

    $ /opt/local/lib/mysql5/bin/mysql_secure_installation

which will also give you the option of removing the test databases and anonymous
user created by default.  This is strongly recommended for production servers.

See the manual for more instructions.

You can start the MySQL daemon with:

    $ cd /opt/local ; /opt/local/lib/mysql5/bin/mysqld_safe &

You can test the MySQL daemon with mysql-test-run.pl

    $ cd /opt/local/mysql-test ; perl mysql-test-run.pl

## References 

* {http://dev.mysql.com/doc/refman/5.0/en/charset-collation-effect.html Examples of the Effect of Collation} (mysql.com)
* {http://en.wikipedia.org/wiki/MySQL Wikipedia article}