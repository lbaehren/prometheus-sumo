
if (YARD_EXECUTABLE)

  ##_____________________________________________________________________________
  ## Run YARD to generate the HTML documentation for all components (source
  ## code and extra documentation)

  configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/yardopts.sources.in
    ${CMAKE_CURRENT_BINARY_DIR}/yardopts.sources
    )

  add_custom_target (doc
    COMMAND ${YARD_EXECUTABLE} --yardopts ${CMAKE_CURRENT_BINARY_DIR}/yardopts.sources
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running YARD to generate code documentation..."
    )

  ##_____________________________________________________________________________
  ## Run YARD to generate the HTML documentation for common information (not
  ## parsing of source code, therefore much faster)

  configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/yardopts.doc.in
    ${CMAKE_CURRENT_BINARY_DIR}/yardopts.doc
    )

  add_custom_target (doc_common
    COMMAND ${YARD_EXECUTABLE} --yardopts ${CMAKE_CURRENT_BINARY_DIR}/yardopts.doc
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running YARD to generate code documentation..."
    )
  
else (YARD_EXECUTABLE)
  
  ## Optional handling of documentation generation in case Yard is not available.

endif (YARD_EXECUTABLE)
