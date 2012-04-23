
# Deploying a new release of pandora

## Introduction

Deploying a new production version of _pandora_ (The prometheus digital image
archive software) requires the completion of a number of steps, some of them 
locally through a working copy of the source code, others on the server hosting
the live versions of the archive software. The steps include

- Marking the release version
- Creating a tag for the release
- Creating a new release on the stable branch
- Deploying the stable version on the test system
- Deploying the stable version on the production system

## Procedure

### Commit changes in trunk

The very first step before starting the actual deploy procedure

    $ rake spec

Commit all the changes to be included into the trunk of the Subversion repository:

    $ svn commit -m "<commit message>"

Review changes since last deploy; in order to get the version number used for the
last deploy, go to the {http://prometheus.uni-koeln.de/pandora/about About pandora}
page on the prometheus website.

    $ svn log -r 3679:HEAD

### Increment version number

The version number is encoded in the following files, where it must be adjusted
manually:

  * lib/pandora/version.rb
  * README

Push the previous changes upstream:

    $ svn commit -m "lib/pandora/version.rb: v0.6.5 -- Added news-box to sidebar."

Comitting the changes to the server will be acknowledged:

    Sending        trunk/README
    Sending        trunk/lib/pandora/version.rb
    Transmitting file data ..
    Committed revision 3705.

### Tag for new release

Once the version number has been adjusted, it is time to create a new tagged
version of the code base:

    $ svn copy ^/trunk ^/tags/0.6.5 -m "Tagging the pandora 0.6.5 release"

### Create stable branch

In order to propagate the same set of changes, as previously tagged with the new
version, to a stable branch, we need to merge the changes submitted to the
``trunk``; for this change into the directory of the targetted release version

    cd pandora/branches/0.6-stable

and instruct Subversion to perform the merge:

    $ svn merge ^/trunk

Which versions exactly have been included in the merge, can be retrieved through

    $ svn diff --depth=empty

The output from that will look something like:

    Property changes on: .
    ___________________________________________________________________
    Modified: svn:mergeinfo
       Merged /trunk:r3677-3706

With the above information we now have everything available to commit the new stable
version:

    $ svn commit -m "Merged r3677-3706 from trunk. (v0.6.5)"

The commit itself will once more display the list of files which are being pushed
onto the server:

    Sending        0.6-stable
    Sending        0.6-stable/README
    ...
    Adding         0.6-stable/public/images/sidebar
    Adding  (bin)  0.6-stable/public/images/sidebar/box_close.gif
    Transmitting file data ...............................................
    Committed revision 3707.

### Deploy stable version

Before rolling out the new version on the production system, one always should
check the effect of the changes on the _stable_ system

    http://prometheus-test.uni-koeln.de/pandora-stable/

The actual deployment is controlled through _capistrano_. E.g., to restart the
stable cluster:

    $ cap stable deploy:restart

The output will look something like this:

    * executing `stable'
    * executing `deploy:restart'
      triggering before callbacks for `deploy:restart'
    * executing "svnversion /var/local/prometheus/app/pandora/stable"
      servers: ["134.95.80.12"]

At this point you will be questioned for your password to log into the remote server.

    [134.95.80.12] executing command
    executing locally: "svn info http://prometheus-srv.uni-koeln.de/svn/pandora/trunk  -rHEAD"
    command finished in 42ms
    command finished in 594ms
  * executing `deploy:mongrel:restart'
  * executing "sudo -p 'AFS Password: ' mongrel_rails cluster::restart -C /var/local/prometheus/app/pandora/stable/config/mongrel_cluster.yml.$CAPISTRANO:HOST$"
    servers: ["134.95.80.12"]
    [134.95.80.12] executing command
 ** [out :: 134.95.80.12] stopping port 8050
 ** [out :: 134.95.80.12] stopping port 8051
 ** [out :: 134.95.80.12] starting port 8050
 ** [out :: 134.95.80.12] starting port 8051
    command finished in 3444ms

### Check status of the staging cluster

Log in onto the staging server

    $ ssh <login>@prometheus2.uni-koeln.de

The ``pandora_cluster`` tool is used to inspect the status of the server; if the
``bin`` directory of the prometheus installation already is in your ``PATH`` simply
type

    $ TARGET=stable pandora_cluster ps

Otherwise provide the full path to the executable:

    $ TARGET=stable /var/local/prometheus/bin/pandora_cluster ps

If the result is empty, none of the required cluster processes is active; in such
case it will be necessary to start them manually via

    $ TARGET=stable pandora_cluster start

Where ``TARGET`` designates the stage to apply the command to. It's either ``current``
(default) for the production system, +stable+ for the "stable" staging environment,
or ``trunk`` for the "development" (cutting edge) staging environment. The former
lives on ``prometheus1.uni-koeln.de``, the latter two on ``prometheus2.uni-koeln.de``.

### Deploy new production system

Deployment from the stable version onto the production system can be controlled
through capistrano:

    $ cap production deploy

Amongst the log messages provided you should see e.g.

    * executing `production'
    * executing `deploy'
    * executing `deploy:update'
   ** transaction: start
    * executing `deploy:update_code'
      executing locally: "svn info http://<pandora SVN root>/branches/0.6-stable  -rHEAD"
      command finished in 38ms
    * executing "svn checkout -q  -r3707 http://<pandora SVN root>/branches/0.6-stable /var/local/prometheus/app/pandora/releases/20120416143435 && (echo 3707 > /var/local/prometheus/app/pandora/releases/20120416143435/REVISION)"


## Troubleshooting

There are quite a number of reasons why the deployment process might fail or stop
along the lines - first point to retrieve diagnostics information should be the
log messages generated while the deploy is running.

### Unable to run pandora_cluster executable

Most likely the ``bin`` directory of the prometheus installation is not in your path:

    $ export PATH=$PATH:/var/local/prometheus/bin

### No documentation generated

Part of the deployment process is the generation of the documentation; if this
step fails, the new version will not be activated. One of the possible causes
might be that the user trying to deploy the new version does not have sufficient
accss permissions to the files and directories which need to be touched in the 
process - ideally this aspects should be covered by the Rake and Capistrano
scripts. In order to investigate (and possibly mitigate) this problem, you
will have to log onto the server, in order to have a closer look at the 
files and directories in question.