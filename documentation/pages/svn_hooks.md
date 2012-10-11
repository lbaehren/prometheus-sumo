SVN Hooks    {#svn_hooks}
=========

\tableofcontents

\section subversion_hooks_pre_commit Pre-commit

The pre-commit hook is invoked before a Subversion txn is
committed. Subversion runs this hook by invoking a program
(script, executable, binary, etc.) named 'pre-commit' (for which
the file `pre-commit.tmpl` is a template), with the following ordered arguments:

\code
[1] REPOS-PATH   (the path to this repository)
[2] TXN-NAME     (the name of the txn about to be committed)
\endcode

The default working directory for the invocation is undefined, so
the program should set one explicitly if it cares.

If the hook program exits with success, the txn is committed; but
if it exits with failure (non-zero), the txn is aborted, no commit
takes place, and STDERR is returned to the client.   The hook
program can use the 'svnlook' utility to help it examine the txn.

On a Unix system, the normal procedure is to have 'pre-commit'
invoke other programs to do the real work, though it may do the
work itself too.

The hook program typically does not inherit the environment of
its parent process.  For example, a common problem is for the
PATH environment variable to not be set to its usual value, so
that subprograms fail to launch unless invoked via absolute path.
If you're having unexpected problems with a hook program, the
culprit may be unusual (or missing) environment variables.

The following pre-commit hook is configured for checking code
into the \ref pandora source code repository:
\code
#! /bin/bash

REPOS="$1"
TXN="$2"

SVNLOOK="/usr/bin/svnlook"

# Make sure that the log message contains some text.
$SVNLOOK log -t "$TXN" "$REPOS" | grep -q "[A-Z]" || {
  echo "Shame on you! Go put a proper log message in there at once, or..." 1>&2;
  exit 1;
}

# Condemn trailing whitespace!
$SVNLOOK diff --no-diff-deleted -t "$TXN" "$REPOS" | grep -q "^+.*[^-][[:space:]]$" && {
  echo "Get back to your code and remove the trailing whitespace!" 1>&2;
  exit 1;
}

# All checks passed, so allow the commit.
exit 0
\endcode

\section subversion_hooks_post_commit Post-commit

The post-commit hook is invoked after a commit.  Subversion runs
this hook by invoking a program (script, executable, binary, etc.)
named 'post-commit' (for which the file `post-commit.tmpl` is a template) with the
following ordered arguments:

\code
[1] REPOS-PATH   (the path to this repository)
[2] REV          (the number of the revision just committed)
\endcode

The default working directory for the invocation is undefined, so
the program should set one explicitly if it cares.

Because the commit has already completed and cannot be undone,
the exit code of the hook program is ignored.  The hook program
can use the 'svnlook' utility to help it examine the
newly-committed tree.

On a Unix system, the normal procedure is to have 'post-commit'
invoke other programs to do the real work, though it may do the
work itself too.

Note that 'post-commit' must be executable by the user(s) who will
invoke it (typically the user httpd runs as), and that user must
have filesystem-level permission to access the repository.

The following post-commit hook is configured for checking code
into the \ref pandora source code repository:
\code
#! /bin/bash

REPOS="$1"
REV="$2"

BASE="/var/local/prometheus"

SVN_SYNC="/usr/bin/svnsync"
COMMIT_EMAIL="$BASE/bin/commit-email.pl"
REDMINE_RUNNER="$BASE/srv/redmine/script/runner"

if [ -x "$COMMIT_EMAIL" ]; then
  TO=(pandora-devel@uni-koeln.de)
  FROM="pandora-svn-NOREPLY"
  PREFIX="[pandora-svn]"
  URL="http://prometheus-srv.uni-koeln.de/redmine/projects/pandora/repository/revisions/"

  $COMMIT_EMAIL "$REPOS" "$REV" -s "$PREFIX" --from "$FROM" -r "$TO" -u "$URL" "${TO[@]}"
fi

if [ -x "$SVN_SYNC" ]; then
  SYNC_USER="<user>"
  SYNC_PASS="<pass>"

  SYNC_DEST=(
    http://prometheus-app.uni-koeln.de/svn/pandora
    http://prometheus-test.uni-koeln.de/svn/pandora
  )

  for dest in "${SYNC_DEST[@]}"; do
    $SVN_SYNC sync "$dest" --username "$SYNC_USER" --password "$SYNC_PASS" --no-auth-cache &
  done
fi

if [ -x "$REDMINE_RUNNER" ]; then
  PATH=/usr/local/bin:/usr/bin:/bin $REDMINE_RUNNER -e production 'Project.find_by_name("pandora").repository.fetch_changesets' &
fi
\endcode

For details on how to set up the synchronization between the master repository and
repository mirros see section \ref svn_sync.
