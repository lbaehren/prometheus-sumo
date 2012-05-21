
if (DOXYGEN_EXECUTABLE)

  find_path (DOXYGEN_EXAMPLE_PATH monster.yaml
    PATHS ${PROJECT_SOURCE_DIR}
    PATH_SUFFIXES documentation documentation/examples
    )

  find_path (DOXYGEN_IMAGE_PATH
    NAMES "Redmine - Issues overview.png"
    PATHS ${PROJECT_SOURCE_DIR}
    PATH_SUFFIXES documentation documentation/images
    )
  
  ##__________________________________________________________  
  ## Generate configuration file for Doxygen
  
  set (MANUAL_PROJECT_NAME   "prometheus Reference Manual")
  set (MANUAL_INPUT          "${CMAKE_CURRENT_SOURCE_DIR}"  )
  set (MANUAL_GENERATE_LATEX "YES"                          )

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

  add_custom_command (
    TARGET Manual
    POST_BUILD
    COMMAND make
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/latex
    COMMENT "Generating PDF version of manual ..."
    )
  
  set_property (DIRECTORY
    APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/html
    )

  ## Target dependency

  add_dependencies(doc Manual)
  
endif (DOXYGEN_EXECUTABLE)
