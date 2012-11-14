CMake    {#cmake}
=====

\tableofcontents

\section cmake_intro Introduction

CMake is an extensible, open-source system that manages the build process in an
operating system and compiler independent manner. Unlike many cross-platform
systems, CMake is designed to be used in conjunction with the native build
environment. Simple configuration files placed in each source directory (called
`CMakeLists.txt` files) are used to generate standard build files (e.g.,
`makefiles` on Unix and projects/workspaces in Windows MSVC) which are used in
the usual way. CMake can compile source code, create libraries, generate
wrappers, and build executables in arbitrary combinations. CMake supports
in-place and out-of-place builds, and can therefore support multiple builds from
a single source tree. CMake also supports static and dynamic library builds.
Another nice feature of CMake is that it generates a cache file that is designed
to be used with a graphical editor. For example, when CMake runs, it locates
include files, libraries, and executable, and may encounter optional build
directives. This information is gathered into the cache, which may be changed
by the user prior to the generation of the native build files.

CMake is designed to support complex directory hierarchies and applications dependent on several libraries. For example, CMake supports projects consisting of multiple toolkits (i.e., libraries), where each toolkit might contain several directories, and the application depends on the toolkits plus additional code. CMake can also handle situations where executables must be built in order to generate code that is then compiled and linked into a final application. Because CMake is open source, and has a simple, extensible design, CMake can be extended as necessary to support new features.

Using CMake is simple. The build process is controlled by creating one or more
`CMakeLists.txt` files in each directory (including subdirectories) that make up
a project. Each `CMakeLists.txt` consists of one or more commands. Each command
has the form `COMMAND (args…)` where `COMMAND` is the name of the command, and args is a white-space separated list of arguments. CMake provides many pre-defined commands, but if you need to, you can add your own commands. In addition, the advanced user can add other makefile generators for a particular compiler/OS combination. (While Unix and MSVC++ is supported currently, other developers are adding other compiler/OS support.) You may wish to study the examples page to see more details.

\section cmake_external Building External Projects

The `ExternalProject` module in CMake 2.8 makes it easier to build projects
dependent upon external software components. An "external project" is one that
you can get the source code for, but does not readily build with a simple
`ADD_SUBDIRECTORY` call in your `CMakeLists.txt` file. The `ExternalProject_Add`
function makes it possible to say "download this project from the internet, run
its configure step, build it and install it" with just a few lines of code added
to your `CMakeLists.txt` file. The time intensive processing for each step is
deferred until build time, making the CMake configuration of an
`ExternalProject_Add` lightning fast.

The basic concept of ExternalProject is simple: given an external source of
software (url to a .tar.gz file, cvs repository, svn repository, local directory),
execute the sequence of commands necessary to build and install that software so
that you can refer to it (include, link, run) from your project.

\code
    ExternalProject_Add (doxygen
      PREFIX ${PROJECT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      SVN_REPOSITORY ${DOXYGEN_SVN}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ${PROJECT_BINARY_DIR}/source/configure --prefix ${CMAKE_INSTALL_PREFIX}
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )
\endcode

\section cmake_references References

* [cmake.org](http:/www.cmake.org)
* [Building External Projects with CMake 2.8](http://www.kitware.com/media/html/BuildingExternalProjectsWithCMake2.8.html)
