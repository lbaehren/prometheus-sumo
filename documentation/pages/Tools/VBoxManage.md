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

\subsection vboxmanage_commands_list List the available VMs (list)

~~~~
VBoxManage list vms
~~~~

\subsection vboxmanage_commands_import Import a VM image (import)

\verbatim
VBoxManage import <ovf/ova> [--dry-run|-n]
\endverbatim

\subsection vboxmanage_commands_startvm Start a VM (startvm)

\verbatim
VBoxManage startvm <uuid>|<name> [--type gui|sdl|headless]
\endverbatim

\subsection vboxmanage_commands_export Export a virtual appliance (export)

The `export` command is simple to use: list the machine (or the machines) that
you would like to export to the same OVF file and specify the target OVF file
after an additional `--output` or `-o` option. Note that the directory of the
target OVF file will also receive the exported disk images in the compressed VMDK
format (regardless of the original format) and should have enough disk space left
for them.

Beside a simple export of a given virtual machine, you can append several product
information to the appliance file. Use `--product`, `--producturl`, `--vendor`,
`--vendorurl` and `--version` to specify this additional information. For legal
reasons you may add a license text or the content of a license file by using the
`--eula` and `--eulafile` option respectively. As with OVF import, you must use
the `--vsys X` option to direct the previously mentioned options to the correct
virtual machine.

\verbatim
VBoxManage export <machines> --output|-o <name>.<ovf/ova>
                            [--legacy09|--ovf09|--ovf10|--ovf20]
                            [--manifest]
                            [--vsys <number of virtual system>]
                            [--product <product name>]
                            [--producturl <product url>]
                            [--vendor <vendor name>]
                            [--vendorurl <vendor url>]
                            [--version <version info>]
                            [--eula <license text>]
                            [--eulafile <filename>]
\endverbatim

\subsection vboxmanage_commands_guestcontrol Control a guest system (guestcontrol)

The "guestcontrol" commands allow you to control certain things inside a guest from the host. Please see the section called “Guest control” for an introduction.

Generally, the syntax is as follows:

\verbatim
VBoxManage guestcontrol <command>
\endverbatim

In order to execute a command/program on the guest system:

\verbatim
VBoxManage guestcontrol   <vmname>|<uuid>
                          exec[ute]
                          --image <path to program>
                          --username <name> --password <password>
                          [--dos2unix]
                          [--environment "<NAME>=<VALUE> [<NAME>=<VALUE>]"]
                          [--timeout <msec>] [--unix2dos] [--verbose]
                          [--wait-exit] [--wait-stdout] [--wait-stderr]
                          [-- [<argument1>] ... [<argumentN>]]
\endverbatim

\section vboxmanage_references References

* [VBoxManage](http://www.virtualbox.org/manual/ch08.html) -- Chapter from VirtualBox manual
* [VirtualBox management commands](http://wiki.inisec.com/index.php/Virtualbox_management_commands)
