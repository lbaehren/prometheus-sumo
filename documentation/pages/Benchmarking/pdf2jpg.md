Convert PDF to JPG    {#benchmark_pdf2jpg}
==================

nof. input documents: 1000

\tableofcontents

\section benchmark_pdf2jpg_benchmarks Benchmarks

\subsection benchmark_pdf2jpg_gs Ghostscript

Conversion command:

~~~~
gs -dQUIET -sDEVICE=jpeg -o "$FILE".jpg -dJPEGQ=95 $FILE
~~~~

Timing:

~~~~
images  1000
real    11m5.316s
user    9m53.458s
sys     0m33.303s
~~~~

\subsection benchmark_pdf2jpg_convert ImageMagick convert

Conversion command:

~~~~
convert -density 300 "$FILE" "$FILE".jpg
~~~~

\subsection benchmark_pdf2jpg_pdfimages pdfimages

Conversion command:

~~~~
pdfimages -j -p -q $FILE $FILE
~~~~

Timing:

~~~~
images  1344
real	2m43.549s
user	1m5.365s
sys	0m16.794s
~~~~

\section benchmark_pdf2jpg_references References

- [PoDoFo](http://podofo.sourceforge.net/about.html) is a library to work with the PDF file format. The name comes from the first letter of PDF (Portable Document Format). A few tools to work with PDF files are already included in the PoDoFo package. 