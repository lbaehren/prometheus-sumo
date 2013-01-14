ZOOM    {#zoom}
====

\tableofcontents

\test testYAZPP.cc

\section zoom_about About

[ZOOM](http://zoom.z3950.org) is the emerging standard API for information
retrieval programming using the [Z39.50 protocol](http://en.wikipedia.org/wiki/Z39.50).
[ZOOM's Abstract API](http://zoom.z3950.org/api/zoom-current.html) specifies
semantics for classes representing key IR concepts such as connections, queries,
result sets and records; and there are various bindings specifying how those
concepts should be represented in various programming languages.

\section zoom_cpp C++ bindings for ZOOM

The \ref yaz_yazpp library includes an implementation of the C++ binding for ZOOM, enabling
quick, easy development of client applications.

For example, here is a tiny Z39.50 client that fetches and displays the MARC
record for Farlow & Brett Surman's _The Complete Dinosaur_ from the Library of
Congress's Z39.50 server:

\code
#include <iostream>
#include <yazpp/zoom.h>

using namespace ZOOM;

int main(int argc, char **argv)
{
    /* Configuration of server connection */
    connection conn("z3950.loc.gov", 7090);
    conn.option("databaseName", "Voyager");
    conn.option("preferredRecordSyntax", "USMARC");

    /* Retrieve data from server ... */
    resultSet rs(conn, prefixQuery("@attr 1=7 0253333490"));

    /* ... and display them */
    record rec (rs, 0);
    cout << rec->render() << endl;
}
\endcode

\section zoom_classes ZOOM Classes

The Z39.50 services are provided as methods on classes, where the classes represent the key Z39.50 concepts:

\li A Connection - or an ``application association'', as the OSI terminology in the standard has it - represents an ongoing dialogue between the client (``origin'' in the standard) and server (``target''). A connection is forged by the act of creating a Connection object; and initialisation is performed implicitly, so that the new object is ready to be used immediately.

\li The Connection class supports methods for instantiation and searching, together with the housekeeping and option management methods provided on all classes - all detailed below.

\li A Query represents a set of search criteria which will be submitted to a server via a connection. There are various subclasses of the Query class, representing different query syntaxes.

\li A Result Set represents a set of records, held on a server, which have been identified by searching (that is, submitting a Query to a Connection).

\li The Result Set class supports methods for discovering the number of its records, and fetching records either one by one or all at once.

\li A Record represents a record from a result set, which has been retrieved from a server.

\li The Record class supports methods for discovering the number of its fields, fetching fields either one by one or all at once, rendering the whole record in a ``human-readable'' format and returning the raw data.

\li A Scan Set represents a set of potential query terms which a server suggests may be useful. In some cases, the terms may be accompanied by hit counts and other information.

The API described in this document is fully synchronous, and does not provide any facilities for asynchronous connection, searching and retrieval. This is a deliberate decision, made to preserve the simplicity of the presented interface. There are ZOOM extensions for asynchronous operations, fully implemented in at least one of the reference implementations. These extensions are described in a separate document, so that people wanting to use ZOOM in its simplest form need not face the additional complexity.

\subsection zoom_classes_options Standard options

  \li [Standard Options](http://zoom.z3950.org/api/zoom-current.html#3.8)
  | Option | Level | Description | Default |
  |--------|-------|-------------|---------|
  | \c implementationId | Connection | The identifier of your client, to be sent to the server at connection time. By convention, this string often includes the implementation creator's Z39.50 implementor ID. | \a none |
  | \c implementationName | Connection | The name of your client, to be sent to the server at connection time. This is an arbitrary string. | \a none |
  | \c implementationVersion | Connection | The version of your client, to be sent to the server at connection time. | \a none |
  | \c user | Connection | User name to be used in authentication. See below for details. | \a none |
  | \c group | Connection | Group name to be used in authentication. See below for details. | \a none |
  | \c password | Connection | Password to be used in authentication. See below for details. | \a none |
  | \c databaseName | Connection | One or more database names separated by the plus character (+), to be used by subsequent search requests on this Connection. | \a Default |
  | \c elementSetName | Result Set | Element-set name of records. Most servers should honor the element-set names B and F for brief and full records respectively. | \a none |
  | \c preferredRecordSyntax | Result Set | The record syntax in which the returned records are requested. See below for valid values of this option. | \a none |
  | \c recordDatabase | Record | The database from which the record was returned. This is useful when searching across multiple databases using a complex value of the same-named option on the Connection. | \a none |

\li Values for [preferredRecordSyntax](http://zoom.z3950.org/api/zoom-current.html#3.9)
| Value   | Description |
|---------|-------------|
| USMARC  | USMARC records (OID 1.2.840.10003.5.10) |
| SUTRS   | SUTRS records (OID 1.2.840.10003.5.101) |
| XML     | XMLK records, corresponding to the MIME-type text/xml (OID 1.2.840.10003.5.109.10) |
| SGML    | SGML records (OID 1.2.840.10003.5.109.9) |
| GRS-1   | GRS-1 records (OID 1.2.840.10003.5.105) |
| OPAC    | OPAC records (OID 1.2.840.10003.5.102) |
| EXPLAIN | Explain records (OID 1.2.840.10003.5.100) |

\section zoom_references References

\li [ZOOM++](http://www.indexdata.com/yazpp/doc/zoom.html)
\li [Yaz-marcdump: Simple but powerful MARC batch-tool](http://www.j-gorman.com/blog/2012/4/22/yaz-marcdump-simple-but-powerful-marc-batch-tool.html)