
message (STATUS "Processing directory source/lib")

##_______________________________________________________________________________
## Generate configured header file

find_file (CONFIG_SETTINGS_H_IN ConfigSettings.h.in
  PATHS ${CMAKE_CURRENT_SOURCE_DIR}
  PATH_SUFFIXES Config
  )

if (CONFIG_SETTINGS_H_IN)
  configure_file (
    ${CONFIG_SETTINGS_H_IN}
    ${CMAKE_CURRENT_BINARY_DIR}/Config/ConfigSettings.h
    )
endif (CONFIG_SETTINGS_H_IN)

##_______________________________________________________________________________
## Build instructions for the library

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
