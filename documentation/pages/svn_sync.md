Mirroring with svnsync    {#svn_sync}
======================

\tableofcontents

If you like to keep all your work under svn source control, you're probably going to also want to keep a backup of your svn repositories in case of a hardware failure or some other catastrophic event. svn comes with a utility to help you do this - svnsync, which we can use to keep a real-time, read only backup of our svn repositories.

\section subversion_svnsync_slave On the Slave

On your Slave machine, set up a new svn repository. It's very important that you don't make any commits in this repository - it needs to be a blank canvas for svnsync to work with.
\verbatim
svnadmin create /svr/svn/myrepo
chown -R www-data:www-data /svr/svn/myrepo
\endverbatim
Since this repository is going to be a read-ony mirror, the best thing is to create a dedicated svnsync user that has read/write access to the repository. This should be the only user that is allowed to write to the repository to avoid accidental repository writes.

Set up Apache to make the repository available over the net.
\verbatim
<Location>
  DAV svn
  SVNParentPath /srv/svn/repos/
  AuthType Basic
  AuthName "My Read-only SVN Mirror"
  AuthUserFile /srv/svn/dav_svn.passwd
  Require valid-user
</Location>
\endverbatim

Then create the [htpasswd](http://httpd.apache.org/docs/2.2/programs/htpasswd.html)
file to allow the svnsync user access to the repository:
\verbatim
htpasswd -c /srv/svn/dav_svn.passwd svnsync
\endverbatim

Now, for a little more added security we will limit the repository so that it will only allow our svnsync user to make commits. We do this by creating a start-commit hook (still on the slave machine). Create the file `/srv/svn/repos/myproject/hooks/start-commit`).
\verbatim
#!/bin/sh
USER="$2"
if [ "$USER" = "svnsync" ];
  then exit 0;
fi
echo "Only the svnsync user may commit new revisions" >&2 exit 1
\endverbatim

And by a similar token, we want to be sure that svnsync is the only user that is able to add, modify or delete revision properties. Create the file `/srv/svn/repos/myproject/hooks/pre-revprop-change`.
\verbatim
#!/bin/sh
USER="$3"
if [ "$USER" = "svnsync" ];
  then exit 0;
fi
echo "Only the svnsync user may change revision properties" >&2 exit 1
\endverbatim

Make sure both of these scripts are executable.
\verbatim
chmod 755 /srv/svn/repos/myproject/hooks/start-commit
chmod 755 /srv/svn/repos/myproject/hooks/pre-revprop-change
\endverbatim

For more information on the configuration of hooks, see section \ref svn_hooks.

\section subversion_svnsync_master On the Master

Our Slave machine is now ready, so jump over to the Master machine. First thing we need to do here is to initialise the svnsync target.
\verbatim
svnsync initialize https://target/myproject/ https://source/myproject/ \
--sync-username svnsync --sync-password syncpassword \
--source-username sourceusername --source-password sourcepassword
\endverbatim
Next, we want to add a post-commit script to tell our master repository that it should run svnsync after every commit. Create the file /srv/svn/repos/myproject/hooks/post-commit.
\verbatim
#!/bin/sh
SVNSYNC=/usr/bin/svnsync
TO=http://my.slave.machine/myproject/
SYNC_USER=svnsync
SYNC_PASS=syncpassword
SOURCE_USER=me
SOURCE_PASS=mypassword

$SVNSYNC --non-interactive sync $TO \
--sync-username $SYNC_USER --sync-password $SYNC_PASS \
--source-username $SOURCE_USER --source-password $SOURCE_PASS &  exit 0
\endverbatim
One last thing, we also want to ensure that changes to revision properties are also synced. Create the file /srv/svn/repos/myproject/hooks/post-revprop-change.
\verbatim
#!/bin/sh
SVNSYNC=/usr/bin/svnsync
TO=http://my.slave.machine/myproject/
SYNC_USER=svnsync
SYNC_PASS=syncpassword
SOURCE_USER=me
SOURCE_PASS=mypassword

$SVNSYNC --non-interactive copy-revprops $TO \
--sync-username $SYNC_USER --sync-password $SYNC_PASS \
--source-username $SOURCE_USER --source-password $SOURCE_PASS $2 & exit 0
\endverbatim
Make sure both of these scripts are executable.
\verbatim
chmod 755 /srv/svn/repos/myproject/hooks/post-commit
chmod 755 /srv/svn/repos/myproject/hooks/post-revprop-change
\endverbatim
And that should be it!
