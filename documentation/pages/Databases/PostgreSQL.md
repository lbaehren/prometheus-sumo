PostgreSQL    {#postgresql}
==========

\tableofcontents

\section postgresql_overview Overview

PostgreSQL is a powerful, open source object-relational database system. It has more than 15 years of active development and a proven architecture that has earned it a strong reputation for reliability, data integrity, and correctness. It runs on all major operating systems, including Linux, UNIX (AIX, BSD, HP-UX, SGI IRIX, Mac OS X, Solaris, Tru64), and Windows. It is fully ACID compliant, has full support for foreign keys, joins, views, triggers, and stored procedures (in multiple languages). It includes most SQL:2008 data types, including INTEGER, NUMERIC, BOOLEAN, CHAR, VARCHAR, DATE, INTERVAL, and TIMESTAMP. It also supports storage of binary large objects, including pictures, sounds, or video. It has native programming interfaces for C/C++, Java, .Net, Perl, Python, Ruby, Tcl, ODBC, among others, and exceptional documentation.

An enterprise class database, PostgreSQL boasts sophisticated features such as Multi-Version Concurrency Control (MVCC), point in time recovery, tablespaces, asynchronous replication, nested transactions (savepoints), online/hot backups, a sophisticated query planner/optimizer, and write ahead logging for fault tolerance. It supports international character sets, multibyte character encodings, Unicode, and it is locale-aware for sorting, case-sensitivity, and formatting. It is highly scalable both in the sheer quantity of data it can manage and in the number of concurrent users it can accommodate. There are active PostgreSQL systems in production environments that manage in excess of 4 terabytes of data.

\section postgresql_architecture Architectural Fundamentals

Before we proceed, you should understand the basic PostgreSQL system architecture. Understanding how the parts of PostgreSQL interact will make this chapter somewhat clearer.

In database jargon, PostgreSQL uses a client/server model. A PostgreSQL session consists of the following cooperating processes (programs):

  * A server process, which manages the database files, accepts connections to the database from client applications, and performs database actions on behalf of the clients. The database server program is called postgres.
  * The user's client (frontend) application that wants to perform database operations. Client applications can be very diverse in nature: a client could be a text-oriented tool, a graphical application, a web server that accesses the database to display web pages, or a specialized database maintenance tool. Some client applications are supplied with the PostgreSQL distribution; most are developed by users.

As is typical of client/server applications, the client and the server can be on different hosts. In that case they communicate over a TCP/IP network connection. You should keep this in mind, because the files that can be accessed on a client machine might not be accessible (or might only be accessible using a different file name) on the database server machine.

The PostgreSQL server can handle multiple concurrent connections from clients. To achieve this it starts (“forks”) a new process for each connection. From that point on, the client and the new server process communicate without intervention by the original postgres process. Thus, the master server process is always running, waiting for client connections, whereas client and associated server processes come and go.

\section postgresql_references References

General information

* [PostgreSQL](http://www.postgresql.org) - The world's most advanced open source database
* [Wiki](http://wiki.postgresql.org/wiki)
* [Books](http://www.postgresql.org/docs/books)
* [PostgreSQL: Introduction and Concepts](http://www.postgresql.org/files/documentation/books/aw_pgsql)
* Chaos-Seminar PostgreSQL: [Video](http://prometheus.khi.uni-koeln.de/media/misc/dbms/cs-200611-postgres_video.mp4), [Slides](http://prometheus.khi.uni-koeln.de/media/misc/dbms/cs-200611-postgres_presentation.pdf)
* [Manuals](http://www.postgresql.org/docs/manuals) - [v8.3](http://www.postgresql.org/docs/8.3/interactive/index.html)

Performance

* [Chapter 25. High Availability, Load Balancing, and Replication](http://www.postgresql.org/docs/8.3/static/high-availability.html) (PostgreSQL 8.3 Documentation)
* [PostgreSQL 8.0 Performance Checklist](http://www.powerpostgresql.com/PerfList) - [webarchive](http://web.archive.org/web/20080207064312/http://www.powerpostgresql.com/PerfList)
* [PostgreSQL Hardware Performance Tuning](http://momjian.us/main/writings/pgsql/hw_performance/index.html)
* [Tuning PostgreSQL on your Dedicated Server](http://www.anchor.com.au/hosting/dedicated/Tuning_PostgreSQL_on_your_Dedicated_Server)
* [Faster IO for Ruby with Postgres](http://oldmoe.blogspot.com/2008/07/faster-io-for-ruby-with-postgres.html)
* [MySQL vs. PostgreSQL](http://www.wikivs.com/wiki/MySQL_vs_PostgreSQL)
* [MySQL vs. PostgreSQL](https://wiki.man.poznan.pl/perfsonar-mdm/index.php/Mysql_vs_postgres) (Detailed comparison)
* [PostgreSQL Gotchas](http://sql-info.de/postgresql/postgres-gotchas.html)
  * [MySQL Gotchas - 1](http://sql-info.de/mysql/gotchas.html)
  * [MySQL Gotchas - 2](http://discuss.fogcreek.com/joelonsoftware3/default.asp?cmd=show&ixPost=88368)

Conversion from other databases

* [Converting from MySQL to PostgreSQL](http://wiki.postgresql.org/wiki/Converting_from_other_Databases_to_PostgreSQL#MySQL)
* [Converting MySQL to PostgreSQL](http://en.wikibooks.org/wiki/Converting_MySQL_to_PostgreSQL)
* [Converting MySQL database to Postgresql](http://jmz.iki.fi/blog/programming/converting_mysql_database_to_postgresql)
* [Converted the site from MySQL to PostgreSQL](http://jamonation.com/node/734#comments)

Use cases

* [PostgreSQL@Amazon](http://www.amazon.de/s/url=search-alias%3Daps&field-keywords=PostgreSQL)
