
Virtual machine images   {#virtual_machines}
======================

\tableofcontents

\section vm_overview Overview

In order to ease testing and/or development on a number of specific common
platforms, a number of virtual machines running inside VirtualBox have been set
up and are being provided to the user:

| Operating system | Machine name  | Comments |
|------------------|---------------|----------|
| Debian GNU/Linux 6.x | vm-debian6 |  |
| Debian GNU/Linux 7.x | vm-debian7 |  |
| Windows XP (IE6) | vm-windowsxp-ie6 | Installers for InDesign & Illustrator |
| Windows XP (IE7) | vm-windowsxp-ie7 | Installers for InDesign & Illustrator |

_Comment:_ For completeness the original machines images for the Windows XP 
variants are being kept.

\section vm_linux Linux

\subsection vm_linux_debian6 Debian GNU/Linux 6.x

  - [Debian “squeeze” Installation Information](http://www.debian.org/releases/squeeze/debian-installer)
  - Installation base: _debian-6.0.5-i386-netinst.iso_
  - Software selection:
    - Graphical Desktop environment
    - Web Server
    - SQL Database
    - SSH Server
    - Standard system utilities
  - Packages installed after setting up the base system:
~~~~
apt-get install build-essential cmake git-svn
~~~~

\subsection vm_linux_debian7 Debian GNU/Linux 7.x

  - [Debian installation information](http://www.debian.org/devel/debian-installer)
  - Software selection:
    - Graphical Desktop environment
    - Web Server
    - SQL Database
    - SSH Server
    - Standard system utilities
  - Packages installed after setting up the base system:
~~~~
apt-get install build-essential cmake git-svn
~~~~

\section vm_windows Windows

\subsection vm_windows_xp-ie6 Windows XP (IE6)

Web browsers:

| Browser | Initial version     | Upgraded to       |
|---------|---------------------|-------------------|
| IE      | 6                   | 6                 |
| Firefox | 3.5.3               | 14.0.1            |
| Opera   | 10.00 (1750)        | 12.01 (1532)      |
| Chrome  | 4.0.0249.78 (36714) | 21.0.1180.79      |
| Safari  | 4.0.3 (531.9.1)     | 5.1.7 (7534.57.2) |


Additionale software packages:

  - Git
  - Adobe Download Manager

Clone of documents directory:

~~~~
git clone lars@134.95.11.139:/Users/lars/Documents/Work/prometheus prom-docs
~~~~

\subsection vm_windows_xp-ie7 Windows XP (IE7)

Initial configuration:

  - IE      : 6
  - Firefox : 3.5.3
  - Opera   : 10.00 (1750)
  - Chrome  : 3.0.195.33
  - Safari  : 4.0.3 (531.9.1)

Browser updates:

  - IE      : 6
  - Firefox : 14.0.1
  - Opera   : 12.01 (1532)
  - Chrome  : 21.0.1180.79
  - Safari  : 5.1.7 (7534.57.2)

Additionale software packages:

  - Git
  - Adobe Download Manager

\section vm_references References 

  - [Git SCM](http://git-scm.com)
  - [Firefox](http://www.mozilla.org/en-US/firefox/new) web browser
  - [Chrome](https://www.google.com/intl/en/chrome/browser) web browser
  - [Opera](http://www.opera.com) web browser

