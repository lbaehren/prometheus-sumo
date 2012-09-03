
message (STATUS "Processing directory source/lib")

file (GLOB prometheus_sources *.cc Models/*.cc)

if (prometheus_sources)

  add_library (libprometheus ${prometheus_sources})

  set_target_properties(libprometheus
                        PROPERTIES
                        OUTPUT_NAME prometheus
                        )

endif (prometheus_sources)

message (STATUS "Processing directory source/lib - done")

