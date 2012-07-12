
message (STATUS "Processing directory source/lib")

file (GLOB prometheus_sources *.cc)

if (prometheus_sources)
  add_library (prometheus ${prometheus_sources})
endif (prometheus_sources)

message (STATUS "Processing directory source/lib - done")

