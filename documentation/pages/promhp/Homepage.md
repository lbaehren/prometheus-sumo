
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
ways, depending on the user's proviciency with SCM tools (such as \ref Git);
aside the more developers-type approach -- i.e. checking out the sources, editing
them and thereafter committing back the changes -- there also exists a web-based
tool to aid iterating through a number of changes, allowing to preview them
before publishing the modifications made.

\li \subpage homepage_editing
\li \subpage homepage_build
\li \subpage JekyllCommander

\section homepage_repositories Repositories

\subsection homepage_repositories_srv3 ... on prometheus-srv3

The repository from which both the \c staging and \c live version of the
homepage are being build is hosted on \c prometheus-srv3.uni-koeln.de -- it
is there where also the \ref JekyllCommander, which allows editing of the pages
from within a web browser.

\verbatim
/var/local/prometheus                        ...  Root of prometheus installation
           |-- bin
           |   |-- promhp.post-commit        ... Script run post commit
           |   `-- promhp.post-receive       ... Script run post receive
           `-- srv
               `-- promhp
                   |-- live                  ...  Live version of the website
                   |-- promhp.git            ...  Git repository
                   |   `-- hooks
                   |       `-- post-receive  ...  Hook script for the "post-receive" event
                   |-- promhp.git.old
                   `-- staging               ...  Staging version of website
\endverbatim

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

\section homepage_code Organization of the source code

After checkout out a working copy from the repository hosted on Github,
the following directory structure can be found on disk:

\verbatim
.
|-- _config
|-- _includes
|   `-- series
|-- _layouts
|-- _lib
|-- _plugins
|-- _posts
|-- about
|   |-- association
|   |-- jobs
|   `-- tagung2011
|-- blog
|-- databases
|-- faq
|-- files
|   |-- blog
|   |-- icons
|   |-- images
|   |-- media
|   |-- modules
|   `-- text
|-- images
|-- inc
|-- javascripts
|-- license
|-- projects
|-- prometheus
|   |-- newsletter
|   `-- publications
|-- series                            ...  Image series
|-- stylesheets
`-- tools
\endverbatim

\li The \c images subdirectory contains (small) images used as part of the
page layout and its navigation elements:
\verbatim
.
`-- images/
    |-- icon
    |-- misc
    `-- sidebar
\endverbatim

\li Configuration settings of and postings to the Blog are split across two
directories: while rendering settings are stored in \c blog, the actual
blog entries are collected in \c _posts.
\verbatim
.
|-- _posts
`-- blog
\endverbatim

\li Stylesheets for the various representations/renderings of the homepage
are collected within the \c styleheets directory:
\verbatim
.
`-- stylesheets/
    |-- application.css
    |-- application_ie.css
    |-- application_ie7.css
    |-- mobile.css
    |-- noscript.css
    |-- print.css
    |-- screen.css
    `-- syntax.css
\endverbatim

\li Configuration files for Jekyll - the tool used to build the static HTML
pages - can be found in \c _config.

\li The directory \c series contains data - images and descriptions - for the
image series featured on the homepage.
\verbatim
.
`-- series/
    |-- 2010
    |-- 2011
    `-- 2012
\endverbatim

\section homepage_build Building the Homepage

\subsection homepage_build_pre Prerequisites

\b Pygments aims to be a generic syntax highlighter for general use in all
kinds of software such as forum systems, wikis or other applications that need
to prettify source code. You can check if the command-line tool is available
via
\verbatim
which pygmentize
\endverbatim
If the result turns out to be empty, there are at least two routes to install
the tool:
\li Using Ruby Gems, where [pygmentize](https://github.com/djanowski/pygmentize)
provides a standalone Pygments for Ruby
\code
gem install pygmentize
\endcode
\li Using the system's package manager (e.g. \c apt-get on
[Debian GNU/Linux](http://www.debian.org))
\code
apt-get install python-pygments
\endcode

\subsection homepage_build_tasks Rake tasks

Building the website from the sources files is controlled through a number of
Rake tasks; in order to get a list of the available tasks run
\code
rake -T
\endcode
Available tasks are:
| Task                | Description |
|---------------------|-------------|
| rake build          | Build the site |
| rake clean          | Remove current site |
| rake live           | Run following tasks in live environment |
| rake series_preview | Build preview for start page with NUM's (yyyy/ww) image series |
| rake setup          | Set up build environment |
| rake staging        | Run following tasks in staging environment |
| rake tag            | Tag release |

To build the website from the sources, run
\verbatim
rake setup
rake build
\endverbatim
Unless defined otherwise, the generated site will be placed into the \c _site
directory
\verbatim
.
`-- _site/
    |-- about
    |-- blog
    |-- databases
    |-- files
    |-- images
    |-- inc
    |-- javascripts
    |-- license
    |-- page2
    |-- page3
    |-- page4
    |-- page5
    |-- page6
    |-- projects
    |-- prometheus
    |-- series
    |-- stylesheets
    |-- tag
    `-- tools
\endverbatim
