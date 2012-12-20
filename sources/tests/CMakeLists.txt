
message (STATUS "Processing directory source/tests")

## ==============================================================================
##
##  Generic C++ test programs
##
## ==============================================================================

foreach (test_cpp
  testCommon
  testImage
  )
  ## Compiler instructions
  add_executable (${test_cpp} ${test_cpp}.cc)
  ## Linker instructions
  target_link_libraries (${test_cpp} libprometheus)
  ## Testing
  add_test (${test_cpp} ${test_cpp})
endforeach (test_cpp)

## ==============================================================================
##
##  XML test programs
##
## ==============================================================================

##__________________________________________________________
## Parsing via Boost library

if (Boost_FOUND)

  ## Header files
  include_directories(${Boost_INCLUDE_DIRS})

  foreach (test_with_boost
      testApacheLogs.cc
      )
    ## remove file extension
    get_filename_component (varFilename ${test_with_boost} NAME_WE)
    ## compiler instructions
    add_executable (${varFilename} ${test_with_boost})
    ## linker instructions
    target_link_libraries (${varFilename} libprometheus ${Boost_LIBRARIES})
  endforeach (test_with_boost)

  if (apache_access_log)
    add_test (testApacheLogs testApacheLogs ${apache_access_log})
  endif (apache_access_log)

endif (Boost_FOUND)

## ==============================================================================
##
##  Project sub-directories
##
## ==============================================================================

add_subdirectory (3rdparty)
add_subdirectory (Config)
add_subdirectory (Sources)

message (STATUS "Processing directory source/tests - done")
