Procedures    {#pandora_procedures}
==========

\tableofcontents

\section pandora_procedures_startup Startup procedure

\li Check status of the Mongrel cluster
\code
pandora_cluster ps
\endcode
If the cluster is not up and running, use:
\code
pandora_cluster start
\endcode

\li Check NFS imports
\code
nfsimports
\endcode

\li Change the maintenance message from
\code
---
layout: default
changefreq: daily
priority: 1.0
---
#include virtual="<%=r "inc/nopandora.html.#{page.lang}" %>"
\endcode
back to
\code
---
layout: default
changefreq: daily
priority: 1.0
---
<!--NOPANDORA#include virtual="<%=r "inc/nopandora.html.#{page.lang}" %>" -->
\endcode


\section pandora_procedures_shutdown Shutdown procedure

  \li At prom1: Disable the usage of the application
  \code
  production deploy web:disable
  \endcode

  \li Enable SSI for message in `index.de.html`: Change from
  \code
---
layout: default
changefreq: daily
priority: 1.0
---
<!--NOPANDORA#include virtual="<%=r "inc/nopandora.html.#{page.lang}" %>" -->
\endcode
to
\code
---
layout: default
changefreq: daily
priority: 1.0
---
#include virtual="<%=r "inc/nopandora.html.#{page.lang}" %>"
\endcode

  \li Deactivate cronjobs, not to be active during shutdown period (or before the system
  is back up completely)

  \li Stop the application
  \code
  production deploy:stop
  \endcode

  \li Shut down the individual server machines:
  \code
  shutdown -h now
  \endcode