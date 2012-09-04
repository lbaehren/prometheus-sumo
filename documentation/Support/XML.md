
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

\test TestXML.cc TestXMLTree.c

\section xml_programming Programming interfaces

The design goals of XML include, "It shall be easy to write programs which process XML documents." Despite this, the XML specification contains almost no information about how programmers might go about doing such processing. The XML Infoset specification provides a vocabulary to refer to the constructs within an XML document, but also does not provide any guidance on how to access this information. A variety of APIs for accessing XML have been developed and used, and some have been standardized.

Existing APIs for XML processing tend to fall into these categories:

- Stream-oriented APIs accessible from a programming language, for example SAX and StAX.
- Tree-traversal APIs accessible from a programming language, for example DOM.
- XML data binding, which provides an automated translation between an XML document and programming-language objects.
- Declarative transformation languages such as XSLT and XQuery.

Stream-oriented facilities require less memory and, for certain tasks which are based on a linear traversal of an XML document, are faster and simpler than other alternatives. Tree-traversal and data-binding APIs typically require the use of much more memory, but are often found more convenient for use by programmers; some include declarative retrieval of document components via the use of XPath expressions.

XSLT is designed for declarative description of XML document transformations, and has been widely implemented both in server-side packages and Web browsers. XQuery overlaps XSLT in its functionality, but is designed more for searching of large XML databases.

\subsection xml_programming_libxml libxml

Libxml2 is the XML C parser and toolkit developed for the Gnome project (but usable outside of the Gnome platform), it is free software available under the MIT License. XML itself is a metalanguage to design markup languages, i.e. text language where semantic and structure are added to the content using extra "markup" information enclosed between angle brackets. HTML is the most well-known markup language. Though the library is written in C a variety of language bindings make it available in other environments.

\subsection xml_programming_libxmlpp libxml++

Like the underlying libxml library, libxml++ allows the use of 3 parsers, depending on your needs - the DOM, SAX, and TextReader parsers. The relative advantages and behaviour of these parsers will be explained here.

All of the parsers may parse XML documents directly from disk, a string, or a C++ std::istream. Although the libxml++ API uses only Glib::ustring, and therefore the UTF-8 encoding, libxml++ can parse documents in any encoding, converting to UTF-8 automatically. This conversion will not lose any information because UTF-8 can represent any locale.

Remember that white space is usually significant in XML documents, so the parsers might provide unexpected text nodes that contain only spaces and new lines. The parser does not know whether you care about these text nodes, but your application may choose to ignore them.

\section xml_references References

  - [Extensible Markup Language](http://www.w3.org/TR/xml) (XML) -- W3C Recommendation
  - [XML Path Language](http://www.w3.org/TR/xpath) -- W3C Recommendation
  - [XPath Tutorial](http://www.w3schools.com/xpath/default.asp)
  - [Free C or C++ XML Parser Libraries](http://lars.ruoff.free.fr/xmlcpp)
  - [libxml++ Tutorial](http://developer.gnome.org/libxml++-tutorial/stable) - An XML Parser for C++
  - [Parsin XML with Boost](http://akrzemi1.wordpress.com/2011/07/13/parsing-xml-with-boost)