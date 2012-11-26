Convert PDF to JPG    {#benchmark_pdf2jpg}
==================

\tableofcontents

\section benchmark_pdf2jpg_benchmarks Benchmarks

Size of the test set: 1000 PDF documents

Many of the PDF documents contain multiple layers, which at conversion using
_pdfimage_ are stored in separate files:

~~~~
page   num  type   width height color comp bpc  enc interp  object ID
---------------------------------------------------------------------
   1     0 image    2536  1848  gray    1   8  jpeg   no        10  0
   1     1 image    1902  1386  gray    1   8  jpeg   no        11  0
   1     2 mask     7608  5544  -       1   1  jpeg   no        11  0
~~~~

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
| `gs -dQUIET -sDEVICE=jpeg -o "$FILE".jpg -dJPEGQ=80` | 10m19.721s | 9m10.380s | 0m28.706s |
|    | 10m13.771s | 9m31.442s | 0m30.525s |
|    | 10m18.111s | 9m34.676s | 0m30.880s |
|    |  10m6.984s | 9m15.131s | 0m28.760s |
|    |  9m53.144s |  9m8.766s | 0m28.565s |
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
| `gs -dQUIET -sDEVICE=jpeg -o "$FILE".jpg -dJPEGQ=100 $FILE` | 11m11.836s | 9m31.706s | 0m28.879s |
|    |  11m5.063s |  9m53.046s | 0m31.230s |
|    | 12m57.330s | 10m36.744s | 0m34.647s |
|    | 11m14.513s |  9m43.029s | 0m30.922s |
|    | 12m36.705s |  10m4.481s | 0m33.370s |

Test runs on `prom-desktop`:

| Command | real | user | sys |
|---------|------|------|-----|
| `gs -dQUIET -sDEVICE=jpeg -o "$FILE".jpg -dJPEGQ=100 $FILE` | 10m29.533s | 10m11.702s | 0m18.533s |
|    | 10m27.588s | 10m10.470s | 0m18.113s |
|    | 10m27.976s | 10m11.306s | 0m17.633s |
|    | 10m27.323s | 10m10.622s | 0m17.637s |
|    | 10m27.662s | 10m10.090s | 0m18.537s |
|    | 10m27.190s |  10m9.894s | 0m18.241s |
|    | 10m27.344s |  10m9.890s | 0m18.545s |
|    | 10m27.486s | 10m10.318s | 0m18.165s |
|    | 10m27.424s | 10m10.526s | 0m17.861s |
|    | 10m28.876s | 10m10.422s | 0m19.033s |
| `gs -dQUIET -sDEVICE=jpeg -o "$FILE".jpg $FILE` | 10m0.389s | 9m43.336s | 0m18.025s |

Timing results on \ref servers_srv1 :

| Command | real | user | sys |
|---------|------|------|-----|
| `gs -dQUIET -sDEVICE=jpeg -o "$FILE".jpg -dJPEGQ=95 $FILE` | 11m7.667s | 10m29.075s | 0m23.221s |
|    | 10m33.518s | 10m10.378s | 0m22.629s |
|    | 10m46.286s | 10m21.995s | 0m22.729s |
|    | 10m33.206s | 10m11.138s | 0m21.793s |
|    | 10m35.929s | 10m14.154s | 0m21.573s |

\subsection benchmark_pdf2jpg_convert ImageMagick convert

Conversion command:

~~~~
convert -density 300 "$FILE" "$FILE".jpg
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

\subsection benchmark_podofo PoDoFo

\ref podofo is a library to work with the PDF file format and includes also a few
tools. The name comes from the first two letters of PDF (Portable Document
Format).

| Command                    | real       | user     | sys       |
|----------------------------|------------|----------|-----------|
| `podofoimgextract $FILE .` | 1m24.301s | 0m16.829s | 0m16.159s |

\section benchmark_pdf2jpg_summary Summary

Though they clearly are the fastest tools in the field, both `podofoimgextract`
and `pdfimages` have to be discarded, as both will store layer of an images
separately, which would require subsequent recombination of these parts.
