
if (YARD_EXECUTABLE)

  ##_____________________________________________________________________________
  ## Generate YARD options file

  set (YARDOPTS "${CMAKE_CURRENT_BINARY_DIR}/yardopts")

  file (WRITE  ${YARDOPTS} "-o ${CMAKE_CURRENT_BINARY_DIR}/html\n" )
  file (APPEND ${YARDOPTS} "--main ${PROJECT_SOURCE_DIR}/README\n" )
  
  if (DOCUMENTATION_PANDORA)
    file (APPEND ${YARDOPTS} "${PROJECT_SOURCE_DIR}/sources/pandora\n"  )
  endif (DOCUMENTATION_PANDORA)
  
  file (APPEND ${YARDOPTS} "-\n"                                   )
  file (APPEND ${YARDOPTS} "${CMAKE_CURRENT_SOURCE_DIR}/*.md\n"    )
  
  ##_____________________________________________________________________________
  ## Run YARD to generate the HTML documentation

  find_file (HAVE_YARDOPTS yardopts
    ${CMAKE_CURRENT_BINARY_DIR}
    )
  
  if (HAVE_YARDOPTS)
    add_custom_target (doc
      COMMAND ${YARD_EXECUTABLE} --yardopts ${YARDOPTS}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Running YARD to generate code documentation..."
      )
  else (HAVE_YARDOPTS)
    message (STATUS "Unable to find YARD options file!")
  endif (HAVE_YARDOPTS)
  
else (YARD_EXECUTABLE)
  
  ## Optional handling of documentation generation in case Yard is not available.

endif (YARD_EXECUTABLE)
