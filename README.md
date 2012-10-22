# prometheus-sumo


## Introduction

"prometheus-sumo" is a simple (almost) virtual package, to ease the retrieval of
the various components in the software stack for "prometheus - The Distributed
Digital Image Archive for Research and Studies".

prometheus (www.prometheus-bildarchiv.de) is a digital image archive for Art and
Cultural Sciences. prometheus enables the convenient search for images on a
common user interface within different image archives, variable databases from
institutes, research facilities and museums.

For further information visit one of the following websites:

* [prometheus website](http://www.prometheus-bildarchiv.de)
* [pandora website](http://prometheus.uni-koeln.de/pandora)

## External dependencies

External dependencies are kept to a minimum for this package:

| Package | Version   | Website              | Description/Comments        |
|---------|-----------|----------------------|-----------------------------|
| Git     | >= 1.7    | http://git-scm.com   | Version control system      |
| CMake   | >= 2.8.3  | http://www.cmake.org | Cross-platform build system |

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
    |-- data
    |   `-- repositories        ...  Working copies of the various code repositories
    |-- documentation           ...  Extended documentation
    |   |-- examples            ...  Code examples to be included into the documentation
    |   |-- images              ...  Images to be included into the documentation
    |   `-- manual              ...  Reference Manual
    |-- packages                ...  Wrappers for installation of the various packages
    `-- sources                 ...  Source files


## Configuration and build ##

### Getting the source code ###

The source for _prometheus-sumo_ is hosted on Github at;
[go there](https://github.com/lbaehren/prometheus-sumo) to read about the various
options to retrieve a working copy of the code. In the simplest case, were you
need a read-only copy, simply run

    git clone git://github.com/lbaehren/prometheus-sumo.git

in order to to clone into a local working copy.

### Build directory ###

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

Once the configuration run has completed you can obtain a list of available build
targets by typing

   make help


### Configuration options ###

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


## Documentation ##

An extended set of documentation pages can be generated using the [Doxygen](http://www.doxygen.org)
documentation system. If the latter is available on your system, just type

    make Documentation

from within the build directory.


## Testing ##

A [public dashboard](http://my.cdash.org/index.php?project=prometheus-sumo) for _prometheus-sumo_
is hosted on my.cdash.org. [CDash](http://www.cdash.org) is an open-source web-based server
for continuous integration. CDash aggregates, analyzes and displays the results of software
testing processes submitted from clients located around the world. Developers depend on CDash
to convey the state of a software system, and to continually improve its quality.

In order to submit the results of an experimental build, simply run

    make Experimental

This will trigger CTest to configure and build the project, before running the tests defined
therein - the collected results then will be submitted to CDash for visualization and analysis.

## Further reading

* prometheus website <http://www.prometheus-bildarchiv.de>
* pandora website <http://prometheus.uni-koeln.de/pandora>
