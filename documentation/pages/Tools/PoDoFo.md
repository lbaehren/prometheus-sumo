PoDoFo    {#podofo}
======

\tableofcontents

\section podofo_about About

PoDoFo is a library to work with the PDF file format. The name comes from the first letter of PDF (Portable Document Format). A few tools to work with PDF files are already included in the PoDoFo package.

The PoDoFo library is a free, portable C++ library which includes classes to parse PDF files and modify their contents into memory. The changes can be written back to disk easily. The parser can also be used to extract information from a PDF file (for example the parser could be used in a PDF viewer). Besides parsing PoDoFo includes also very simple classes to create your own PDF files. All classes are documented so it is easy to start writing your own application using PoDoFo.

PoDoFo is written in C++ and the code was sucessfully compiled under Unix, Mac OS X and Windows.

\section podofo_tools Tools

The PoDoFo tools are simple tools build around the PoDoFo library. These tools are first of all examples on how to use the PoDoFo library in your own projects. But secondly they offer also features for working with PDF files. More tools will come with future release and the existing tools will gain more features.
Currently there are the following tools:

 * `podofoencrypt` - Encrypts any PDF and allows to set PDF permissions..
 * `podofoimgextract` - Extracts all images from a given PDF file.
 * `podofoimpose` - A powerful PDF imposition tool. It places pages from one or more source PDFs onto pages of a new PDF, applying scaling and positioning.
 * `podofomerge` - Merges two PDF files into onw.
 * `podofopdfinfo` - Provides some basic info about a PDF - metadata, page details, etc.
 * `podofotxt2pdf` - Converts a text file to a PDF
 * `podofotxtextract` - A tool that extracts all text from a PDF file. Works only for simple PDFs at the moment.
 * `podofouncompress` - Removes all compression filters from a PDF file. This is useful for debugging existing PDF files. You might also find PoDoFoBrowser, distributed separately, to be useful if you're using this tool a lot.

\section podofo_references References

- [Sourceforge page](http://podofo.sourceforge.net)