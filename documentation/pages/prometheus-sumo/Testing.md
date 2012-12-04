Testing    {#sumo_testing}
=======

\tableofcontents

The `ctest` executable is the \ref cmake test driver program. CMake-generated
build trees created for projects that use the `ENABLE_TESTING` and `ADD_TEST`
commands have testing support. This program will run the tests and report
results. If the test driver has been enabled, a number of additional targets
will become visible, most notibly:

    Continuous           ...  Continuous testing whenever changes become available
    Experimental         ...  Test the current version
    Nightly              ...  Nightly build and test at a scheduled time

\image html Dashboard.png
