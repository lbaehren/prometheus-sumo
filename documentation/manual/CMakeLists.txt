
if (DOXYGEN_EXECUTABLE)
  
  ##__________________________________________________________  
  ## Generate configuration file for Doxygen
  
  set (MANUAL_PROJECT_NAME "prometheus Developer's Manual")
  set (MANUAL_INPUT        "${CMAKE_CURRENT_SOURCE_DIR}"  )

  configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    )
  
  ##__________________________________________________________  
  ## Run Doxygen to generate documentation from sources
  
  add_custom_target (Manual
    COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
  
  set_property (DIRECTORY
    APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/html
    )

  ## Target dependency

  add_dependencies(doc Manual)
  
endif (DOXYGEN_EXECUTABLE)
