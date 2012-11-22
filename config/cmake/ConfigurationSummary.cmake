
## ==============================================================================
##
##  Configuration summary
##
## ==============================================================================

message (STATUS "------------------------------------------------------------"   )
message (STATUS "[prometheus-sumo] Configuration summary."                       )
message (STATUS "------------------------------------------------------------ "  )

message (STATUS " System configuration:"                                         )
message (STATUS " .. Processor type .............. = ${CMAKE_SYSTEM_PROCESSOR}"  )
message (STATUS " .. CMake executable ............ = ${CMAKE_COMMAND}"           )
message (STATUS " .. CMake version ............... = ${CMAKE_VERSION}"           )
message (STATUS " .. System name ................. = ${CMAKE_SYSTEM}"            )
message (STATUS " .. Operating system name ....... = ${CMAKE_OS_NAME}"           )
message (STATUS " .. C++ compiler ................ = ${CMAKE_CXX_COMPILER}"      )
message (STATUS " .. C compiler .................. = ${CMAKE_C_COMPILER}"        )
message (STATUS " .. size(void*) ................. = ${CMAKE_SIZEOF_VOID_P}"     )

message (STATUS " Project configuration:"                                        )
message (STATUS " .. Version number .............. = ${PROJECT_VERSION}"         )
message (STATUS " .. Installation prefix ......... = ${CMAKE_INSTALL_PREFIX}"    )
message (STATUS " .. Git repository base URL ..... = ${GIT_REPOSITORY_BASE}"     )
message (STATUS " .. Clone Github repositories r/w = ${GIT_REPOSITORIES_RW}"     )
message (STATUS " .. Enable CTest test driver? ... = ${ENABLE_TESTING}"          )
message (STATUS " .. Verbose configure? .......... = ${CONFIGURE_VERBOSE}"       )
message (STATUS " .. pandora database dumps ...... = ${PANDORA_DATA_DIR}"        )

message (STATUS " Ruby configuration:"                                           )
message (STATUS " .. Required version ............ = ${REQUIRED_VERSION_RUBY}"   )
message (STATUS " .. Ruby executable ............. = ${RUBY_EXECUTABLE} (${RUBY_VERSION})" )
message (STATUS " .. Path to Ruby library ........ = ${RUBY_LIBRARY}"            )
message (STATUS " .. Include directory ........... = ${RUBY_INCLUDE_DIRS}"       )
message (STATUS " .. Gem executable .............. = ${GEM_FOUND} (${GEM_VERSION})" )
message (STATUS " .. Rails executable ............ = ${RAILS_FOUND} (${RAILS_VERSION})" )
message (STATUS " .. Rake executable ............. = ${RAKE_FOUND} (${RAKE_VERSION})" )
message (STATUS " .. Rant executable ............. = ${RANT_FOUND} (${RANT_VERSION})" )
message (STATUS " .. RDoc ........................ = ${RDOC_FOUND} (${RDOC_VERSION})"            )
message (STATUS " .. YARD executable ............. = ${YARD_FOUND} (${YARD_VERSION})" )

message (STATUS " Processing tools & libraries:"                                 )
message (STATUS " .. Boost ....................... = ${Boost_FOUND}"             )
message (STATUS " .. Doxygen ..................... = ${DOXYGEN_FOUND} (${DOXYGEN_VERSION})" )
message (STATUS " .. ImageMagick ................. = ${ImageMagick_FOUND} (${ImageMagick_VERSION_STRING})" )
message (STATUS " .. KWSys ....................... = ${KWSYS_FOUND}"             )
message (STATUS " .. Magic ....................... = ${MAGIC_FOUND}"             )
message (STATUS " .. MySQL ....................... = ${MYSQL_FOUND}"             )
message (STATUS " .. TinyXML ..................... = ${TINYXML_FOUND}"           )
message (STATUS " .. VirtualBox .................. = ${VIRTUALBOX_FOUND}"        )
message (STATUS " .. Yaml ........................ = ${YAML_FOUND}"              )
message (STATUS " .. YAZ ......................... = ${YAZ_FOUND} (${YAZ_VERSION})"     )
message (STATUS " .. YAZ++ ....................... = ${YAZPP_FOUND} (${YAZPP_VERSION})" )

message (STATUS "------------------------------------------------------------ "  )
