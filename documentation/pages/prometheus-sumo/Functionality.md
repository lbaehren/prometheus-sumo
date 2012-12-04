Functionality    {#sumo_functionality}
=============

\tableofcontents

\section sumo_functionality_documentation Documentation

An extended set of documentation pages can be generated using the [Doxygen](http://www.doxygen.org)
documentation system. If the latter is available on your system, just type

    make Documentation

from within the build directory.

\section sumo_functionality_library C++ library

In order to establish an infrastructure able to life outside the framework of the
\ref pandora web application, some common basic functionality is impemented in
the form of a C++ library.

\include tree_sources.txt

\section sumo_functionality_external Dealing with external resources

\subsection sumo_functionality_external_packages Installation of external packages

In order to keep track of required external dependencies -- and keeping this
information accessible throughout the code base -- package information is kept
in a collection of \ref yaml files; which of the therein listed packages needs
to be pulled in will depend on the platform (e.g. Debian GNU/Linux, Redhat, OS X)
the software is being build on. In order to simplify this process and provide a
common configuration path, the `promManagePackages` tool (promManagePackages.cc) allows for the installation
and update of these dependencies.

\subsection sumo_functionality_repositories Repository working copies

As the various components and sub-packages for the prometheus image archive software
are spread across a number of code repositories \ref prometheus-sumo provides a
mechanism to easily obtain a working copy for all of them:

    make FetchRepositories

\subsection sumo_functionality_vm Virtual machine images

Part of the \ref infrastructure to aid in the testing across multiple platforms
is a set of \ref virtual_machines which can be loaded as appliances directly into
[VirtualBox](https://www.virtualbox.org); in order to retrieve the most recent
disk images use the command

    make FetchVirtualMachines

which will download the imags into ``data/vm``


