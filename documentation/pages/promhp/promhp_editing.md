Editing the homepage    {#promhp_editing}
====================

\tableofcontents

Editing the contents (i.e. the pages) of the website can be done in two different
ways:

\li Editing the files within the local working copy obtained from the code
repository.

\li Modifying files through the [Jekyll Commander](https://github.com/prometheus-ev/JekyllCommander), a Sinatra based web interface, to maintain a Jekyll website, including Git version control.

While the first of the two methods - w.r.t. the editing of the source files -
is no different from any other source code working copy, the resulting static
webpages need to be generated locally as, in order to verify the changes.

\section homepage_editing_manual Manual editing

\li Check out a working copy of the source files, as described in section
\ref homepage_code above.

\li Make the changes you would like to make, using your favorite text editor.

\li Preview the result of your changes, following the procedure described in
section \ref homepage_build below.

\li If the result ok -- possibly after iterating through the previous two
points a number of times -- you can check in your changes
\code
git add <files>
git commit -m <commit message>
\endcode
and push them back to the repository on Github.

\section homepage_editing_command Editing using the Jekyll Commander

  Starting up the [Jekyll Commander](http://prometheus-app.uni-koeln.de/promhp)
  it will take a few seconds before the interface is initialized for usage; the
  for this is, that in the background a working copy of the source code is being
  updated, such that changes can be submitted once they have been carried out.

  \image html promhp__Jekyll_Commander.png
  \image latex promhp__Jekyll_Commander.png "Start page of the Jekyll Commander" width=.9\textwidth

  If you want to edit a specific page, use the navigation panel to the left in
  order to select it.; clicking on the filename will open up the file contents
  in an embedded editor:

  \image html promhp__Edit_page.png
  \image latex promhp__Edit_page.png "Editing a page within Jekyll Commander" width=.9\textwidth

  All changes an user made will be merged into a staging version of the website
  when he/she decides that everything is done so far. This staging repo, which
  has its own preview, combines the commits of all user.

  \image html promhp__Safe_changes.png
  \image latex promhp__Safe_changes.png "Saving changes" width=.9\textwidth

  Once the changes have have been saved, a preview can be rendered, such that is
  possible to inspect the outcome; since this signifies that (most of the time)
  the complete website needs to be regenerated, this process might take a while.

  \image html promhp__Site_update.png

  And at one point, in the case that everything is alright, it can go public. This
  means (in the background) that all changes will be pushed to the live repo.
  In our case this (or rather pushing a tag) triggers the system to generate the
  webside and move it into the document root of our webserver. There are our
  scripts in the "example" folder for a better understanding.

  \image html promhp__Publish_site.png
  \image latex promhp__Publish_site.png "Publish the changes to the website." width=.9\textwidth

