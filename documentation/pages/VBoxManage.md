VBoxManage    {#vboxmanage}
==========

\tableofcontents

\section vboxmanage_about About

VBoxManage is our command-line interface for automated and very detailed control of every aspect of VirtualBox. With it, you can completely control VirtualBox from the command line of your host operating system. VBoxManage supports all the features that the graphical user interface gives you access to, but it supports a lot more than that. It exposes really all the features of the virtualization engine, even those that cannot (yet) be accessed from the GUI.

You will need to use the command line if you want to

* use a different user interface than the main GUI (for example, VBoxSDL or the VBoxHeadless server);
* control some of the more advanced and experimental configuration settings for a VM.

\section vboxmanage_commands Commands

When running `VBoxManage` without parameters or when supplying an invalid command
line, the below syntax diagram will be shown. Note that the output will be
slightly different depending on the host platform; when in doubt, check the
output of VBoxManage for the commands available on your particular host.

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

\section vboxmanage_references References

* [VBoxManage](http://www.virtualbox.org/manual/ch08.html) -- Chapter from VirtualBox manual