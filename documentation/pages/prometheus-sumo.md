prometheus-sumo    {#prometheus-sumo}
===============

\tableofcontents


\section sumo_about About

[prometheus-sumo](https://github.com/lbaehren/prometheus-sumo) is a simple
(almost) virtual package, to ease the retrieval of the various components in
the software stack for "prometheus - The Distributed Digital Image Archive for
Research and Studies".


\section sumo_dependencies External dependencies

External dependencies are kept to a minimum for this package:

| Package | Version   | Website              |
|---------|-----------|----------------------|
| Git     | >= 1.7    | http://git-scm.com   |
| CMake   | >= 2.8.3  | http://www.cmake.org |

Further dependencies, as required when developing the prometheus software
packages, are handled as part of this tool.


\section sumo_organiation Organization of the source code

Once cloning into a working copy has completed, the following directory structure
can be found:

~~~~
  .
  |- CMakeLists.txt          ...  Top-level CMake script for the project
  |- README.md               ...  README file
  |- config
  |   |- cmake               ...  Collection of CMake scripts and modules
  |   `- rake                ...  Collection of Rake scripts and modules
  |- data
  |   |- repositories        ...  Working copies of the various code repositories
  |   `- vm                  ...  Virtual machine images
  |- documentation           ...  Extended documentation
  |   |- examples            ...  Code examples to be included into the documentation
  |   |- images              ...  Images to be included into the documentation
  |   `- manual              ...  Reference Manual
  |- packages                ...  Wrappers for installation of the various packages
  `- sources                 ...  Source files
~~~~

\section sumo_build Configuration and build

\subsection sumo_build_code Getting the source code

The source for _prometheus-sumo_ is hosted on Github at;
[go there](https://github.com/lbaehren/prometheus-sumo) to read about the various
options to retrieve a working copy of the code. In the simplest case, were you
need a read-only copy, simply run

~~~~
git clone git://github.com/lbaehren/prometheus-sumo.git
~~~~

in order to to clone into a local working copy.

\subsection sumo_build_directory Build directory

The _prometheus-sumo_ uses the [CMake](http://www.cmake.org) Cross-Platform
Makefile Generator for configuration and control of the build.

Once your checkout from the Git repository is complete you will have a directory
structure on disk as described in section "Organization of the source code"
above. In order to now configure and build the project "out of source" - hence
keeping your options open to cleanly remove intermediate/temporary files - create
a separate *build* directory from within to continue:

~~~~
mkdir build
cd build
cmake ..
~~~~

\subsection sumo_build_options Configuration options

The behaviour and processing can - to a certain degree - be controlled when
running _CMake_ to configure the project; the list below
shows the available options which can be passed along through the

~~~~
-D<Option>=<Value>
~~~~

syntax from the command line. At the moment the following options are available
(default values in parenthesis):

    ENABLE_TESTING        "Enable CTest test driver?"                     [ YES ]
    CONFIGURE_VERBOSE     "Increase verbosity during configuration?"      [ NO  ]
    GIT_REPOSITORIES_RW   "Check out Github repositories for r/w access?" [ NO  ]
    WITH_PANDORA_DOCS     "Enable documentation of pandora source code?"  [ NO  ]

Besides these options probably the most commonly used command line parameter
passed to CMake in the configuration is the customization of the installation
prefix:

~~~~
-DCMAKE_INSTALL_PREFIX=<prefix>
~~~~

\section sumo_functionality Functionality

\subsection sumo_functionality_repositories Fetching repository working copies

As the various components and sub-packages for the prometheus image archive software
are spread across a number of code repositories \ref prometheus-sumo provides a
mechanism to easily obtain a working copy for all of them:

~~~~
make FetchRepositories
~~~~

\subsection sumo_functionality_vm Fetching virtual machine images

Part of the \ref infrastructure to aid in the testing across multiple platforms
is a set of \ref virtual_machines which can be loaded as appliances directly into
[VirtualBox](https://www.virtualbox.org); in order to retrieve the most recent
disk images use the command

~~~~
make FetchVirtualMachines
~~~~

which will download the imags into ``data/vm``

\subsection sumo_functionality_documentation Documentation

Besides the basic documentation of the source code extended documentation on
\ref infrastructure, \ref software_packages, etc. can be generated both in HTML
format (probably what you are reading right now) and as LaTeX/PDF.

~~~~
make Documentation
~~~~

\subsection sumo_functionality_external Installation of external packages

As the prometheus digital image archive software depends on a number of external
\ref software_packages - libraries and tools - a path is required to resolve
the resulting dependencies; some of these can be taken care of by the system's
package manager (e.g. \c apt-get on [Debian](http://www.debian.org) and
[Ubuntu](http://www.ubuntu.com) or \c yum on [Fedora](http://www.fedoraproject.org))
-- however depending on the platform the proper list of packages needs to be
provided. In order to simplify this process \ref prometheus-sumo provides build
targets to handle the resolution of external dependencies.

\li Installation of system packages:
~~~~
make InstallPackages
~~~~

\li Installation of Ruby Gems:
~~~~
make InstallGems
~~~~

