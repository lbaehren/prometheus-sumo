DILPS (Distributed Image Library Processing System)    {#dilps}
===================================================

\tableofcontents

\section dilps_about About

DILPS ist ein Bilddatenbanksystem zur Verwaltung und Recherche digitaler Bilder. Es ist eine gemeinsame Entwicklung des Kunstgeschichtlichen Instituts der Universität Frankfurt, der Hochschule für Gestaltung und Kunst, Zürich (HGKZ) und der Staatlichen Hochschule für Gestaltung Karlsruhe.

Auf den Einsatz kommerzieller Software wurde vollständig verzichtet, um zu gewährleisten, dass das System ohne Lizenzkosten weitergegeben werden kann. Der Zugriff auf DILPS erfolgt ausschließlich über eine Web-Oberfläche mit üblichen Webbrowsern (Internet-Explorer, Netscape Navigator, Mozilla, Opera, Konquerer, …). Die Daten werden in relationalen Tabellen in MySQL gespeichert und via XML in andere Systeme exportiert. Um zu gewährleisten, dass die Daten auch auf andere Systeme migriert werden können, wird eine Exportfunktion angeboten, die die Erstellung von DVDs mit Bildern und Metadaten ermöglicht. Großer Wert wird bei der Entwicklung auf die Einbindung verschiedener Archive gelegt, um die Erweiterbarkeit und Zusammenfassbarkeit von lokalen und externen Archiven zu gewährleisten.

\section dilps_software Software

DILPS is a library for media database management. DILPS/W is a frontend for this library, which is implemented as a mediawiki extension with the aim of replacing the mediawiki file management subsystem with a much more elaborated media library.

The [source code](http://developer.berlios.de/projects/dilps) can be retrieved
via anonymous SVN access from the \ref subversion repository:

  \li via SVN:
\code
svn checkout svn://svn.berlios.de/dilps/trunk
\endcode
  \li via Git:
\code
git svn clone -s svn://svn.berlios.de/dilps dilps
\endcode

\section dilps_prom promDILPS

Since 2006, prometheus offers the use of the promDILPS image database free of charge. promDILPS is based on the software DILPS. Images and data record sets can be archived without having to use a server. All you need is a good scanner and a digital camera!

A fork of the DILPS code base that drives the prometheus promDILPS service is
[hosted on Github](https://github.com/prometheus-ev/promdilps). A copy of the
source code can be obtained via
\code
git clone git://github.com/prometheus-ev/promdilps.git promdilps
\endcode

promDILPS ist ein Service von uns, der Institutionen und Projekten, die eine Datenbank aufbauen möchten, aber selbst nicht die Möglichkeit haben selbst einen Server zu pflegen, die Möglichkeit bietet, auf unserem Server eine auf der Software DILPS basierte Datenbank aufzubauen. Bei diesen Kooperationen schließen wir einen Vertrag mit dem jeweiligen Partner ab, mit dem Ziel die Datenbank, die auf dem Server aufgebaut wird, in unser Bildarchiv einzubinden und so allen unseren Nutzern zur Verfügung zu stellen.

The minimum size for an image collection to be included into the prometheus digital image
archive is **1000 individual datasets**.

At this point in time the service cannot be rendered to private individuals. However
you can download, install and use the software (which itself is open-source) free
of charge for non-commercial purposes. Installation of the software is non-trivial and
no support is available at this point.

DILPS is a rather simple and flat database, not offering the possibility to
interconnect datasets based on an object-oriented approach, i.e. attaching
multiple images to a given object.
