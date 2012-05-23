
if (DOXYGEN_EXECUTABLE)

  ## ============================================================================
  ##
  ##  Locate directories and files
  ##
  ## ============================================================================

  find_path (DOXYGEN_EXAMPLE_PATH monster.yaml
    PATHS ${PROJECT_SOURCE_DIR}
    PATH_SUFFIXES documentation documentation/examples
    )

  find_path (DOXYGEN_IMAGE_PATH
    NAMES "Redmine - Issues overview.png" "Redmine - Issues by project.png"
    PATHS ${PROJECT_SOURCE_DIR}
    PATH_SUFFIXES documentation documentation/images
    )

  ## ============================================================================
  ##
  ##  Test LaTeX installation
  ##
  ## ============================================================================

  ##__________________________________________________________  
  ## Find LaTeX installation

  find_package (LATEX)

  ##__________________________________________________________  
  ## Test for LaTeX modules

  if (LATEX_COMPILER)

    set (DOXYGEN_GENERATE_LATEX TRUE)
    set (_latexTest ${CMAKE_CURRENT_BINARY_DIR}/TestLATEX.tex)
    
    foreach (_latexPackage
      float
      listings
      )
      
      message (STATUS "Checking for LaTeX package ${_latexPackage}")
      
      string (TOUPPER ${_latexPackage} _latexPackageVar)
      
      ## Generate LaTeX source file
      file (WRITE  ${_latexTest} "\\documentclass[a4paper,fontsize=10pt]{scrartcl}"\n )
      file (APPEND ${_latexTest} "\\usepackage{"${_latexPackage}}\n )
      file (APPEND ${_latexTest} "\\begin{document}"\n )
      file (APPEND ${_latexTest} "This is a simple test document."\n )
      file (APPEND ${_latexTest} "\\end{document}"\n )
      
      ## Run the test file through LaTeX
      
      execute_process(
	COMMAND ${LATEX_COMPILER} ${_latexTest}
	TIMEOUT 2
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	RESULT_VARIABLE _latexTestResult
	OUTPUT_VARIABLE _latexTestOutput
	ERROR_VARIABLE _latexTestError
	)
      
      if (_latexTestResult)
        set (DOXYGEN_GENERATE_LATEX FALSE)
	message (STATUS "Checking for LaTeX package ${_latexPackage} - FAIL")
      else (_latexTestResult)
	message (STATUS "Checking for LaTeX package ${_latexPackage} - Success")
      endif (_latexTestResult)
      
    endforeach (_latexPackage)
  endif (LATEX_COMPILER)
  
  ##__________________________________________________________  
  ##  Set Doxygen configuration parameters

  if (PDFLATEX_COMPILER)
    set (DOXYGEN_USE_PDFLATEX "YES" )
  else (PDFLATEX_COMPILER)
    set (DOXYGEN_USE_PDFLATEX "YES" )
  endif (PDFLATEX_COMPILER)
  
  ## ============================================================================
  ##
  ##  Generate configuration file for Doxygen
  ##
  ## ============================================================================
  
  set (MANUAL_PROJECT_NAME     "prometheus Reference Manual"   )
  set (MANUAL_INPUT            "${CMAKE_CURRENT_SOURCE_DIR}"   )
  set (DOXYGEN_HTML_STYLESHEET "${CMAKE_CURRENT_BINARY_DIR}/doxygen_html_stylesheet.css")
  set (DOXYGEN_HTML_FOOTER     "${CMAKE_CURRENT_BINARY_DIR}/doxygen_html_footer.html")

  if (DOXYGEN_GENERATE_LATEX)
    set (MANUAL_GENERATE_LATEX "YES" )
  else ()
    set (MANUAL_GENERATE_LATEX "NO" )
  endif ()

  configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/doxygen_html_stylesheet.css.in
    ${DOXYGEN_HTML_STYLESHEET}
    )
  
  configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/doxygen_html_footer.html.in
    ${DOXYGEN_HTML_FOOTER}
    )
  
  configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    )
  
  ## ============================================================================
  ##
  ##  Build targets
  ##
  ## ============================================================================

  ## HTML output
  
  add_custom_target (Manual
    COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )

  ## LaTeX / PDF output

  if (DOXYGEN_GENERATE_LATEX)
     add_custom_command (
      TARGET Manual
      POST_BUILD
      COMMAND make
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/latex
      COMMENT "Generating PDF version of manual ..."
      )
  endif (DOXYGEN_GENERATE_LATEX)

  ## Directory cleanup

  set_property (DIRECTORY
    APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/html
    )
  
  ## Target dependency
  
  add_dependencies(doc Manual)
  
endif (DOXYGEN_EXECUTABLE)
