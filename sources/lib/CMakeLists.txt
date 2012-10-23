
message (STATUS "Processing directory source/lib")

file (GLOB libprometheus_sources *.cc Config/* Sources/* Statistics/*)

if (libprometheus_sources)

  add_library (libprometheus ${libprometheus_sources})

  target_link_libraries (libprometheus ${libprometheus_link_libraries})

  set_target_properties(libprometheus
    PROPERTIES
    OUTPUT_NAME prometheus
    )

endif (libprometheus_sources)

message (STATUS "Processing directory source/lib - done")
