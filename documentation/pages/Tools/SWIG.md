SWIG    {#swig}
====

\tableofcontents

\section swig_overview Overview

SWIG is a software development tool that simplifies the task of interfacing different languages to C and C++ programs. In a nutshell, SWIG is a compiler that takes C declarations and creates the wrappers needed to access those declarations from other languages including including Perl, Python, Tcl, Ruby, Guile, and Java. SWIG normally requires no modifications to existing code and can often be used to build a usable interface in only a few minutes. Possible applications of SWIG include:

  * Building interpreted interfaces to existing C programs.
  * Rapid prototyping and application development.
  * Interactive debugging.
  * Reengineering or refactoring of legacy software into a scripting language components.
  * Making a graphical user interface (using Tk for example).
  * Testing of C libraries and programs (using scripts).
  * Building high performance C modules for scripting languages.
  * Making C programming more enjoyable (or tolerable depending on your point of view).
  * Impressing your friends.
  * Obtaining vast sums of research funding (although obviously not applicable to the author). 

SWIG was originally designed to make it extremely easy for scientists and engineers to build extensible scientific software without having to get a degree in software engineering. Because of this, the use of SWIG tends to be somewhat informal and ad-hoc (e.g., SWIG does not require users to provide formal interface specifications as you would find in a dedicated IDL compiler). Although this style of development isn't appropriate for every project, it is particularly well suited to software development in the small; especially the research and development work that is commonly found in scientific and engineering projects.

\section swig_build Incorporating SWIG into a build system

SWIG is a command line tool and as such can be incorporated into any build system that supports invoking external tools/compilers. SWIG is most commonly invoked from within a Makefile, but is also known to be invoked from from popular IDEs such as Microsoft Visual Studio.

If you are using the GNU Autotools (Autoconf/ Automake/ Libtool) to configure SWIG use in your project, the SWIG Autoconf macros can be used. The primary macro is `ac_pkg_swig`, see [www.gnu.org](http://www.gnu.org/software/autoconf-archive/ax_pkg_swig.html). The `ac_python_devel` macro is also helpful for generating Python extensions. See the Autoconf Macro Archive for further information on this and other Autoconf macros.

There is growing support for SWIG in some build tools, for example \ref cmake is a cross-platform, open-source build manager with built in support for SWIG. CMake can detect the SWIG executable and many of the target language libraries for linking against. CMake knows how to build shared libraries and loadable modules on many different operating systems. This allows easy cross platform SWIG development. It also can generate the custom commands necessary for driving SWIG from IDE's and makefiles. All of this can be done from a single cross platform input file. The following example is a CMake input file for creating a python wrapper for the SWIG interface file, example.i:

\code
# This is a CMake example for Python

FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

FIND_PACKAGE(PythonLibs)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

SET(CMAKE_SWIG_FLAGS "")

SET_SOURCE_FILES_PROPERTIES(example.i PROPERTIES CPLUSPLUS ON)
SET_SOURCE_FILES_PROPERTIES(example.i PROPERTIES SWIG_FLAGS "-includeall")
SWIG_ADD_MODULE(example python example.i example.cxx)
SWIG_LINK_LIBRARIES(example ${PYTHON_LIBRARIES})
\endcode

The above example will generate native build files such as makefiles, nmake files and Visual Studio projects which will invoke SWIG and compile the generated C++ files into _example.so (UNIX) or _example.pyd (Windows). For other target languages on Windows a dll, instead of a .pyd file, is usually generated.

\section swig_cpp SWIG and C++

\subsection swig_cpp_comments Comments on C++ Wrapping

Because of its complexity and the fact that C++ can be difficult to integrate with itself let alone other languages, SWIG only provides support for a subset of C++ features. Fortunately, this is now a rather large subset.

In part, the problem with C++ wrapping is that there is no semantically obvious (or automatic ) way to map many of its advanced features into other languages. As a simple example, consider the problem of wrapping C++ multiple inheritance to a target language with no such support. Similarly, the use of overloaded operators and overloaded functions can be problematic when no such capability exists in a target language.

A more subtle issue with C++ has to do with the way that some C++ programmers think about programming libraries. In the world of SWIG, you are really trying to create binary-level software components for use in other languages. In order for this to work, a "component" has to contain real executable instructions and there has to be some kind of binary linking mechanism for accessing its functionality. In contrast, C++ has increasingly relied upon generic programming and templates for much of its functionality. Although templates are a powerful feature, they are largely orthogonal to the whole notion of binary components and libraries. For example, an STL vector does not define any kind of binary object for which SWIG can just create a wrapper. To further complicate matters, these libraries often utilize a lot of behind the scenes magic in which the semantics of seemingly basic operations (e.g., pointer dereferencing, procedure call, etc.) can be changed in dramatic and sometimes non-obvious ways. Although this "magic" may present few problems in a C++-only universe, it greatly complicates the problem of crossing language boundaries and provides many opportunities to shoot yourself in the foot. You will just have to be careful.

\subsection swig_cpp_approach Approach

To wrap C++, SWIG uses a layered approach to code generation. At the lowest level, SWIG generates a collection of procedural ANSI-C style wrappers. These wrappers take care of basic type conversion, type checking, error handling, and other low-level details of the C++ binding. These wrappers are also sufficient to bind C++ into any target language that supports built-in procedures. In some sense, you might view this layer of wrapping as providing a C library interface to C++. On top of the low-level procedural (flattened) interface, SWIG generates proxy classes that provide a natural object-oriented (OO) interface to the underlying code. The proxy classes are typically written in the target language itself. For instance, in Python, a real Python class is used to provide a wrapper around the underlying C++ object.

It is important to emphasize that SWIG takes a deliberately conservative and non-intrusive approach to C++ wrapping. SWIG does not encapsulate C++ classes inside a special C++ adaptor, it does not rely upon templates, nor does it add in additional C++ inheritance when generating wrappers. The last thing that most C++ programs need is even more compiler magic. Therefore, SWIG tries to maintain a very strict and clean separation between the implementation of your C++ application and the resulting wrapper code. You might say that SWIG has been written to follow the principle of least surprise--it does not play sneaky tricks with the C++ type system, it doesn't mess with your class hierarchies, and it doesn't introduce new semantics. Although this approach might not provide the most seamless integration with C++, it is safe, simple, portable, and debuggable.

Some of this chapter focuses on the low-level procedural interface to C++ that is used as the foundation for all language modules. Keep in mind that the target languages also provide the high-level OO interface via proxy classes. More detailed coverage can be found in the documentation for each target language.

\section swig_ruby SWIG and Ruby

\subsection swig_ruby_preliminaries Preliminaries

SWIG 1.3 is known to work with Ruby versions 1.6 and later. Given the choice, you should use the latest stable version of Ruby. You should also determine if your system supports shared libraries and dynamic loading. SWIG will work with or without dynamic loading, but the compilation process will vary. 

To build a Ruby module, run SWIG using the -ruby option:

\verbatim
$ swig -ruby example.i
\endverbatim

If building a C++ extension, add the -c++ option:

\verbatim
$ swig -c++ -ruby example.i
\endverbatim

This creates a file `example_wrap.c` (`example_wrap.cxx` if compiling a C++ extension) that contains all of the code needed to build a Ruby extension module. To finish building the module, you need to compile this file and link it with the rest of your program.
 
\section swig_references References

* [Simplified Wrapper and Interface Generator](http://www.swig.org) (SWIG)
* [SWIG Basics](http://www.swig.org/Doc2.0/SWIG.html)
* [SWIG and C++](http://www.swig.org/Doc2.0/SWIGPlus.html)
* [SWIG and Ruby](http://www.swig.org/Doc2.0/Ruby.html)
* [Include existing C/C++ libraries in Ruby](http://www.ruby-forum.com/topic/75976) (Ruby Forum)