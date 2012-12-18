
Deploying a new version    {#pandora_deploy}
=======================

\tableofcontents

Deploying a new production version of \ref pandora (The prometheus digital image
archive software) requires the completion of a number of steps, some of them
locally through a working copy of the source code, others on the server hosting
the live versions of the archive software. The steps include

\li Marking the release version
\li Creating a tag for the release
\li Creating a new release on the stable branch
\li Deploying the stable version on the test system
\li Deploying the stable version on the production system


\section pandora_deploy_stable ... on the stable test system

Before rolling out the new version on the production system, one always should check the effect of the changes on the [stable system](http://prometheus-test.uni-koeln.de/pandora-stable).

The actual deployment is controlled through \ref capistrano . E.g., to restart the
stable cluster:

\verbatim
$ cap stable deploy:restart
\endverbatim

The output will look something like this:

\verbatim
* executing `stable'
* executing `deploy:restart'
  triggering before callbacks for `deploy:restart'
* executing "svnversion /var/local/prometheus/app/pandora/stable"
  servers: ["134.95.80.12"]
\endverbatim

At this point you will be questioned for your password to log into the remote server.

\verbatim
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
\endverbatim

\section pandora_deploy_staging ... on the staging test system

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
(default, marked by \b [*] in the table below) for the production system, ``stable`` for the "stable" staging environment,
or ``trunk`` for the "development" (cutting edge) staging environment. The former
lives on \ref servers_prom1, the latter two on \ref servers_prom2 .

  | Target name     | Staging environment |    Hosting machine |
  |-----------------|---------------------|--------------------|
  | ``current`` [*] | production          | \ref servers_prom1 |
  | ``stable``      | stable              | \ref servers_prom2 |
  | ``trunk``       | development         | \ref servers_prom2 |

\section pandora_deploy_production ... on the production system

Deployment from the stable version onto the production system can be controlled
through capistrano:

\verbatim
$ cap production deploy
\endverbatim

Amongst the log messages provided you should see e.g.

\verbatim
  * executing `production'
  * executing `deploy'
  * executing `deploy:update'
 ** transaction: start
  * executing `deploy:update_code'
    executing locally: "svn info http://<pandora SVN root>/branches/0.6-stable  -rHEAD"
    command finished in 38ms
  * executing "svn checkout -q  -r3707 http://<pandora SVN root>/branches/0.6-stable /var/local/prometheus/app/pandora/releases/20120416143435 && (echo 3707 > /var/local/prometheus/app/pandora/releases/20120416143435/REVISION)"
\endverbatim

\section pandora_deploy_trouble Troubleshooting

There are quite a number of reasons why the deployment process might fail or stop
along the lines - first point to retrieve diagnostics information should be the
log messages generated while the deploy is running.

  <dl>

    <dt>Unable to run \c pandora_cluster executable.</dt>
    <dd>
    Most likely the ``bin`` directory of the prometheus installation is not in your path:
    \verbatim
    $ export PATH=$PATH:/var/local/prometheus/bin
    \endverbatim
    </dd>

    <dt>No documentation generated.</dt>
    <dd>
    Part of the deployment process is the generation of the documentation; if this
    step fails, the new version will not be activated. One of the possible causes
    might be that the user trying to deploy the new version does not have sufficient
    accss permissions to the files and directories which need to be touched in the
    process - ideally this aspects should be covered by the Rake and Capistrano
    scripts. In order to investigate (and possibly mitigate) this problem, you
    will have to log onto the server, in order to have a closer look at the
    files and directories in question.
    </dd>
  </dl>
