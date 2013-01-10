
message (STATUS "Processing directory source/lib")

##_______________________________________________________________________________
## Generate configured header file

configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/Config/ConfigSettings.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/Config/ConfigSettings.h
  )

##_______________________________________________________________________________
## Build instructions for the library

file (GLOB libprometheus_sources *.cc */*.cc)

if (libprometheus_sources)

  add_library (libprometheus ${libprometheus_sources})

  target_link_libraries (libprometheus ${libprometheus_link_libraries})

  set_target_properties(libprometheus
    PROPERTIES
    OUTPUT_NAME prometheus
    )

  add_dependencies (libprometheus yaml-cpp kwsys)

  install (
    TARGETS libprometheus
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    )

endif (libprometheus_sources)

##_______________________________________________________________________________
## Wrapper for the library

if (SWIG_FOUND AND libprometheus_sources)

  include (${SWIG_USE_FILE})

  set (CMAKE_SWIG_FLAGS "")

  SET_SOURCE_FILES_PROPERTIES (bindings.i PROPERTIES CPLUSPLUS ON)
  SET_SOURCE_FILES_PROPERTIES (bindings.i PROPERTIES SWIG_FLAGS "-includeall")
#  SWIG_ADD_MODULE (bindings ruby bindings.i bindings_wrap.c)

endif (SWIG_FOUND AND libprometheus_sources)

message (STATUS "Processing directory source/lib - done")
