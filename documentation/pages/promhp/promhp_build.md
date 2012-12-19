Building the Homepage    {#promhp_build}
=====================

\tableofcontents

\section promhp_build_pre Prerequisites

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

\section promhp_build_tasks Rake tasks

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
