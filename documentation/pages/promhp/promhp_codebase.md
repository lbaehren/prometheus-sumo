Organization of the source code    {#promhp_codebase}
===============================

\tableofcontents

After checkout out a working copy from the
[repository hosted on Github](https://github.com/prometheus-ev/promhp),
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

\section promhp_codebase_images Images

The \c images subdirectory contains (small) images used as part of the
page layout and its navigation elements:
\verbatim
.
`-- images/
    |-- icon
    |-- misc
    `-- sidebar
\endverbatim

\section promhp_codebase_blog Blog configuration

Configuration settings of and postings to the Blog are split across two
directories: while rendering settings are stored in \c blog, the actual
blog entries are collected in \c _posts.
\verbatim
.
|-- _posts
`-- blog
\endverbatim

\section promhp_codebase_stylesheets Stylesheets

Stylesheets for the various representations/renderings of the homepage
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

\section promhp_codebase_jekyll Jekyll configuration

Configuration files for Jekyll - the tool used to build the static HTML
pages - can be found in \c _config.

\section promhp_codebase_series Image series

The directory \c series contains data - images and descriptions - for the
image series featured on the homepage.
\verbatim
.
`-- series/
    |-- 2010
    |-- 2011
    `-- 2012
\endverbatim

