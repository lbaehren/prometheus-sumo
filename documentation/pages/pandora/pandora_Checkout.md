Getting the source code    {#pandora_checkout}
=======================

\tableofcontents

At the time of writing these instructions (Oct 2012), the source code of
\ref pandora is hosted in a central \ref subversion repository, located at
http://prometheus-srv.uni-koeln.de/svn/pandora.

\section pandora_checkout_svn ... using Subversion

\subsection pandora_checkout_svn_full Full working copy

Checking out a full working copy from the \ref subversion repository

    svn co http://prometheus-srv.uni-koeln.de/svn/pandora pandora

will create a directory structure like this:

\verbatim
  pandora
  |
  |-- branches
  |   |-- 0.1-stable
  |   |-- 0.2-stable
  |   |-- 0.3-stable
  |   |-- 0.4-stable
  |   |-- 0.5-stable
  |   |-- 0.6-stable
  |   `-- restructuring_models_search_and_everything
  |-- tags
  |   |-- 0.1.0
  |   |-- 0.1.1
  |   |-- 0.1.2
  |   |-- ...
  |   `-- 0.6.5
  `-- trunk
      |-- app
      |-- config
      |-- db
      |-- doc
      |-- index
      |-- ...
\endverbatim

\subsection pandora_checkout_svn_trunk Development trunk

If you are interest only in the most recent version of the code -- a have no need
for all the extra branches and tags -- simply run

    svn co http://prometheus-srv.uni-koeln.de/svn/pandora/trunk pandora

which will result in a considerably simpler directory structure on your disk:

\verbatim
  pandora
  |-- app
  |-- config
  |-- db
  |-- doc
  |-- index
  |-- ...
\endverbatim

\section pandora_checkout_git ... using Git

If at a later point in time you want to be able to create new (release) branches
and tags then accordingly, you will have to clone from the top-level of the
Subversion repository, telling [Git](http://git-scm.com) import from a standard
directory layout:

\verbatim
git svn clone -s http://prometheus-srv.uni-koeln.de/svn/pandora pandora
\endverbatim

The resulting directory structure will look something like this:

\verbatim
    pandora/.git
    |-- hooks
    |-- info
    |-- logs
    |   `-- refs
    |       |-- heads
    |       `-- remotes
    |           `-- tags
    |-- objects
    |-- refs
    |   |-- heads
    |   |-- remotes
    |   |   `-- tags
    |   `-- tags
    `-- svn
        `-- refs
            `-- remotes
                |-- 0.1-stable
                |-- 0.2-stable
                |-- 0.3-stable
                |-- 0.4-stable
                |-- 0.5-stable
                |-- 0.6-stable
                |-- git-svn
                |-- restructuring_models_search_and_everything
                |-- tags
                |   |-- 0.1.0
                |   |-- 0.1.1
                |   |-- 0.1.2
                |   |...
                |   `-- 0.6.5
                `-- trunk
\endverbatim

