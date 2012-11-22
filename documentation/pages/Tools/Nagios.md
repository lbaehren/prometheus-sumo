Nagios    {#nagios}
======

\tableofcontents

\section nagios_overview Overview

**Nagios** is an open source computer system monitor, network monitoring and
infrastructure monitoring software application. Nagios offers monitoring and
alerting for servers, switches, applications, and services. It watches hosts
and services. It alerts users when things go wrong and alerts them again when
those wrong things get better/resolved.

Nagios, originally created under the name NetSaint, was written and is currently
maintained by Ethan Galstad, along with a group of developers actively maintaining
both official and unofficial plugins. N.A.G.I.O.S. is a recursive acronym: "Nagios
Ain't Gonna Insist On Sainthood", "Sainthood" being a reference to the original
name NetSaint, which was changed in response to a legal challenge by owners of a
similar trademark. "Agios" is also a transliteration of the Greek word άγιος which
means "saint".

Nagios was originally designed to run under Linux, but also runs well on other Unix
variants. It is free software, licensed under the terms of the GNU General Public
License version 2 as published by the Free Software Foundation.

*  Monitoring of network services (SMTP, POP3, HTTP, NNTP, ICMP, SNMP, FTP, SSH)
* Monitoring of host resources (processor load, disk usage, system logs) on a majority of network operating systems, including Microsoft Windows with the NSClient++ plugin or Check MK.
*  Monitoring of anything else like probes (temperature, alarms...) which have the ability to send collected data via a network to specifically written plugins
*  Monitoring via remotely-run scripts via Nagios Remote Plugin Executor
* Remote monitoring supported through SSH or SSL encrypted tunnels.
* Simple plugin design that allows users to easily develop their own service checks depending on needs, by using the tools of choice (shell scripts, C++, Perl, Ruby, Python, PHP, C#, etc.)
* Plugins available for graphing of data
* Parallelized service checks available
* Ability to define network host hierarchy using "parent" hosts, allowing detection of and distinction between hosts that are down and those that are unreachable
*  Contact notifications when service or host problems occur and get resolved (via e-mail, pager, SMS, or any user-defined method through plugin system)
* Ability to define event handlers to be run during service or host events for proactive problem resolution
* Automatic log file rotation
* Support for implementing redundant monitoring hosts
* Optional web-interface for viewing current network status, notifications, problem history, log files, etc.
* Data storage is done in text files rather than database


\section nagios_agents Nagios Agents

\subsection nagios_agents_nrpe NRPE

Nagios Remote Plugin Executor (NRPE) is a Nagios agent that allows remote systems monitoring using scripts that are hosted on the remote systems. It allows for monitoring resources such as disk usage, system load or number of users currently logged in. Nagios periodically polls the agent on the remote system using the check_nrpe plugin.

\subsection nagios_agents_nrdp NRDP

Nagios Remote Data Processor (NDRP) is a Nagios agent with a flexible data transport mechanism and processor. It is designed with an architecture that allows it to be easily extended and customized. NRDP uses standard ports and protocols (HTTP(S) and XML) and can be implemented as a replacement for NSCA.

\subsection nagios_agents_nsclient NSClient++

This program is mainly used to monitor Windows machines. Being installed on a remote system NSClient++ listens to port TCP 1248. Nagios plugin that is used to collect information from this addon is called check_nt. As NRPE, NSClient++ allows to monitor the so called "private services" (memory usage, CPU load, disk usage, running processes, etc.)

\section nagios_alert Alert messages

~~~~
Notification Type: PROBLEM

Service: DSMC
Host: prometheus-web1
Address: 134.95.80.96
State: UNKNOWN

Date/Time: Wed Oct 24 09:27:07 CEST 2012

Additional Info:

NRPE: Unable to read output
~~~~

~~~~
Notification Type: PROBLEM

Service: DSMC
Host: prometheus-srv3
Address: 134.95.80.162
State: CRITICAL

Date/Time: Wed Oct 24 08:58:01 CEST 2012

Additional Info:

DSMC CRITICAL - TSM exited with return code: 12
~~~~

~~~~
Notification Type: PROBLEM

Service: DSMC
Host: prometheus-db1
Address: 134.95.80.95
State: CRITICAL

Date/Time: Wed Oct 24 05:55:00 CEST 2012

Additional Info:

DSMC CRITICAL - /var/lib/mysql (dsmcad.default) older than 72h
/var/local/prometheus (dsmcad.default) older than 72h
/ (dsmcad.default) older than 36h
/var (dsmcad.default) older than 36h
/var/local/prometheus/db (dsmcad.default) older than 36h
~~~~

\section nagios_references References

* [nagios.org](http://www.nagios.org)
* [Nagios documentation](http://www.nagios.org/documentation)
