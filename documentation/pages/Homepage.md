
Homepage    {#homepage}
========

\tableofcontents

\section homepage_overview Overview

In order to keep the amount of processing needed behind the scenes in order to
deliver the contents of the website to a minimum, all the pages are served as
\a static pages. The sources from which these pages are being generated are
hosted inside a Git repository, from which they can be obtained for editing
and rendering the resulting pages.

\subpage homepage_editing and \subpage homepage_build can be done at least in two
ways, depending on the user's proviciency with SCM tools (such as \ref Git);
aside the more developers-type approach -- i.e. checking out the sources, editing
them and thereafter committing back the changes -- there also exists a web-based
tool to aid iterating through a number of changes, allowing to preview them
before publishing the modifications made.

\section homepage_infrastructure Infrastructure 

\subsection homepage_infrastructure_srv3 prometheus-srv3

\c prometheus-srv3.uni-koeln.de 

\verbatim
/var/local/prometheus                        ...  Root of prometheus installation
           `-- srv
               `-- promhp
                   |-- live
                   |-- promhp.git            ...  Git repository
                   |-- promhp.git.old
                   `-- staging               ...  Staging version of website
\endverbatim

\subsection homepage_infrastructure_github Github

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
