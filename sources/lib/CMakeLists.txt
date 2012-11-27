
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

  add_dependencies (libprometheus yaml-cpp)

  install (
    TARGETS libprometheus
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    )
  
endif (libprometheus_sources)

message (STATUS "Processing directory source/lib - done")
