
if (YARD_EXECUTABLE)

  ## Generate .yardopts file: The yardoc tool will use the options found in this
  ## file. It is recommended to check this in to your repository and distribute
  ## it with your source. This file is placed at the root of your project (in
  ## the directory you run yardoc from) and contains all of arguments you would
  ## otherwise pass to the command-line tool.
#  configure_file (
#    ${CMAKE_CURRENT_SOURCE_DIR}/yardopts.in
#    ${CMAKE_CURRENT_BINARY_DIR}/.yardopts
#    )
  
  ## Run target to generate the HTML documentation for all components (source
  ## code and extra documentation)
  add_custom_target (doc
    COMMAND ${YARD_EXECUTABLE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running YARD to generate code documentation..."
    )

  add_custom_target (doc_common
    COMMAND ${YARD_EXECUTABLE} -o ${CMAKE_CURRENT_BINARY_DIR}/html -r ${CMAKE_CURRENT_SOURCE_DIR}/Prometheus.rdoc - ${CMAKE_CURRENT_SOURCE_DIR}/*.rdoc
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running YARD to generate code documentation..."
    )
  
else (YARD_EXECUTABLE)
  
  ## Optional handling of documentation generation in case Yard is not available.

endif (YARD_EXECUTABLE)
