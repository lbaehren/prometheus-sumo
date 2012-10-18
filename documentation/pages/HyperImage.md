HyperImage    {#hyperimage}
==========

\tableofcontents

\section hyperimage_server Server installation

\li Install of Java 1.6
\code
sudo aptitude install sun-java6-jdk
\endcode

\li Installation of PostgreSQL (recommended: 8.3; here: 8.4)
\code
sudo aptitude install postgresql postgresql-client
\endcode
Edit configuration files:
\code
sudo vi /etc/postgresql/8.4/main/postgresql.conf
sudo vi /etc/postgresql/8.4/main/pg_hba.conf  # +hiwebservice_usr@<glassfish-host>:metaimage
sudo vi /root/.pgpass
 (+@@localhost:*:*:postgres:<pass>@@)
\endcode
Adjust access permissions:
\code
sudo chmod 600 /root/.pgpass
sudo vi /etc/sysctl.d/local.conf (+@@kernel.shmmax = 1073741824@@)
sudo sysctl -p /etc/sysctl.d/local.conf
\endcode
Restart data database server and create tables:
\code
sudo invoke-rc.d postgresql restart
psql -h <postgresql-host> -U postgres -c "CREATE ROLE hiwebservice_usr LOGIN ENCRYPTED PASSWORD '<PASS>'"
psql -h <postgresql-host> -U postgres -c 'CREATE DATABASE metaimage'
psql -h <postgresql-host> -U postgres -f mi_db.dump metaimage
\endcode

\section hyperimage_references References

\li [HyperImage homepage](http://www.uni-lueneburg.de/hyperimage/hyperimage)
\li [HyperImage Connector](http://apps.sourceforge.net/mediawiki/hyperimage/index.php?title=HIConnector)
\li [Software Design Description for the HIConnector](http://sourceforge.net/project/showfiles.php?group_id=237597&package_id=314700&release_id=669135)
\li [User's Manual for HyperImage Editor 2.0](http://hyperimage.cms.hu-berlin.de/2.0/manual/HIE2_Handbuch_1.0.pdf)
\li [Installation instructions for HIServer 1.0](http://prometheus-bildarchiv.de/wiki/uploads/KnowledgeBase/HIServer_Installation_Instructions-1.0.pdf)

