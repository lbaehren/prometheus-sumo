
## Include directories

include_directories (
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/libcsv_parser++/include
  )

if (Boost_FOUND)
  ## Boost header files
  include_directories(${Boost_INCLUDE_DIRS})
  ## Compiler flags
  add_definitions(-DWITH_BOOST)
endif (Boost_FOUND)

## ==============================================================================
##
##  Sub-directories
##
## ==============================================================================

add_subdirectory (lib)
add_subdirectory (apps)
add_subdirectory (tests)
