
include_directories (
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/lib
  ${CMAKE_CURRENT_SOURCE_DIR}/lib/libcsv_parser++/include
  )

## ==============================================================================
##
##  Sub-directories
##
## ==============================================================================

add_subdirectory (lib)

add_subdirectory (tests)

add_subdirectory (xml)
