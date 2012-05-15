
# By default we are using YARD as tool to generate documentation from the
# source files and any extra files (such as the ones carrying installation 
# instructions, etc.); however YARD is an extra package which (typically) does
# not get installed automatically along with Ruby, hence we need a fallback in
# order to still be able to generate the documentation. Therefore if YARD is
# not installed (or at least: not found), we try to use RDoc, which is the more
# traditional documentation generation tool in the Ruby world.

if (YARD_EXECUTABLE)

  ##_____________________________________________________________________________
  ## Generate YARD options file

  set (YARDOPTS "${CMAKE_CURRENT_BINARY_DIR}/yardopts")

  file (WRITE  ${YARDOPTS} "-o ${CMAKE_CURRENT_BINARY_DIR}/html\n" )
  file (APPEND ${YARDOPTS} "--main ${PROJECT_SOURCE_DIR}/README\n" )
  file (APPEND ${YARDOPTS} "${PROJECT_SOURCE_DIR}/sources\n"  )
  
  if (PANDORA_GENERATE_DOCS)
    file (APPEND ${YARDOPTS} "${PROJECT_SOURCE_DIR}/repositories/pandora/app\n"  )
    file (APPEND ${YARDOPTS} "${PROJECT_SOURCE_DIR}/repositories/pandora/lib\n"  )
  endif (PANDORA_GENERATE_DOCS)
  
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
  
  if (RDOC_EXECUTABLE)

    add_custom_target (doc
      COMMAND ${RDOC_EXECUTABLE} -o ${CMAKE_CURRENT_BINARY_DIR}/html ${CMAKE_CURRENT_SOURCE_DIR}/*.md
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Running YARD to generate code documentation..."
      )

  else (RDOC_EXECUTABLE)
  
    message (STATUS "No fallback found for documentation generation!")

  endif (RDOC_EXECUTABLE)

endif (YARD_EXECUTABLE)

### === Developer's Manual ======================================================

add_subdirectory (manual)
