JekyllCommander    {#JekyllCommander}
===============

\tableofcontents

**JekyllCommander** is a Sinatra based web application, to give non-technical users
the ability to maintain a complex Jekyll website, including git version control,
without any scary terminal experiences.

**JekyllCommander** has been developed to fit exactly our needs. Some parts are
highly specific to our Website <https://github.com/prometheus-ev/promhp> and
our workflow. But maybe you can take some advantage of this code, anyway.

We are thinking about changing JekyllCommander to be more generic, but you know:
Fork it, if we are to slow for you.

\section JekyllCommander_how How it works

Because this is smart, the sources of our website are living in a git
repository. This repo will be cloned by JekyllCommander as a working copy for
every user. Users can make their changes via JekyllCommander's web interface
and generate an own preview.

All changes an user made will be merged into a staging version of the website
when he/she decides that everything is done so far. This staging repo, which
has its own preview, combines the commits of all user.
And at one point, in the case that everything is alright, it can go public. This
means (in the background) that all changes will be pushed to the live repo.
In our case this (or rather pushing a tag) triggers the system to generate the
webside and move it into the document root of our webserver. There are our
scripts in the "example" folder for a better understanding.

\section JekyllCommander_requirements Installation requirements

* [grit](https://github.com/mojombo/grit) - object oriented read/write access to Git repositories via Ruby.
* [jekyll](http://jekyllrb.com) - a simple, blog aware, static site generator.
* [jekyll_commander](https://github.com/prometheus-ev/JekyllCommander) - a Sinatra based web interface, to maintain a Jekyll website, including git version control
* logger - a simple logging utility.

\section JekyllCommander_code Organization of the source code

After checking out a working copy of the source code, you will presented with
the following directory structure:

\verbatim
 .
 |-- examples
 |-- lib
 |-- public
 |   |-- css
 |   |-- images
 |   |-- js
 |   `-- markitup
 |       |-- sets
 |       |   |-- default
 |       |   |   `-- images
 |       |   |-- html
 |       |   |   `-- images
 |       |   |-- markdown
 |       |   |   `-- images
 |       |   `-- textile
 |       |       `-- images
 |       |-- skins
 |       |   |-- markitup
 |       |   |   `-- images
 |       |   `-- simple
 |       |       `-- images
 |       `-- templates
 |-- tmp
 `-- views
\endverbatim

\section JekyllCommander_install Installation

Will hopefully be written in the near future...

\section JekyllCommander_configure Configuration

In order to configure your installation you will have to create a `config.yamle`
file in the root directory of your installation; an example file
`config.yaml.sample` is provided, which can be used as starting point for
your own settings.

\verbatim
    ---
    :repo:    git@example.com:repos/repo.git
    :site:    http://example.com
    :staging: /staging
    :preview: /preview-%s
    :email:   %s@example.com

    :users:
      jd: { :name: John Doe, :email: jdoe@example.net }
\endverbatim