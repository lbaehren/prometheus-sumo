
Releasing a new version    {#pandora_release}
=======================

\tableofcontents

\section pandora_release_commit Commit pending changes

\li Update your working copy to ensure that all the changes to be included
in the new release version have been merged properly:
\verbatim
svn up
\endverbatim

\li Commit all the changes to be included into the trunk of the Subversion
repository:
\verbatim
$ svn commit -m "<commit message>"
\endverbatim

\section pandora_release_testing Run the test suite

Run the tests: Before starting the actual deploy, it should be checked
that no errors are turned up by running the tests:
\verbatim
$ rake spec
\endverbatim
If the tests turn up errors, ensure that they get fixed before starting the
procedure to tag and release a new version of the software.

\a Note: There is a [helper script](https://gist.github.com/146886) to run
specs before each commit and restart staging server afterwards.

\section pandora_release_version Increment version number

Update the version number included within the \ref pandora source files:

\verbatim
pandora
|-- README
`-- lib
    `-- pandora
        `-- version.rb
\endverbatim

\li \c README
\code
= pandora - The prometheus digital image archive software

== VERSION

This documentation refers to pandora version 0.6.8
\endcode
  \li \c lib/pandora/version.rb
  \code{.rb}
module Pandora

  module Version

    MAJOR = 0
    MINOR = 6
    TINY  = 8

    class << self
\endcode

\section pandora_release_changes Review changes since last deploy

Review changes since last deploy, in order to provide the commit for the
new release version with a proper commit message.

\li Get the version number of the previous release/deploy - this can be done either via
      - the [About pandora](http://prometheus.uni-koeln.de/pandora/about) page or
      - the [Redmine issue tracker](http://prometheus-srv.uni-koeln.de/redmine/projects/pandora/repository/show/tags).

  \li Review the log commit messages for the changes since the last release:
  \verbatim
  $ svn log -r <previous release>:HEAD
  \endverbatim
  \a Note: Keep in mind that the version number to compare against actually is
  one after the previous release.

  \li Push the previous changes upstream:
  \verbatim
  $ svn commit -m "lib/pandora/version.rb: v0.6.5 -- Added news-box to sidebar."
  \endverbatim
  Comitting the changes to the server will be acknowledged:
  \verbatim
  Sending        trunk/README
  Sending        trunk/lib/pandora/version.rb
  Transmitting file data ..
  Committed revision 3705.
  \endverbatim

\section pandora_release_tagging Tagging the release version

Once the version number has been adjusted, it is time to create a new tagged
version of the code base:

  \li ... using Subversion:
  \verbatim
  $ svn copy ^/trunk ^/tags/0.6.5 -m "Tagging the pandora 0.6.5 release"
  \endverbatim
  \li ... using Git:
  \verbatim
  git svn branch
  \endverbatim
  with the additional options \c -m (Allows to specify the commit message) and
  \c -t (Create a tag by using the tags_subdir instead of the branches_subdir
  specified during git svn init):
  \verbatim
  git svn branch -t -m "Tagging the pandora 0.6.5 release" 0.6.5
  \endverbatim

\section pandora_release_stable Create stable branch

  In order to propagate the same set of changes, as previously tagged with the new
  version, to a stable branch, we need to merge the changes submitted to the
  ``trunk``:

  \li Change into the directory of the targetted release version
  \verbatim
  cd pandora/branches/0.6-stable
  \endverbatim

  \li Merge the \c trunk into the stable branch:
      - Include all versions since last deploy:
      \verbatim
      $ svn merge ^/trunk
      \endverbatim
      - Include selected versions only:
      \verbatim
      $ svn merge ^/trunk -r <versions>
      \endverbatim

  \li Review the versions included into the merge:
  \verbatim
  $ svn diff --depth=empty
  \endverbatim
  The output from that will look something like:
  \verbatim
  Property changes on: .
  ___________________________________________________________________
  Modified: svn:mergeinfo
     Merged /trunk:r3677-3706
  \endverbatim

  \li Commit the new stable version:
  \verbatim
  $ svn commit -m "Merged r3677-3706 from trunk. (v0.6.5)"
  \endverbatim
  The commit itself will once more display the list of files which are being pushed
  onto the server:
  \verbatim
  Sending        0.6-stable
  Sending        0.6-stable/README
  ...
  Adding         0.6-stable/public/images/sidebar
  Adding  (bin)  0.6-stable/public/images/sidebar/box_close.gif
  Transmitting file data ...............................................
  Committed revision 3707.
  \endverbatim
