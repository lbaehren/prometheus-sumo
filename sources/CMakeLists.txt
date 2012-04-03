
## ==============================================================================
##
##  Macro definitions
##
## ==============================================================================

if (GIT_EXECUTABLE)
  
  ##__________________________________________________________________
  ## Macro for dealing with Git repositories
  
  macro (add_git_repository _projectRepos)
    
    ## Extract project name
    get_filename_component (_projectName ${_projectRepos} NAME_WE)
    
    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${_projectName})
      ## Update existing clone
      add_custom_target(update_${_projectName} ALL
	COMMAND ${GIT_EXECUTABLE} fetch
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${_projectName}
	COMMENT "Updating clone of Git repository ${_projectName} ..."
	)
    else (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${_projectName})
      ## Create new clone
      add_custom_target(clone_${_projectName} ALL
	COMMAND ${GIT_EXECUTABLE} clone --bare ${_projectRepos} ${_projectName}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	COMMENT "Cloning Git repository ${_projectName} ..."
	)
    endif (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${_projectName})

  endmacro (add_git_repository)
  
  ##__________________________________________________________________
  ## Macro for dealing with Subversion repositories
  
  macro (add_svn_repository _projectName _projectRepos)
    
    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${_projectName})
      
      add_custom_target(update_${_projectName} ALL
	COMMAND ${GIT_EXECUTABLE} svn rebase
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${_projectName}
	COMMENT "Updating clone of Subversion repository ${_projectName} ..."
	)
      
    else (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${_projectName})
      
      add_custom_target(clone_${_projectName} ALL
	COMMAND ${GIT_EXECUTABLE} svn clone ${_projectRepos} ${_projectName}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	COMMENT "Cloning Git repository ${_projectName} ..."
	)
      
    endif (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${_projectName})
    
  endmacro (add_svn_repository)
  
endif (GIT_EXECUTABLE)

## ==============================================================================
##
##  Create/Update clones of repositories
##
## ==============================================================================

if (GIT_EXECUTABLE)

  ##
  ##  Git repositories
  ##

  ## Convert database files to various formats.
  add_git_repository (https://github.com/blackwinter/athena.git)

  ## Assist with handling messed up encodings. 
  add_git_repository (https://github.com/blackwinter/cmess.git)

  ## Flatten relational databases.
  add_git_repository (https://github.com/blackwinter/flattendb.git)

  ## Website of prometheus - The digital image archive 
  add_git_repository (git@github.com:prometheus-ev/promhp.git)

  ## Some extensions to the Ruby programming language. 
  add_git_repository (git@github.com:prometheus-ev/ruby-nuggets.git)

  ## Ruby bindings to the magic(4) library, revised. 
  add_git_repository (git@github.com:prometheus-ev/ruby-filemagic.git)

  ## Convert (analyse) Apache log files to COUNTER CSV.
  add_git_repository (git@github.com:prometheus-ev/log2counter.git)

  ## Fuzzy string matching based on linguistic analysis.
  add_git_repository (git@github.com:prometheus-ev/perseus_match.git)

  ## Ruby client for the Web Application Description Language.
  add_git_repository (git@github.com:prometheus-ev/wadl.git)

  ##
  ##  Subversion repositories
  ##

  add_svn_repository (pandora   http://prometheus-app.uni-koeln.de/svn/pandora/trunk)

endif (GIT_EXECUTABLE)

## ==============================================================================
##
##  Subdirectories
##
## ==============================================================================

add_subdirectory (apache)
add_subdirectory (jekyll)
