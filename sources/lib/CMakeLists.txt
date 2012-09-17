
message (STATUS "Processing directory source/lib")

set (prometheus_sources
  Account.cc
  Institution.cc
  Presentation.cc
  Collection.cc
  SourceDump.cc
  Image.cc
  StatisticsHBZ.cc
  StatisticsReader.cc
  StatisticsReaderHBZ.cc
  ## Sources
  Sources/TheolEik.cc
  Sources/Robertinum.cc
  Sources/Beeskow.cc
  Sources/Kassel.cc
)

add_library (libprometheus ${prometheus_sources})

set_target_properties(libprometheus
                      PROPERTIES
                      OUTPUT_NAME prometheus
                      )

message (STATUS "Processing directory source/lib - done")

