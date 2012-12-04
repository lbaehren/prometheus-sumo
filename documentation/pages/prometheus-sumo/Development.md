Development    {#sumo_development}
===========

\tableofcontents

\section sumo_development_external External packages

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
