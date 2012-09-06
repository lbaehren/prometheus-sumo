
XML    {#xml}
===

\tableofcontents

\tableofcontents

\section xml_overview Overview

*Extensible Markup Language* (XML) is a markup language that defines a set of rules for encoding documents in a format that is both human-readable and machine-readable. It is defined in the XML 1.0 Specification produced by the W3C, and several other related specifications, all gratis open standards.

The design goals of XML emphasize simplicity, generality, and usability over the Internet. It is a textual data format with strong support via Unicode for the languages of the world. Although the design of XML focuses on documents, it is widely used for the representation of arbitrary data structures, for example in web services.

Many application programming interfaces (APIs) have been developed for software developers to use to process XML data, and several schema systems exist to aid in the definition of XML-based languages.

ML documents consist entirely of characters from the Unicode repertoire. Except for a small number of specifically excluded control characters, any character defined by Unicode may appear within the content of an XML document.

XML includes facilities for identifying the encoding of the Unicode characters that make up the document, and for expressing characters that, for one reason or another, cannot be used directly.

\test TestXML.cc TestXMLTree.c TestSourcesKassel.cc TestSourcesRobertinum.cc

\section xml_programming Programming interfaces

The design goals of XML include, "It shall be easy to write programs which process XML documents." Despite this, the XML specification contains almost no information about how programmers might go about doing such processing. The XML Infoset specification provides a vocabulary to refer to the constructs within an XML document, but also does not provide any guidance on how to access this information. A variety of APIs for accessing XML have been developed and used, and some have been standardized.

Existing APIs for XML processing tend to fall into these categories:

- Stream-oriented APIs accessible from a programming language, for example SAX and StAX.
- Tree-traversal APIs accessible from a programming language, for example DOM.
- XML data binding, which provides an automated translation between an XML document and programming-language objects.
- Declarative transformation languages such as XSLT and XQuery.

Stream-oriented facilities require less memory and, for certain tasks which are based on a linear traversal of an XML document, are faster and simpler than other alternatives. Tree-traversal and data-binding APIs typically require the use of much more memory, but are often found more convenient for use by programmers; some include declarative retrieval of document components via the use of XPath expressions.

XSLT is designed for declarative description of XML document transformations, and has been widely implemented both in server-side packages and Web browsers. XQuery overlaps XSLT in its functionality, but is designed more for searching of large XML databases.

\subsection xml_programming_nokogiri Nokogiri (Ruby)

Nokogiri is an HTML, XML, SAX, and Reader parser. Among Nokogiri’s many features is the ability to search documents via XPath or CSS3 selectors.

\subsection xml_programming_libxml libxml (C)

Libxml2 is the XML C parser and toolkit developed for the Gnome project (but usable outside of the Gnome platform), it is free software available under the MIT License. XML itself is a metalanguage to design markup languages, i.e. text language where semantic and structure are added to the content using extra "markup" information enclosed between angle brackets. HTML is the most well-known markup language. Though the library is written in C a variety of language bindings make it available in other environments.

\subsection xml_programming_libxmlpp libxml++ (C++)

Like the underlying libxml library, libxml++ allows the use of 3 parsers, depending on your needs - the DOM, SAX, and TextReader parsers. The relative advantages and behaviour of these parsers will be explained here.

All of the parsers may parse XML documents directly from disk, a string, or a C++ std::istream. Although the libxml++ API uses only Glib::ustring, and therefore the UTF-8 encoding, libxml++ can parse documents in any encoding, converting to UTF-8 automatically. This conversion will not lose any information because UTF-8 can represent any locale.

Remember that white space is usually significant in XML documents, so the parsers might provide unexpected text nodes that contain only spaces and new lines. The parser does not know whether you care about these text nodes, but your application may choose to ignore them.

\subsection xml_programming_boost Boost.PropertyTree (C++)

Unfortunately, there is no XML parser in [Boost](http://www.boost.org) as of the time of this writing. The library therefore contains the fast and tiny [RapidXML](http://rapidxml.sourceforge.net) parser (currently in version 1.13) to provide XML parsing support. RapidXML does not fully support the XML standard; it is not capable of parsing DTDs and therefore cannot do full entity substitution.

By default, the parser will preserve most whitespace, but remove element content that consists only of whitespace. Encoded whitespaces (e.g. &#32;) does not count as whitespace in this regard. You can pass the trim_whitespace flag if you want all leading and trailing whitespace trimmed and all continuous whitespace collapsed into a single space.

Please note that RapidXML does not understand the encoding specification. If you pass it a character buffer, it assumes the data is already correctly encoded; if you pass it a filename, it will read the file using the character conversion of the locale you give it (or the global locale if you give it none). This means that, in order to parse a UTF-8-encoded XML file into a wptree, you have to supply an alternate locale, either directly or by replacing the global one.

XML / property tree conversion schema (`read_xml` and `write_xml`):

  - Each XML element corresponds to a property tree node. The child elements correspond to the children of the node.
  - The attributes of an XML element are stored in the subkey `<xmlattr>`. There is one child node per attribute in the attribute node. Existence of the `<xmlattr>` node is not guaranteed or necessary when there are no attributes.
  - XML comments are stored in nodes named `<xmlcomment>`, unless comment ignoring is enabled via the flags.
  - Text content is stored in one of two ways, depending on the flags. The default way concatenates all text nodes and stores them in a single node called `<xmltext>`. This way, the entire content can be conveniently read, but the relative ordering of text and child elements is lost. The other way stores each text content as a separate node, all called `<xmltext>`.

The XML storage encoding does not round-trip perfectly. A read-write cycle loses trimmed whitespace, low-level formatting information, and the distinction between normal data and CDATA nodes. Comments are only preserved when enabled. A write-read cycle loses trimmed whitespace; that is, if the origin tree has string data that starts or ends with whitespace, that whitespace is lost. 

\section xml_references References

  - [Extensible Markup Language](http://www.w3.org/TR/xml) (XML) -- W3C Recommendation
  - [XML Path Language](http://www.w3.org/TR/xpath) -- W3C Recommendation
  - [XPath Tutorial](http://www.w3schools.com/xpath/default.asp)
  - [Free C or C++ XML Parser Libraries](http://lars.ruoff.free.fr/xmlcpp)
  - [libxml++ Tutorial](http://developer.gnome.org/libxml++-tutorial/stable) - An XML Parser for C++
  - [Parsing XML with Boost](http://akrzemi1.wordpress.com/2011/07/13/parsing-xml-with-boost)
  - [Boost.PropertyTree](http://www.boost.org/doc/libs/1_50_0/doc/html/property_tree.html)
  - [Nokogiri](http://nokogiri.org) -- a HTML, XML, SAX, & Reader parser with the ability to search documents via XPath or CSS3 selectors
