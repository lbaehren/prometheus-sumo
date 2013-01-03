Downloads    {#pandora_download}
=========

\tableofcontents

\section pandora_download_overview Overview

Directories and files on the production system (\ref servers_prom1)

\verbatim
/var/local/prometheus
 |-- app
 |   `-- pandora
 |       |-- current
 |       `-- shared
 |           `-- log
 `-- tmp
     `-- pandora
\endverbatim

\section pandora_download_image Downloading an image

\subsection pandora_download_image_log Logfile information

\verbatim
[11587:134.95.80.11] Processing ImageController#download (for 134.95.83.192 at 2013-01-03 07:45:46) [GET]
[11587:134.95.80.11]   Session ID: 5a42a98257930f2ab8c6c36d8e388e0b
[11587:134.95.80.11]   Parameters: {"id"=>"tuberlin-497eb5d50641cc87494e387d43ce3cee84c2b2b7", "format"=>"zip", "action"=>"download", "controller"=>"image"}
[11587:134.95.80.11]   Client info: UA = Mozilla/5.0 (Macintosh; Intel Mac OS X 10_8_2) AppleWebKit/536.26.17 (KHTML, like Gecko) Version/6.0.2 Safari/536.26.17 | LANG = de-de
[11587:134.95.80.11]   Referer: http://prometheus.uni-koeln.de/pandora/image/show/tuberlin-497eb5d50641cc87494e387d43ce3cee84c2b2b7
Rendering image/download
[11587:134.95.80.11]   Meta: User = 47 | Institution = 45
[11587:134.95.80.11] Completed in 0.50302 (1 reqs/sec) | Rendering: 0.08338 (16%) | DB: 0.00000 (0%) | Mem: 347.71 RSS / 513.93 VSZ (2.1%) | 200 OK [http://prometheus.uni-koeln.de/pandora/image/download/tuberlin-497eb5d50641cc87494e387d43ce3cee84c2b2b7.zip]
B4R: [GET /image/download/tuberlin-497eb5d50641cc87494e387d43ce3cee84c2b2b7.zip] action: 0.5465 | filters: 0.0144 | request: 0.9225
\endverbatim

\section pandora_download_collection Downloading a collection

\subsection pandora_download_collection_log Logfile information

Downloading a collection from the image archive will produce an entry in the
\ref pandora `production.log` file:

\verbatim
[11611:134.95.80.11] Processing CollectionController#download (for 134.95.11.139 at 2013-01-03 10:39:02) [GET]
[11611:134.95.80.11]   Session ID: dc7d56bb823b7076c55baa325dd9004c
[11611:134.95.80.11]   Parameters: {"format"=>"zip", "id"=>"32807", "controller"=>"collection", "action"=>"download"}
[11611:134.95.80.11]   Client info: UA = Mozilla/5.0 (Macintosh; Intel Mac OS X 10.6; rv:17.0) Gecko/20100101 Firefox/17.0 | LANG = en-US,en;q=0.5
[11611:134.95.80.11]   Referer: http://prometheus.uni-koeln.de/pandora/collection/edit/32807
Rendering collection/download
[11611:134.95.80.11]   Meta: User = 38318 | Institution = 10
[11611:134.95.80.11] Completed in 9.42667 (0 reqs/sec) | Rendering: 9.40745 (99%) | DB: 0.00000 (0%) | Mem: 290.29 RSS / 458.02 VSZ (1.8%) | 200 OK [http://prometheus.uni-koeln.de/pandora/collection/download/32807.zip]
B4R: [GET /de/pandora.js] action: 0.1349 | filters: 0.0976 | rendering: 0.0949 | request: 0.1704
\endverbatim