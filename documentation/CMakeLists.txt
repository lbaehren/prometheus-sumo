
## ==============================================================================
##
##  System inspection and configuration
##
## ==============================================================================

## Path to directory with examples files

find_path (DOXYGEN_EXAMPLE_PATH monsters.yaml
  PATHS ${PROJECT_SOURCE_DIR}
  PATH_SUFFIXES documentation documentation/examples
  )

## Path to directory with image files

find_path (DOXYGEN_IMAGE_PATH
  NAMES
  Association_Presentation.png
  Wiki__Login.png
  PATHS ${PROJECT_SOURCE_DIR}
  PATH_SUFFIXES documentation documentation/images images
  )

## Custom stylesheet

find_file (DOXYGEN_HTML_STYLESHEET stylesheet.css
  PATHS ${PROJECT_SOURCE_DIR}
  PATH_SUFFIXES documentation
  )

## ==============================================================================
##
##  Documentation generation
##
## ==============================================================================

if (DOXYGEN_EXECUTABLE)

  set (DOXYGEN_INPUT "${PROJECT_SOURCE_DIR}/documentation ${PROJECT_SOURCE_DIR}/sources ${CMAKE_INSTALL_PREFIX}/include")
  set (DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_INSTALL_PREFIX}/share/doc/prometheus")

  if (DOXYGEN_DOT_FOUND)
    set (HAVE_DOT "YES")
  else (DOXYGEN_DOT_FOUND)
    set (HAVE_DOT "NO")
  endif (DOXYGEN_DOT_FOUND)

  if (WITH_LATEX_DOC)
    if (LATEX_COMPILER)
      set (DOXYGEN_GENERATE_LATEX "YES")
    else (LATEX_COMPILER)
      set (DOXYGEN_GENERATE_LATEX "NO")
    endif (LATEX_COMPILER)
  else (WITH_LATEX_DOC)
      set (DOXYGEN_GENERATE_LATEX "NO")
  endif (WITH_LATEX_DOC)

  ## Create Doxygen output directory

  if (NOT EXISTS ${DOXYGEN_OUTPUT_DIRECTORY})
    execute_process (
      COMMAND ${CMAKE_COMMAND} -E make_directory ${DOXYGEN_OUTPUT_DIRECTORY}
      WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}
      )
  endif (NOT EXISTS ${DOXYGEN_OUTPUT_DIRECTORY})

  ## Configuration summary page
  configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/ConfigurationSummary.doxy.in
    ${CMAKE_CURRENT_BINARY_DIR}/ConfigurationSummary.doxy
    )

  ## Configuration file for Doxygen
  configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.config.in
    ${CMAKE_CURRENT_BINARY_DIR}/doxygen.config
    )

  ##________________________________________________________
  ## HTML pages

  add_custom_target (Documentation
    COMMAND ${DOXYGEN_EXECUTABLE} doxygen.config
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/doxygen.config
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Running Doxygen to generate documentation ..."
    )

  ##________________________________________________________
  ## LaTeX/PDF document

  if (WITH_LATEX_DOC)
    if (LATEX_COMPILER)
      add_custom_command (
	TARGET Documentation
	POST_BUILD
	COMMAND ${CMAKE_MAKE_PROGRAM}
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/latex
	)
    endif (LATEX_COMPILER)
  endif (WITH_LATEX_DOC)

  if (ENABLE_TESTING)
    add_test (documentation Documentation)
  endif (ENABLE_TESTING)

endif (DOXYGEN_EXECUTABLE)

## ==============================================================================
##
##  Source code documentation
##
## ==============================================================================

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

  if (WITH_PANDORA_DOCS)
    file (APPEND ${YARDOPTS} "${PROJECT_SOURCE_DIR}/repositories/pandora/app\n"  )
    file (APPEND ${YARDOPTS} "${PROJECT_SOURCE_DIR}/repositories/pandora/lib\n"  )
  endif (WITH_PANDORA_DOCS)

  file (APPEND ${YARDOPTS} "-\n"                                   )
  file (APPEND ${YARDOPTS} "${CMAKE_CURRENT_SOURCE_DIR}/*.md\n"    )

  ##_____________________________________________________________________________
  ## Run YARD to generate the HTML documentation

  find_file (HAVE_YARDOPTS yardopts
    ${CMAKE_CURRENT_BINARY_DIR}
    )

  if (HAVE_YARDOPTS)
    add_custom_target (DocumentationSources
      COMMAND ${YARD_EXECUTABLE} --yardopts ${YARDOPTS}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Running YARD to generate code documentation..."
      )
  else (HAVE_YARDOPTS)
    message (STATUS "Unable to find YARD options file!")
  endif (HAVE_YARDOPTS)

else (YARD_EXECUTABLE)

  if (RDOC_EXECUTABLE)

    add_custom_target (DocumentationSources
      COMMAND ${RDOC_EXECUTABLE} -o ${CMAKE_CURRENT_BINARY_DIR}/html ${CMAKE_CURRENT_SOURCE_DIR}/*.md
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Running YARD to generate code documentation..."
      )

  else (RDOC_EXECUTABLE)

    message (STATUS "No fallback found for documentation generation!")

  endif (RDOC_EXECUTABLE)

endif (YARD_EXECUTABLE)
