# prometheus-sumo


## Introduction

"prometheus-sumo" is a simple (almost) virtual package, to ease the retrieval of
the various components in the software stack for "prometheus – The Distributed
Digital Image Archive for Research and Studies".

prometheus (www.prometheus-bildarchiv.de) is a digital image archive for Art and
Cultural Sciences. prometheus enables the convenient search for images on a
common user interface within different image archives, variable databases from
institutes, research facilities and museums.


## External dependencies

External dependencies are kept to a minimum for this package:

| Package | Version | Website              |
|---------|---------|----------------------|
| Git     | >= 1.7  | http://git-scm.com   |
| CMake   | >= 2.8  | http://www.cmake.org |

Further dependencies, as required when developing the prometheus software
packages, are handled as part of this tool.


## Organization of the source code

Once cloning into a working copy has completed, the following directory structure
can be found:

    .
    |-- CMakeLists.txt          ...  Top-level CMake script for the project
    |-- README                  ...  This README file
    |-- config
    |   |-- cmake               ...  Collection of CMake scripts and modules
    |   `-- rake                ...  Collection of Rake scripts and modules
    |-- documentation           ...  Extended documentation
    |   |-- examples            ...  Code examples to be included into the documentation
    |   |-- images              ...  Images to be included into the documentation
    |   `-- manual              ...  Reference Manual
    |-- packages                ...  Wrappers for installation of the various packages
    `-- sources                 ...  Source files

## Configuration and build

### Getting the source code

The source for _prometheus-sumo_ is hosted on Github at;
[go there](https://github.com/lbaehren/prometheus-sumo) to read about the various
options to retrieve a working copy of the code. In the simplest case, were you
need a read-only copy, simply run

    git clone git://github.com/lbaehren/prometheus-sumo.git

in order to to clone into a local working copy.

### Build directory

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

### Configuration options

The behaviour and processing can - to a certain degree - be controlled when
running _CMake_ to configure the project; the list below
shows the available options which can be passed along through the

    -D<Option>=<Value>

syntax from the command line. At the moment the following options are available
(default values in parenthesis):

    TESTING_ENABLE        "Enable CTest test driver?"                     [ YES ]
    CONFIGURE_VERBOSE     "Increase verbosity during configuration?"      [ NO  ]
    GIT_REPOSITORIES_RW   "Check out Github repositories for r/w access?" [ NO  ]
    PANDORA_GENERATE_DOCS "Enable documentation of pandora source code?"  [ YES ]

## Further reading

* prometheus website <http://www.prometheus-bildarchiv.de>
* pandora website <http://prometheus.uni-koeln.de/pandora>
