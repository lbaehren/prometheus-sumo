
Homepage    {#homepage}
========

\tableofcontents

\section homepage_overview Overview

In order to keep the amount of processing needed behind the scenes in order to
deliver the contents of the website to a minimum, all the pages are served as
\a static pages. The sources from which these pages are being generated are
hosted inside a Git repository, from which they can be obtained for editing
and rendering the resulting pages.

Editing the source files and building the homepage can be done at least in two
ways, depending on the user's proviciency with SCM tools (such as \ref git);
aside the more developers-type approach -- i.e. checking out the sources, editing
them and thereafter committing back the changes -- there also exists a web-based
tool to aid iterating through a number of changes, allowing to preview them
before publishing the modifications made.

\li \subpage promhp_codebase
\li \subpage promhp_editing
\li \subpage promhp_build
\li \subpage JekyllCommander

\section homepage_repositories Repositories

\subsection homepage_repositories_srv3 ... on prometheus-srv3

The repository from which both the \c staging and \c live version of the
homepage are being build is hosted on \ref servers_srv3 -- it
is there where also the \ref JekyllCommander, which allows editing of the pages
from within a web browser.

\verbatim
/var/local/prometheus
 ├── bin
 │   ├── promhp.post-commit        ... Script run post commit
 │   └── promhp.post-receive       ... Script run post receive
 └── srv
     └── promhp
         ├── live                  ...  Live version of the website
         ├── promhp.git            ...  Git repository
         │   └── hooks
         │       └── post-receive  ...  Hook script for the "post-receive" event
         └── staging               ...  Staging version of website
\endverbatim

In order to check out a working copy:

    git clone <login>@prom-srv3:/var/local/prometheus/srv/promhp/promhp.git

\subsection homepage_repositories_github ... on Github

A second repository for the sources of the homepage is
[hosted on Github](https://github.com/prometheus-ev/promhp); depending on the
access permission a working copy can be obtained through one of the following
methods:

\li Read/Write access
\verbatim
git clone git@github.com:prometheus-ev/promhp.git promhp
\endverbatim
\li Read-only access
\verbatim
git clone git://github.com/prometheus-ev/promhp.git promhp
\endverbatim

\subsection homepage_update Updating procedure

\li Commit the changes to the repository; this can either be done directly or through the \subpage JekyllCommander.

\li The "post-receive" script `promhp.git/hooks/post-receive` is run after receive-pack has accepted a pack and the repository has been updated.
\code
PROM_ROOT=/var/local/prometheus

##
## [1] Create a temporary file or directory, safely, and print its name.
##
tmp="`mktemp`"
cat - > "$tmp"

##
## [2] Send emails listing new revisions to the repository introduced by the change being reported
##
. $PROM_ROOT/bin/git-post-receive-email < "$tmp"

##
## [3] Push updated version of web pages to directory from where the website is hosted
##
. $PROM_ROOT/bin/promhp.post-receive < "$tmp"

##
## [4] Clean up: remove the temporary directory
##
rm -f "$tmp"

##
## [5] Adjust access permissions on the directories
##
chmod -Rf g+w $PROM_ROOT/srv/promhp/{promhp.git,staging,live}
\endcode

