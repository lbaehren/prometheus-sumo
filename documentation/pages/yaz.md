YAZ    {#yaz}
===

\tableofcontents

 - [User's Guide and Reference](http://www.indexdata.com/yaz/doc)

\section yaz_toolkit YAZ programmers’ toolkit

[YAZ](http://www.indexdata.com/yaz) is a programmers’ toolkit supporting the
development of Z39.50/SRW/SRU clients and servers. Z39.50-2003 (version 3) as
well as SRW/SRU version 1.1 are supported in both the client and server roles.
The SOLR webservice is supported in the client role through the ZOOM API.

The current version of YAZ includes support for the industry standard ZOOM API
for Z39.50. This API vastly simplifies the process of writing new clients using
YAZ, and it reduces your dependency on any single toolkit.

YAZ can be used by itself to build Z39.50 applications in C. For programmers
preferring another language, YAZ has three language bindings to commonly used
application development languages. We provide
 - the YAZ++ toolkit for applications in C++,
 - PHP/YAZ for application building in PHP,
 - SimpleServer for server applications in Perl, and
 - NET::Z3950 for client applications in Perl.
(If you are looking for a Z39.50 toolkit in Java, we recommend that you check
out Knowledge Integration's open source offering, JZKit.) In addition to these
wrappers, a number of the language bindings of the ZOOM API are based on YAZ.

Libraries and vendors can freely download YAZ and its associated toolkits to build their own Z39.50 applications. Alternatively, they can use the consultancy and support services of Index Data to take advantage of our decade of experience building and supporting Z39.50 toolkits and applications.

YAZ has been considered the leading toolkit for building Z39.50 clients and servers since its first release in 1995. During a decade and a half of active service, the YAZ toolkit has been battle-hardened in every conceivable type of employment, and grown in its support for even the more esoteric aspects of the Z39.50, SUR/SRW, and lately SOLR protocols.

Who Uses YAZ?

More Z39.50 Clients and Servers in use around the world are based on YAZ than any other toolkit.

Statistics from Index Data’s Z39.50 Target Directory page compiled in the Fall of 2004 indicate that at least 35% of all Z39.50 server installations worldwide were built with YAZ. We estimate that the true figure is probably closer to 50%, but an exact percentage is not known. Use statistics gathered in mid 2004 from the Z39.50 gateway to the Library of Congress Catalog indicate that a minimum of 65%, and possibly quite a bit more, of the clients accessing the LC catalog are based on the YAZ toolkit.

\subsection yaz_yazpp YAZ++

[YAZ++](http://www.indexdata.com/yazpp) is an application programming interface (API) to YAZ which supports the development of Z39.50/SRW/SRU client and server applications using C++. Like YAZ, it supports Z39.50-2003 (version 3) as well as SRW/SRU version 1.1 in both the client and server roles. YAZ++ includes an implementation of the ZOOM C++ binding and a generic client/server API based on the Observer/Observable design pattern.

\subsection yaz_php PHP/YAZ

PHP/YAZ is an extension to the popular web server language PHP that implements Z39.50 origin (client) functionality as well as the SRW/SRU protocols.

The following Z39.50 services are supported by this extension: init, search, present, scan and sort. The extension can handle GRS-1, MARC, SUTRS and XML. The module also allows you to convert MARC in ISO2709 to MARCXML on the client side.

The PHP/YAZ extension is part of PHP 4.0.1 and later but has now been moved to PECL. As a PECL module, PHP/YAZ is now independent of PHP versions. It works with both PHP 4 and PHP 5.

\section yaz_zoom ZOOM

[ZOOM](http://zoom.z3950.org) is the emerging standard API for information
retrieval programming using the Z39.50 protocol.
[ZOOM's Abstract API](http://zoom.z3950.org/api/zoom-current.html) specifies
semantics for classes representing key IR concepts such as connections, queries,
result sets and records; and there are various bindings specifying how those
concepts should be represented in various programming languages.

The YAZ++ library includes an implementation of the C++ binding for ZOOM, enabling
quick, easy development of client applications.

For example, here is a tiny Z39.50 client that fetches and displays the MARC
record for Farlow & Brett Surman's The Complete Dinosaur from the Library of
Congress's Z39.50 server:

\code
  #include <iostream>
  #include <yazpp/zoom.h>

  using namespace ZOOM;

  int main(int argc, char **argv)
  {
      connection conn("z3950.loc.gov", 7090);
      conn.option("databaseName", "Voyager");
      conn.option("preferredRecordSyntax", "USMARC");
      resultSet rs(conn, prefixQuery("@attr 1=7 0253333490"));
      const record *rec = rs.getRecord(0);
      cout << rec->render() << endl;
  }
\endcode
