Logwatch    {#logwatch}
========

\tableofcontents

Logwatch is a modular log analyser that runs every night and mails you the
results. It can also be run from command line. The output is by service and you
can limit the output to one particular service. The subscripts which are
responsible for the output, mostly convert the raw log lines in structured format.

Logwatch generally ignores the time component in the output, that means, you will
know that the reported event was logged in the requested range of time, but you
will have to go to the raw log files to get the exact details.

\section logwatch_installation Installation

\subsection logwatch_installation_debian ... on Debian/Ubuntu

Install logwatch using the following command

    sudo apt-get install logwatch

This will install all the required packages.

\subsection logwatch_installation_osx ... on Mac OS X

Logwatch is available via MacPorts:

    sudo port search logwatch

\section logwatch_configuration Configuration

Once you have installed Logwatch, you will need to configure it to email you the
reports it generates. You are encouraged to look through the entire configuration
(`/usr/share/logwatch/default.conf/logwatch.conf`), but you may safely use
Logwatch after editing the lines below.

~~~~
Output = mail
Format = html
MailTo = myemail@mydomain.com
MailFrom = logwatch@mydomain.com
~~~~

These directives tell Logwatch to email you reports in an HTML format. The
`MailTo` and `MailFrom` directives should be valid email addresses.

\section logwatch_usage Usage

\verbatim
logwatch [--detail <level>] [--logfile <name>]
   [--print] [--mailto <addr>] [--archives] [--range <range>] [--debug <level>]
   [--save <filename>] [--help] [--version] [--service <name>]
   [--numeric] [--output <output_type>]
   [--splithosts] [--multiemail]
\endverbatim

| Command line option | Description |
|---------------------|-------------|
| `--detail <level>`  | Report Detail Level - High, Med, Low or any #. |
| `--logfile <name>`  | *Name of a logfile definition to report on.    |
| `--logdir <name>`   | Name of default directory where logs are stored. |
| `--service <name>`  | *Name of a service definition to report on. |
| `--print`           | Display report to stdout.   |
| `--mailto <addr>`   | Mail report to `<addr>`.    |
| `--archives`        | Use archived log files too. |
| `--save <filename>` | Save to `<filename>`.       |
| `--range <range>`   | Date range: Yesterday, Today, All, Help, where help will describe additional options |
| `--numeric`         | Display addresses numerically rather than symbolically and numerically (saves  a  nameserver address-to-name lookup). |
| `--debug <level>`   | Debug Level - High, Med, Low or any #. |
| `--splithosts`      | Create a report for each host in syslog. |
| `--multiemail`      | Send each host report in a separate email. Ignored if not using `--splithosts`. |
| `--output <output type>` | Report Format - mail, html or unformatted#. |
| `--encode`               | Use base64 encoding on output mail. |
| `--version`              | Displays current version. |

\section logwatch_output Output

In its most basic form, it uses a set of predefined configuration options to scan
a wide range of log types on the system and presents it in a human-readable,
simply analyzed, plain text format like this:

\verbatim
 ################### Logwatch 7.3.6 (05/19/07) ####################
        Processing Initiated: Wed Feb  9 14:33:53 2011
        Date Range Processed: yesterday
                              ( 2011-Feb-08 )
                              Period is day.
      Detail Level of Output: 0
              Type of Output: unformatted
           Logfiles for Host: host.example
 ################################################################## 

 --------------------- Disk Space Begin ------------------------ 

 Filesystem  1K-blocks     Used    Avail Capacity  Mounted on
 /dev/ad0s1a    507630   466900      120   100%    /
 devfs               1        1        0   100%    /dev
 /dev/ad0s1e    507630   284336   182684    61%    /tmp
 /dev/ad0s1f  48709138 14977840 29834568    33%    /usr
 /dev/ad0s1d   3018382   191416  2585496     7%    /var
 linprocfs           4        4        0   100%    /usr/compat/linux/proc

 /dev/ad0s1a => 100% Used. Warning. Disk Filling up.
 devfs => 100% Used. Warning. Disk Filling up.
 linprocfs => 100% Used. Warning. Disk Filling up.

 ---------------------- Disk Space End ------------------------- 

 --------------------- Fortune Begin ------------------------ 

 Some of us are becoming the men we wanted to marry.
                -- Gloria Steinem

 ---------------------- Fortune End ------------------------- 

 ###################### Logwatch End #########################
\endverbatim

Default behavior for Logwatch is to send such information for the last day to an
email address. In most cases, no email address will be defined by default,
however; one can be specified with the `--mailto` option. To see output on the
screen, use the `--print` option instead.

\section logwatch_references References

* [How to setup Logwatch on Linux](http://photogabble.co.uk/technical/how-to-setup-logwatch-on-linux.html)
* [How to setup Logwatch on Ubuntu Desktop/Server](http://www.ubuntugeek.com/how-to-setup-logwatch-on-ubuntu-desktopserver.html)
* [Monitor System Logs with Logwatch on Ubuntu 10.04](http://library.linode.com/server-monitoring/logwatch/ubuntu-10.04-lucid)
* [How to customize Logwatch](http://www.stellarcore.net/logwatch/tabs/docs/HOWTO-Customize-LogWatch.html)