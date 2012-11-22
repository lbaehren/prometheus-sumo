YAZ    {#yaz}
===

\tableofcontents

\test testYAZPP.cc

\section yaz_toolkit YAZ programmers’ toolkit

[YAZ](http://www.indexdata.com/yaz) is a programmers’ toolkit supporting the
development of Z39.50/SRW/SRU clients and servers. Z39.50-2003 (version 3) as
well as SRW/SRU version 1.1 are supported in both the client and server roles.
The SOLR webservice is supported in the client role through the \ref zoom API.

The current version of YAZ includes support for the industry standard \ref zoom API
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
wrappers, a number of the language bindings of the \ref zoom API are based on YAZ.

Libraries and vendors can freely download YAZ and its associated toolkits to
build their own Z39.50 applications. Alternatively, they can use the consultancy
and support services of Index Data to take advantage of our decade of experience
building and supporting Z39.50 toolkits and applications.

YAZ has been considered the leading toolkit for building Z39.50 clients and
servers since its first release in 1995. During a decade and a half of active
service, the YAZ toolkit has been battle-hardened in every conceivable type of
employment, and grown in its support for even the more esoteric aspects of the
Z39.50, SUR/SRW, and lately SOLR protocols.

Who Uses YAZ?

More Z39.50 Clients and Servers in use around the world are based on YAZ than
any other toolkit.

Statistics from Index Data’s Z39.50 Target Directory page compiled in the Fall
of 2004 indicate that at least 35% of all Z39.50 server installations worldwide
were built with YAZ. We estimate that the true figure is probably closer to 50%,
but an exact percentage is not known. Use statistics gathered in mid 2004 from
the Z39.50 gateway to the Library of Congress Catalog indicate that a minimum of
65%, and possibly quite a bit more, of the clients accessing the LC catalog are
based on the YAZ toolkit.

\subsection yaz_yazpp YAZ++

[YAZ++](http://www.indexdata.com/yazpp) is an application programming interface (API) to YAZ which supports the development of Z39.50/SRW/SRU client and server applications using C++. Like YAZ, it supports Z39.50-2003 (version 3) as well as SRW/SRU version 1.1 in both the client and server roles. YAZ++ includes an implementation of the \ref zoom C++ binding and a generic client/server API based on the Observer/Observable design pattern.

\subsection yaz_php PHP/YAZ

PHP/YAZ is an extension to the popular web server language PHP that implements Z39.50 origin (client) functionality as well as the SRW/SRU protocols.

The following Z39.50 services are supported by this extension: init, search, present, scan and sort. The extension can handle GRS-1, MARC, SUTRS and XML. The module also allows you to convert \ref marc in ISO2709 to MARCXML on the client side.

The PHP/YAZ extension is part of PHP 4.0.1 and later but has now been moved to PECL. As a PECL module, PHP/YAZ is now independent of PHP versions. It works with both PHP 4 and PHP 5.

\subsection yaz_usemarcon USEMARCON

[USEMARCON](http://www.nationallibrary.fi/libraries/format/usemarcon.html) is a rule-based \ref marc record manipulation program and library. It is free, open source, written in C++. USEMARCON can be used interactively with USEMARCON GUI, in batch processing using the command line version and it's also possible to integrate the library with other software (this has been done e.g. with YAZ Proxy»).

USEMARCON is a software application that allows users to convert bibliographic records from one MAchine-Readable Cataloguing (MARC) format to another. Approximately fifty variant MARC formats are currently in use throughout the world. The differences between the MARC formats present a barrier to the easy exchange of records. This is a fundamental problem for libraries, and necessitates the costly re-cataloguing of material for which records are already available, but in a MARC format other than their own.

In 1995, a project funded by the European Union was set up to address this issue. The project was successfully completed in 1997 with the development of the USEMARCON (User Controlled Generic MARC Converter) software.

USEMARCON facilitates the conversion of catalogue records from one MARC format to another e.g. from UKMARC to UNIMARC. The software was designed as a toolbox-style application, allowing users with detailed knowledge of the source and target MARC formats to develop rules governing the behaviour of the conversion. Rules files may be supplemented by additional tables for more accurate conversion of MARC-specific character sets or coded information. The tables and rules files are simple ASCII text files and can be created using any standard text editor such as MS Windows Notepad.

\section yaz_pqf Prefix Query Format

Since RPN or reverse polish notation is really just a fancy way of describing a suffix notation format (operator follows operands), it would seem that the confusion is total when we now introduce a prefix notation for RPN. The reason is one of simple laziness - it's somewhat simpler to interpret a prefix format, and this utility was designed for maximum simplicity, to provide a baseline representation for use in simple test applications and scripting environments (like Tcl). The demonstration client included with YAZ uses the PQF.

The PQF is defined by the pquery module in the YAZ library. There are two sets of function that have similar behavior. First set operates on a PQF parser handle, second set doesn't. First set set of functions are more flexible than the second set. Second set is obsolete and is only provided to ensure backwards compatibility. 

\section yaz_toolkit_intro YAZ toolkit

One of the things Index Data is known for is the YAZ toolkit - an open source
programmers’ toolkit supporting the development of Z39.50/SRW/SRU clients and
servers. The first release was in 1995 and I've been using it for my own
metasearch engine ZACK Gateway since 1998, long before I joined Index Data.

Z39.50 is a client-server protocol for searching and retrieving information from
remote computer databases. It is a mature low level protocol like HTTP and FTP.
You don't implement Z39.50 yourself, you use the YAZ utilities and the libraries
and frameworks for in other languages (C++, PHP, Perl, etc.).

There are many people who thinks that Z39.50 is a dead standard, and hard to
understand. That is not true. Z39.50 is still growing in use, stable and very
fast. It is the only widely available protocol for metasearch.

Using Z39.50 is not harder than using FTP. I think that the overhead for learning Z39.50 is less than a half day for an experienced programmer. Every problem which you have later is not related to the Z39.50 protocol itself, it is related to underlying system behind the Z39.50 server. Keep in mind that Z39.50 is an API to access (bibliographic) databases. It does not define how the data is structured and indexed in the database.

\subsection yaz_toolkit_search Simple search

Let's start with a simple question: does the Library of Congress have the book "library mashups"? (I strongly recommend you buy this book - I wrote chapter 19):

\verbatim
$ zoomsh "connect z3950.loc.gov:7090/voyager" 'search "library mashups"' quit

z3950.loc.gov:7090/voyager: 2 hits
\endverbatim

That's all! Only one line on the command line. A SRU or SOAP request would not
be shorter.

The default exchange format for bibliographic records in Z39.50 is MARC21. This
is maybe not what you want to parse yourself.

Ok, now let's download the record in \ref xml format:

\code
$ zoomsh "connect z3950.loc.gov:7090/voyager" 'search "library mashups"' "show 0 1 xml" "quit"
\endcode

The resulting output will look something like this:

\verbatim
z3950.loc.gov:7090/voyager: 2 hits
0 database=VOYAGER syntax=USmarc schema=unknown
<record xmlns="http://www.loc.gov/MARC21/slim">
 <leader>02438cam a22003018a 4500</leader>
 <controlfield tag="001">15804854</controlfield>
 <controlfield tag="005">20090710141909.0</controlfield>
 <controlfield tag="008">090706s2009 nju b 001 0 eng </controlfield>
 <datafield tag="906" ind1=" " ind2=" ">
 <subfield code="a">7</subfield>
 <subfield code="b">cbc</subfield>
 <subfield code="c">orignew</subfield>
 <subfield code="d">1</subfield>
 <subfield code="e">ecip</subfield>
 <subfield code="f">20</subfield>
 <subfield code="g">y-gencatlg</subfield>
 </datafield>

[large XML output...]
</record>
\endverbatim

You can parse the \ref xml output with your favorite tools, usually an XSLT style sheet.

\subsection yaz_toolkit_metasearch Simple metasearch

It as well is possible to run a simple metasearch on the command line. You want
to know which library has the book with the ISBN 0-13-949876-1 (UNIX network
programming / W. Richard Stevens)? You can run the zoomsh in a shell loop.

Put the list of databases (zURL's) line by line in the text file zurl.txt:

\verbatim
z3950.loc.gov:7090/voyager
melvyl.cdlib.org:210/CDL90
library.ox.ac.uk:210/ADVANCE
z3950.library.wisc.edu:210/madison
\endverbatim

and run a little loop in a shell script:

\code
$ for zurl in `cat zurl.txt`
do
 zoomsh "connect $zurl" \
 "search @attr 1=7 0-13-949876-1" "quit"
done
\endcode

The resulting output will look something like this:

\verbatim
z3950.loc.gov:7090/voyager: 0 hits
melvyl.cdlib.org:210/CDL90: 1 hits
library.ox.ac.uk:210/ADVANCE: 1 hits
z3950.library.wisc.edu:210/madison: 0 hits
\endverbatim

Of course it takes time to run one search request after another. How about a parallel search? Modern xargs(1) commands on BSD based Operating Systems (MacOS, FreeBSD) and the GNU xargs supports to run several processes at a time.

\section yaz_references References

 - [YAZ toolkit](http://www.indexdata.com/yaz)
 - [User's Guide and Reference](http://www.indexdata.com/yaz/doc)
 - [YAZ++ User's Guide and Reference](http://www.indexdata.com/yazpp/doc/index.html)
 - [The Z39.50 Object-Orientation Model](http://zoom.z3950.org/api/zoom-current.html)
 - [Bib-1 Diagnostics Defined within the Z39.50-1995 Standard](http://www.loc.gov/z3950/agency/defns/bib1diag.html)
 - [Standards at the Library of Congress](http://www.loc.gov/standards)
 - [Pictura Paedagogica Online - The Concept and its Realisation](http://bbf.dipf.de/virtuellesbildarchiv/projektbeschreibung_e.html)
 - [Retrieve bibliographic data via Z39.50 with PHPYAZ](http://blog.peschla.net/2011/12/bibliographic-data-via-z3950-and-phpyaz)

