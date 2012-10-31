
Virtual machine images   {#virtual_machines}
======================

\tableofcontents

\section vm_overview Overview

In order to ease testing and/or development on a number of specific common
platforms, a number of virtual machines running inside VirtualBox have been set
up and are being provided to the user:

| Operating system | Machine name  | Comments |
|------------------|---------------|----------|
| Debian GNU/Linux 6.x | [vm-debian6](http://134.95.11.135/virtualbox/vm-debian6.ova) |  |
| Debian GNU/Linux 7.x | [vm-debian7](http://134.95.11.135/virtualbox/vm-debian7.ova) |  |
| Ubuntu 10.04 LTS     | [vm-ubuntu1004.ova](http://134.95.11.135/virtualbox/vm-ubuntu1004.ova) |  |
| Ubuntu 12.04 LTS     | [vm-ubuntu1204.ova](http://134.95.11.135/virtualbox/vm-ubuntu1204.ova) |  |
| Windows XP (IE6) | [vm-windowsxp-ie6](http://134.95.11.135/virtualbox/vm-windowsxp-ie6.ova) | Installers for InDesign & Illustrator |
| Windows XP (IE7) | [vm-windowsxp-ie7](http://134.95.11.135/virtualbox/vm-windowsxp-ie7.ova) | Installers for InDesign & Illustrator |
| Windows XP (IE8) | [vm-windowsxp-ie8](http://134.95.11.135/virtualbox/vm-windowsxp-ie8.ova) | in preparation |

__Note:__ You can [use prometheus-sumo](\ref sumo_functionality_vm) to retrieve all of the virtual machine disk images.

\section vm_images Available virtual machine images

\subsection vm_linux Linux

\subsubsection vm_linux_debian6 Debian GNU/Linux 6.x

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
apt-get install build-essential cmake git-svn subversion doxygen mysql-server ruby1.8-dev
~~~~
  - MySQL server Root password: mysqlR00t

\subsubsection vm_linux_debian7 Debian GNU/Linux 7.x

  - [Debian installation information](http://www.debian.org/devel/debian-installer)
  - Installation base: _debian-wheezy-DI-b1-i386-netinst.iso_
  - Software selection:
    - Debian desktop environment
    - Web Server
    - SQL database
    - SSH Server
    - Standard system utilities
  - Packages installed after setting up the base system:
~~~~
apt-get install build-essential cmake git-svn subversion doxygen mysql-server ruby1.8-dev
~~~~
  - MySQL server Root password: mysqlR00t

\subsubsection vm_linux_ubuntu_1004 Ubuntu 10.04 LTS (Lucid Lynx)

  - Installation base: _ubuntu-10.04.4-desktop-i386.iso_
  - Packages installed after setting up the base system:
~~~~
apt-get install build-essential cmake git-svn subversion doxygen mysql-server ruby1.8-dev
~~~~
  - MySQL server Root password: mysqlR00t

\subsubsection vm_linux_ubuntu_1204 Ubuntu 12.04 LTS (Precise Pangolin)

  - Installation base : _ubuntu-12.04-desktop-i386.iso_
  - Packages installed after setting up the base system:
~~~~
apt-get install build-essential cmake git-svn subversion doxygen mysql-server ruby1.8-dev
~~~~
  - MySQL server Root password: mysqlR00t

\subsection vm_windows Windows

\subsubsection vm_windows_xp-ie6 Windows XP (IE6)

\ref browser "Web browsers":

| Browser | Initial version     | Upgraded to       |
|---------|---------------------|-------------------|
| IE      | 6                   | 6                 |
| Firefox | 3.5.3               | 14.0.1            |
| Opera   | 10.00 (1750)        | 12.01 (1532)      |
| Chrome  | 4.0.0249.78 (36714) | 21.0.1180.79      |
| Safari  | 4.0.3 (531.9.1)     | 5.1.7 (7534.57.2) |

Additionale software packages:

  - Adobe Download Manager
  - [Git](http://www.git-scm.com)
  - MinGW
    - MinGW Compier Suite (C, C++)
    - MSYS Basic System

\subsubsection vm_windows_xp-ie7 Windows XP (IE7)

\ref browser "Web browsers":

| Browser | Initial version     | Upgraded to       |
|---------|---------------------|-------------------|
| IE      | 7                   | 7                 |
| Firefox | 3.5.3               | 14.0.1            |
| Opera   | 10.00 (1750)        | 12.01 (1532)      |
| Chrome  | 3.0.195.33          | 21.0.1180.79      |
| Safari  | 4.0.3 (531.9.1)     | 5.1.7 (7534.57.2) |

Additional software packages:

  - Adobe Download Manager
  - Git
  - MinGW
    - MinGW Compier Suite (C, C++)
    - MSYS Basic System

\subsubsection vm_windows_xp-ie8 Windows XP (IE8)

\ref browser "Web browsers":

| Browser | Initial version     | Upgraded to       |
|---------|---------------------|-------------------|
| IE      | 8                   | 8                 |
| Firefox | 3.5.30729           | 15.0              |
| Opera   | 10.00 (1750)        | 12.02 (1578)      |
| Chrome  | 4.0.249.78 (36714)  | 21.0.1180.89      |
| Safari  | 4.0.3 (531.9.1)     | 5.1.7 (7534.57.2) |

Additional software packages:

  - Git
  - Adobe Download Manager

\section vm_manage Scripting VirtualBox with VBoxManage

* List the available VMs:
~~~~
VBoxManage list vms
~~~~

* Import VM image
~~~~
VBoxManage import <ovf/ova> [--dry-run|-n]
~~~~

* Start a VM
~~~~
VBoxManage startvm <uuid>|<name> [--type gui|sdl|headless]
~~~~

\section vm_references References

  - [VirtualBox](http://www.virtualbox.org)
  - [7-Zip](http://www.7-zip.org) is a file archiver with a high compression ratio.
  - [Debian GNU/Linux](http://www.debian.org) - a free operating system (OS) for your computer.
  - [Cygwin](http://cygwin.com) - a collection of tools which provide a Linux look and feel environment for Windows.
  - [MinGW](http://www.mingw.org) -Minimalist GNU for Windows
  - [Git SCM](http://git-scm.com) - a free and open source distributed version control system
  - [Firefox](http://www.mozilla.org/en-US/firefox/new) web browser
  - [Chrome](https://www.google.com/intl/en/chrome/browser) web browser
  - [Opera](http://www.opera.com) web browser
