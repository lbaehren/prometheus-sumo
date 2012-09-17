
message (STATUS "Processing directory source/lib")

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
  ## Sources
  Sources/TheolEik.cc
  Sources/Robertinum.cc
  Sources/Beeskow.cc
  Sources/Kassel.cc
  )

set_target_properties(libprometheus
                      PROPERTIES
                      OUTPUT_NAME prometheus
                      )

message (STATUS "Processing directory source/lib - done")
