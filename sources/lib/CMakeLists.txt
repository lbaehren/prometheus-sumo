
message (STATUS "Processing directory source/lib")

file (GLOB libprometheus_sources Sources/*)

add_library (libprometheus
  Account.cc
  Institution.cc
  Presentation.cc
  Collection.cc
  SourceDump.cc
  Image.cc
  StatisticsHBZ.cc
  StatisticsReader.cc
  StatisticsReaderHBZ.cc
  ${libprometheus_sources}
  )

set_target_properties(libprometheus
                      PROPERTIES
                      OUTPUT_NAME prometheus
                      )

message (STATUS "Processing directory source/lib - done")
