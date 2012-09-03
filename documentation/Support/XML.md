
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

\test TestXML.cc

\section xml_references References

  - [XML Path Language](http://www.w3.org/TR/xpath) (W3C Recommendation)
  - [XPath Tutorial](http://www.w3schools.com/xpath/default.asp)
  - [Free C or C++ XML Parser Libraries](http://lars.ruoff.free.fr/xmlcpp)
