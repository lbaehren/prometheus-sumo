
# Deploying a new release of pandora

## Procedure

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