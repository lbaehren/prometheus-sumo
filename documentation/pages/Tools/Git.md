Git    {#git}
===

\tableofcontents

[Git](http://www.git-scm.com) is a distributed revision control system with an
emphasis on being fast. Git was initially designed and developed by Linus Torvalds
for [Linux kernel](http://www.kernel.org) development.

Every Git working directory is a full-fledged repository with complete history
and full revision tracking capabilities, not dependent on network access or a
central server.

\section git_configuration Configuration

\ref subversion includes your _username_ in your commits, whereas Git includes
your _real name_ and your _e-mail address_. You should add these before you
start using Git:

\verbatim
git config --global user.name "Your Name"
git config --global user.email you@yourdomain.example.com
\endverbatim

`git config` is the command to set configuration options. While you're
configuring, here are some other things you might like to do:

\verbatim
git config --global color.ui auto    # colorised `git diff`, etc.
git config --global alias.st status  # make `git st` work
git config -l                        # list all configuration options
\endverbatim

\section git_submodules Submodules

Large projects are often composed of smaller, self-contained modules. For
example, an embedded Linux distribution's source tree would include every
piece of software in the distribution with some local modifications; a movie
player might need to build against a specific, known-working version of a
decompression library; several independent programs might all share the same
build scripts.

With centralized revision control systems this is often accomplished by including
every module in one single repository. Developers can check out all modules or
only the modules they need to work with. They can even modify files across several
modules in a single commit while moving things around or updating APIs and
translations.

Git does not allow partial checkouts, so duplicating this approach in Git would
force developers to keep a local copy of modules they are not interested in
touching. Commits in an enormous checkout would be slower than you'd expect as
Git would have to scan every directory for changes. If modules have a lot of
local history, clones would take forever.

On the plus side, distributed revision control systems can much better integrate
with external sources. In a centralized model, a single arbitrary snapshot of
the external project is exported from its own revision control and then imported
into the local revision control on a vendor branch. All the history is hidden.
With distributed revision control you can clone the entire external history and
much more easily follow development and re-merge local changes.

Git's submodule support allows a repository to contain, as a subdirectory, a checkout of an external project. Submodules maintain their own identity; the submodule support just stores the submodule repository location and commit ID, so other developers who clone the containing project (“superproject”) can easily clone all the submodules at the same revision. Partial checkouts of the superproject are possible: you can tell Git to clone none, some or all of the submodules.

\subsection git_submodules_usage Command usage

The git submodule command is available since Git 1.5.3. Users with Git 1.5.2 can look up the submodule commits in the repository and manually check them out; earlier versions won't recognize the submodules at all.

\verbatim
  git submodule [--quiet] add [-b branch] [-f|--force]
                [--reference <repository>] [--] <repository> [<path>]
  git submodule [--quiet] status [--cached] [--recursive] [--] [<path>...]
  git submodule [--quiet] init [--] [<path>...]
  git submodule [--quiet] update [--init] [-N|--no-fetch] [--rebase]
                [--reference <repository>] [--merge] [--recursive] [--] [<path>...]
\endverbatim

\subsection git_submodules_recipes Recipes

Note: the `[main]$` bits on each line represents your bash prompt. You should
only type the stuff after the `$`.

 * Set up the submodule for the first time:
\verbatim
 [~]$  cd ~/main/
 [main]$  git submodule add git://github.com/my/submodule.git ./subm
 [main]$  git submodule update --init
 [main]$  git commit ./submodule -m "Added submodule as ./subm"
\endverbatim
 * Fetch submodules after cloning a repository:
\verbatim
 [~]$  git clone git://github.com/my/main.git ~/main
 [~]$  cd ~/main/
 [main]$  git submodule update --init
\endverbatim
 * Pull upstream main repo changes and update submodule contents:
\verbatim
 [main]$  git pull origin/master
 [main]$  git submodule update
\endverbatim
 * Pull upstream changes to the submodule:
\verbatim
 [main]$  cd ./subm
 [subm]$  git pull origin/master   # or fetch then merge
 [subm]$  cd ..
 [main]$  git commit ./subm -m "Updated submodule reference"
\endverbatim
 * Edit and commit files in your submodule:
\verbatim
 [main]$  cd ./subm
 [subm]$  edit whatever.rb
 [subm]$  git commit whatever.rb -m "Updated whatever.rb"
 [subm]$  cd ..
 [main]$  git commit ./subm -m "Updated submodule reference"
\endverbatim
 * Push your submodule changes to the submodule upstream:
\verbatim
 [main]$  cd ./subm
 [subm]$  git push origin master
\endverbatim

\section git_subtree Subtrees

Subtrees allow subprojects to be included within a subdirectory of the main
project, optionally including the subproject's entire history.

For example, you could include the source code for a library as a subdirectory of
your application.

Subtrees are not to be confused with \ref git_submodules, which are meant for the same task.
Unlike submodules, subtrees do not need any special constructions (like .gitmodule
files or gitlinks) be present in your repository, and do not force end-users of
your repository to do anything special or to understand how subtrees work. A
subtree is just a subdirectory that can be committed to, branched, and merged along
with your project in any way you want.

They are also not to be confused with using the subtree merge strategy. The main
difference is that, besides merging the other project as a subdirectory, you can
also extract the entire history of a subdirectory from your project and make it
into a standalone project. Unlike the subtree merge strategy you can alternate back
and forth between these two operations. If the standalone library gets updated, you
can automatically merge the changes into your project; if you update the library
inside your project, you can "split" the changes back out again and merge them back
into the library project.

For example, if a library you made for one application ends up being useful
elsewhere, you can extract its entire history and publish that as its own git
repository, without accidentally intermingling the history of your application
project.

\verbatim
  git subtree add   -P <prefix> <commit>
  git subtree pull  -P <prefix> <repository> <refspec...>
  git subtree push  -P <prefix> <repository> <refspec...>
  git subtree merge -P <prefix> <commit>
  git subtree split -P <prefix> [OPTIONS] [<commit>]
\endverbatim

\subsection git_subtree_branch Extract a subtree using branch

Suppose you have a source directory with many files and subdirectories, and you
want to extract the lib directory to its own git project. Here's a short way to do
it:

First, make the new repository wherever you want:
\verbatim
<go to the new location>
git init --bare
\endverbatim
Back in your original directory:
\verbatim
git subtree split --prefix=lib --annotate="(split)" -b split
\endverbatim
Then push the new branch onto the new empty repository:
\verbatim
git push <new-repo> split:master
\endverbatim

\section git_timetracking Time-tracking

Usage:

\verbatim
git timetrack command [options]
\endverbatim

Current timer commands:

\verbatim
  -s, --start                start/continue counting time spent
  -k, --start-hacking        start/continue counting time spent, won't stop (only reset) on commit
  -p, --stop                 stop/pause counting time spent
  -r, --reset                reset counting time spent
  -g  --add <[-]minutes>     add (or substract) time from the timer
  -e, --set <minutes>        set time spent in minutes
  -ts, --timesince           set time spent since last commit
  -c, --current              time spent currently in next commit
\endverbatim

\section git_references References

 * [Git](http://www.git-scm.com)
 * [Understanding Git submodules](http://speirs.org/blog/2009/5/11/understanding-git-submodules.html)
 * [Git Submodules Cheat Sheet](http://blog.jacius.info/git-submodule-cheat-sheet)
 * [git-svn Manual pages](http://kernel.org/pub/software/scm/git/docs/git-svn.html)
 * [Git Community Book](http://book.git-scm.com)
 * [git SVN Tutorial](http://trac.parrot.org/parrot/wiki/git-svn-tutorial)
 * [An introduction to git-svn](http://utsl.gen.nz/talks/git-svn/intro.html)
 * [Intro to distributed version control](http://betterexplained.com/articles/intro-to-distributed-version-control-illustrated)
 * [Sharing code between projects with git subtree](http://psionides.eu/2010/02/04/sharing-code-between-projects-with-git-subtree)
 * [Modular git with "git subtree"](http://log.pardus.de/2012/08/modular-git-with-git-subtree.html)
 * [A new alternative to git submodules: git subtree](http://apenwarr.ca/log/?m=200904#30)
 * [Git subtree notes and workflows](http://www.tipstank.com/2011/02/21/git-subtree-notes-and-workflows)