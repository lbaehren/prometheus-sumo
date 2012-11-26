Convert PDF to JPG    {#benchmark_pdf2jpg}
==================

nof. input documents: 1000

\tableofcontents

\section benchmark_pdf2jpg_benchmarks Benchmarks

\subsection benchmark_pdf2jpg_gs Ghostscript

The  gs  (gswin32c,  gswin32, gsos2) command invokes Ghostscript, an interpreter of
Adobe Systems' PostScript(tm) and Portable Document  Format  (PDF)  languages.   gs
reads  "files"  in  sequence and executes them as Ghostscript programs. After doing
this, it reads further input from the standard  input  stream  (normally  the  key-
board),  interpreting each line separately and output to an output device (may be a
file or an X11 window preview, see below). The interpreter exits gracefully when it
encounters  the  `quit` command (either in a file or from the keyboard), at end-of-
file, or at an interrupt signal (such as Control-C at the keyboard).

The interpreter recognizes many option switches, some of which are described below.
Please  see  the  usage documentation for complete information. Switches may appear
anywhere in  the  command  line  and  apply  to  all  files  thereafter.   Invoking
Ghostscript  with the `-h` or `-?` switch produces a message which shows several useful
switches, all the devices known to that executable, and the search path for  fonts;
on Unix it also shows the location of detailed documentation.

Ghostscript  may  be  built  to  use  many  different output devices.  To see which
devices your executable includes, run `gs -h`.

Conversion command:

~~~~
gs -dQUIET -sDEVICE=jpeg -o "$FILE".jpg -dJPEGQ=95 $FILE
~~~~

Timing results:

| Command | real | user | sys |
|---------|------|------|-----|
| `gs -dQUIET -sDEVICE=jpeg -o "$FILE".jpg -dJPEGQ=95 $FILE` | 10m52.783s | 9m23.397s | 0m30.845s |
|    |  11m5.316s |  9m53.458s | 0m33.303s |
|    | 10m52.783s |  9m23.397s | 0m30.845s |
|    | 13m15.446s |  9m58.525s | 0m34.016s |
|    | 11m49.223s |  10m5.400s | 0m34.562s |
|    | 12m34.534s | 10m38.507s | 0m37.025s |
|    | 12m15.616s | 10m29.569s | 0m35.921s |
|    | 12m14.754s | 10m18.043s | 0m35.251s |
|    | 11m48.921s |  10m1.803s | 0m33.981s |
|    | 11m38.352s |  9m50.859s | 0m33.627s |
|    |  12m9.776s |  9m49.003s | 0m33.643s |
|    | 11m59.953s |  10m2.220s | 0m34.121s |
|    | 10m56.013s |  9m33.400s | 0m31.229s |

\subsection benchmark_pdf2jpg_convert ImageMagick convert

Conversion command:

~~~~
convert -density 300 "$FILE" "$FILE".jpg
convert -density 200 "$FILE" "$FILE".jpg
convert -density 150 "$FILE" "$FILE".jpg
~~~~

Timing results:

| Command                                    | real | user | sys |
|--------------------------------------------|------|------|-----|
| `convert -density 300 "$FILE" "$FILE".jpg` | 135m57.055s | 121m51.104s | 6m28.778s |
|    | 135m43.788s | 121m44.964s | 6m33.208s |
|    | 132m12.909s | 119m20.026s | 6m16.269s |
|    | 131m30.327s | 119m11.298s |  6m9.690s |
|    | 131m10.303s | 118m51.776s | 6m10.850s |
|    | 134m54.243s | 119m58.922s | 6m15.211s |
|    | 131m54.356s | 118m48.753s |  6m7.546s |
|    |  131m3.508s | 117m38.235s |  6m0.572s |

\subsection benchmark_pdf2jpg_pdfimages pdfimages

Conversion command:

~~~~
pdfimages -j -p -q $FILE $FILE
~~~~

Timing results:

| Command                          | real       | user      | sys       |
|----------------------------------|------------|-----------|-----------|
| `pdfimages -j -p -q $FILE $FILE` | 2m43.549s  | 1m5.365s  | 0m16.794s |
|                                  | 2m46.323s  | 1m1.286s  | 0m14.972s |
|                                  | 4m23.899s  | 1m2.899s  | 0m16.072s |
|                                  | 3m27.729s  | 1m2.051s  | 0m15.410s |
|                                  | 2m36.761s  | 1m1.216s  | 0m14.732s |
|                                  | 2m34.054s  | 1m1.079s  | 0m14.678s |
|                                  | 2m46.327s  | 1m1.904s  | 0m14.783s |
|                                  | 2m35.455s  | 1m1.165s  | 0m14.683s |
|                                  | 2m50.597s  | 1m2.319s  | 0m14.957s |
|                                  | 3m36.058s  | 1m4.645s  | 0m15.769s |
|                                  | 5m19.994s  | 1m5.385s  | 0m16.083s |

\section benchmark_pdf2jpg_summary Summary

| Command   | real       | user      | sys       |
|-----------|------------|-----------|-----------|
| `convert -density 300 "$FILE" "$FILE".jpg` | 128m10.605s | 116m25.354s | 5m54.815s |
|                                            | 131m26.716s | 117m50.019s | 5m43.686s |
| gs        | 11m5.316s  | 9m53.458s | 0m33.303s |

\section benchmark_pdf2jpg_references References

- [PoDoFo](http://podofo.sourceforge.net/about.html) is a library to work with the PDF file format. The name comes from the first letter of PDF (Portable Document Format). A few tools to work with PDF files are already included in the PoDoFo package. 