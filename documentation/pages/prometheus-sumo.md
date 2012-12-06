prometheus-sumo    {#prometheus-sumo}
===============

\tableofcontents

[prometheus-sumo](https://github.com/lbaehren/prometheus-sumo) is a simple
(almost) virtual package, to ease the retrieval of the various components in
the software stack for "prometheus - The Distributed Digital Image Archive for
Research and Studies".

**Local pages** | \subpage sumo_functionality | \subpage sumo_development | \subpage sumo_testing |

**External pages** | [Github](https://github.com/lbaehren/prometheus-sumo) | [Dashboard](http://my.cdash.org/index.php?project=prometheus-sumo)

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

    ENABLE_TESTING       "Enable CTest test driver?"                        [YES]
    CONFIGURE_VERBOSE    "Increase verbosity during configuration?"         [NO ]
    GIT_REPOSITORIES_RW  "Check out Github repositories for r/w access?"    [NO ]
    WITH_DOXYGEN         "Build Doxygen documention generator?"             [NO ]
    WITH_PACKAGE_CLAMAV  "Build ClamAV antivirus software tool-kit?"        [NO ]
    WITH_PACKAGE_SPHINX  "Build Sphinx search server?"                      [NO ]
    WITH_PACKAGE_YAZ     "Build YAZ programmers' toolkit?"                  [NO ]
    WITH_PANDORA_DOCS    "Enable documentation of pandora source code?"     [NO ]
    WITH_LATEX_DOC       "Enable generation of LaTeX output from Doxygen?"  [NO ]

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

