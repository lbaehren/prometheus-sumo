prometheus-sumo    {#prometheus-sumo}
===============

\tableofcontents

[prometheus-sumo](https://github.com/lbaehren/prometheus-sumo) is a simple
(almost) virtual package, to ease the retrieval of the various components in
the software stack for "prometheus - The Distributed Digital Image Archive for
Research and Studies".


\section sumo_dependencies External dependencies

In order to keep configuration and build simple, we try to keep the number of
_mandatory_ external dependencies -- which need to be resolved beforehand -- as
small as possible. Further dependencies - e.g. to support specific functionality
and features -- are resolved as part of the build procedure, automatically
pulling in components which are not available as a system-wide installation.

| Package                           | Version   | Relevance | Notes     |
|-----------------------------------|-----------|-----------|-----------|
| [Git](http://git-scm.com)         | >= 1.7    | mandatory | Distributed revision control system |
| [CMake](http://www.cmake.org)     | >= 2.8.3  | mandatory/provided |           |
| [Doxygen](http://www.doxygen.org) | >  1.7    | optional/provided | Documentation generation  |
| [yaml-cpp](http://code.google.com/p/yaml-cpp) |    | optional/provided | \ref yaml parsing |
| [YAZ](http://www.indexdata.com/yaz) | >= 4.2.30 | optional/provided | \ref yaz developer's toolkit for Z39.50 |
| [Boost](http://www.boost.org)     | >  1.40   | optional  | \ref xml  and logfile parsing |

\section sumo_directories Organization of the source code

Once cloning into a working copy has completed, the following directory structure
can be found:

    .
    ├── CMakeLists.txt          ...  Top-level CMake script for the project
    ├── README.md               ...  Top-level README file
    ├── config
    |   ├── cmake               ...  Collection of CMake scripts and modules
    │   └── rake                ...  Collection of Rake scripts and modules
    ├── data
    │   └── repositories        ...  Working copies of the various code repositories
    ├── documentation           ...  Extended documentation
    |   ├── examples            ...  Code examples to be included into the documentation
    |   ├── images              ...  Images to be included into the documentation
    │   └── pages               ...  Source pages from which the documentation is generated
    ├── packages                ...  Wrappers for installation of the various external packages
    └── sources                 ...  Source files
        ├── apps
        ├── lib
        └── tests

Not included in this picture yet is the `release` directory (containing the standard
set of sub-directories, such as `include`, `lib`, etc.), which is set as the default
\ref sumo_install "installation location".


\section sumo_build Configuration and build

\subsection sumo_build_code Getting the source code

The source for _prometheus-sumo_ is hosted on Github at;
[go there](https://github.com/lbaehren/prometheus-sumo) to read about the various
options to retrieve a working copy of the code. In the simplest case, were you
need a read-only copy, simply run

    git clone git://github.com/lbaehren/prometheus-sumo.git

in order to to clone into a local working copy.

\subsection sumo_build_directory Build directory

The _prometheus-sumo_ uses the [CMake](http://www.cmake.org) Cross-Platform
Makefile Generator for configuration and control of the build.

Once your checkout from the Git repository is complete you will have a directory
structure on disk as described in section "Organization of the source code"
above. In order to now configure and build the project "out of source" - hence
keeping your options open to cleanly remove intermediate/temporary files - create
a separate *build* directory from within to continue:

    mkdir build
    cd build
    cmake ..

\subsection sumo_build_options Configuration options

The behaviour and processing can - to a certain degree - be controlled when
running _CMake_ to configure the project; the list below
shows the available options which can be passed along through the

    -D<Option>=<Value>

syntax from the command line. At the moment the following options are available
(default values in parenthesis):

    ENABLE_TESTING        "Enable CTest test driver?"                     [ YES ]
    CONFIGURE_VERBOSE     "Increase verbosity during configuration?"      [ NO  ]
    GIT_REPOSITORIES_RW   "Check out Github repositories for r/w access?" [ NO  ]
    WITH_PANDORA_DOCS     "Enable documentation of pandora source code?"  [ NO  ]

Besides these options probably the most commonly used command line parameter
passed to CMake in the configuration is the customization of the installation
prefix:

    -DCMAKE_INSTALL_PREFIX=<prefix>


\section sumo_install Installation

In order to allow installation of all components build -- be it pulled in external
packages or project code -- by default header files, libraries, application
executables and configuration data are placed into a `release` directory underneath
the project's root directory.

    .
    └── release                         ...  CMAKE_INSTALL_PREFIX
        ├── bin
        ├── include
        ├── etc
        │   └── prometheus              ...  Configuration data
        ├── lib
        └── share
            └── doc
                └── prometheus          ...  (Extended) Documentation for prometheus
                    ├── html
                    └── xml

In order to simplify running the installed tools/programs, make the `bin`
directory is in your `PATH`:

    export PATH=$PATH:<prefix>/bin

\section sumo_testing Testing

The `ctest` executable is the \ref cmake test driver program. CMake-generated
build trees created for projects that use the `ENABLE_TESTING` and `ADD_TEST`
commands have testing support. This program will run the tests and report
results. If the test driver has been enabled, a number of additional targets
will become visible, most notibly:

    Continuous           ...  Continuous testing whenever changes become available
    Experimental         ...  Test the current version
    Nightly              ...  Nightly build and test at a scheduled time


* [Dashboard](http://my.cdash.org/index.php?project=prometheus-sumo)

\image html Dashboard.png

\section sumo_functionality Functionality

\subsection sumo_functionality_documentation Documentation

An extended set of documentation pages can be generated using the [Doxygen](http://www.doxygen.org)
documentation system. If the latter is available on your system, just type

    make Documentation

from within the build directory.

\subsection sumo_functionality_library C++ library

In order to establish an infrastructure able to life outside the framework of the
\ref pandora web application, some common basic functionality is impemented in
the form of a C++ library.

\include tree_sources.txt

\subsection sumo_functionality_external Dealing with external resources

\subsubsection sumo_functionality_external_packages Installation of external packages

In order to keep track of required external dependencies -- and keeping this
information accessible throughout the code base -- package information is kept
in a collection of \ref yaml files; which of the therein listed packages needs
to be pulled in will depend on the platform (e.g. Debian GNU/Linux, Redhat, OS X)
the software is being build on. In order to simplify this process and provide a
common configuration path, the `promManagePackages` tool (promManagePackages.cc) allows for the installation
and update of these dependencies.

\subsubsection sumo_functionality_repositories Repository working copies

As the various components and sub-packages for the prometheus image archive software
are spread across a number of code repositories \ref prometheus-sumo provides a
mechanism to easily obtain a working copy for all of them:

    make FetchRepositories

\subsubsection sumo_functionality_vm Virtual machine images

Part of the \ref infrastructure to aid in the testing across multiple platforms
is a set of \ref virtual_machines which can be loaded as appliances directly into
[VirtualBox](https://www.virtualbox.org); in order to retrieve the most recent
disk images use the command

    make FetchVirtualMachines

which will download the imags into ``data/vm``


\section sumo_development Development

\subsection sumo_development_external External packages

As shown in the \ref sumo_directories, there exists a collection of CMake-based
wrappers to handle the build and installation of external packages.

~~~~
./packages
  ├── CMakeLists.txt
  └── <project>
      └── CMakeLists.txt
~~~~

* Create a new sub-directory within the `packages` directory
~~~~
cd ./packages
mkdir <package>
~~~~
* Put in place a CMake wrapper script (which can be obtained from a template):
~~~~
cd <package>
cp ../../config/cmake/template_ExternalProject.txt CMakeLists.txt
~~~~
* Adjust the `CMakeLists.txt` file for the package you want to support
~~~~
## Name of the project handled by CMake
project (<PACKAGE>)

## Minimum required version of CMake to configure the project
cmake_minimum_required (VERSION 2.8)

## Enforced CMake policy
cmake_policy (VERSION 2.8)

##  Package information
set (<PACKAGE>_VERSION        "" )
set (<PACKAGE>_SOURCE_ARCHIVE "" )
set (<PACKAGE>_URL            "" )
set (<PACKAGE>_SVN            "" )
~~~~
As can be seen from the excerpt, most of the internal book-keeping is done via
a set of `<PACKAGE>`-variables; replace `<PACKAGE>` by the actual name of the
project and fill in the reminder of the information (such as e.g. download
location). The edited version of the `CMakeLists.txt` file then will look 
something like this:
~~~~
## Name of the project handled by CMake
project (RANT)

## Minimum required version of CMake to configure the project
cmake_minimum_required (VERSION 2.8)

## Enforced CMake policy
cmake_policy (VERSION 2.8)

##  Package information
set (RANT_VERSION        "0.5.8" )
set (RANT_SOURCE_ARCHIVE "rant-${RANT_VERSION}.tar.gz" )
set (RANT_URL            "http://rubyforge.org/frs/download.php/14775/${RANT_SOURCE_ARCHIVE}" )
set (RANT_SVN            "http://rant.rubyforge.org/svn" )
~~~~
