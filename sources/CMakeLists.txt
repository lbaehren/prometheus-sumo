
## ==============================================================================
##
##  Top-level target for updating clones of working copies
##
## ==============================================================================

add_custom_target (UpdateSources ALL
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Updating clones of working copies ..."
  )

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
      add_custom_command (
	TARGET UpdateSources
        POST_BUILD
	COMMAND ${GIT_EXECUTABLE} fetch
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${_projectName}
	COMMENT "Updating clone of Git repository ${_projectName} ..."
	)
    else (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${_projectName})
      ## Create new clone
      add_custom_command (
	TARGET UpdateSources
        POST_BUILD
	COMMAND ${GIT_EXECUTABLE} clone ${_projectRepos} ${_projectName}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	COMMENT "Cloning Git repository ${_projectName} ..."
	)
    endif (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${_projectName})

  endmacro (add_git_repository)
  
  ##__________________________________________________________________
  ## Macro for dealing with Subversion repositories
  
  macro (add_svn_repository _projectName _projectRepos)
    
    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${_projectName})
      
      add_custom_command (
	TARGET UpdateSources
        POST_BUILD
	COMMAND ${GIT_EXECUTABLE} svn rebase
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${_projectName}
	COMMENT "Updating clone of Subversion repository ${_projectName} ..."
	)
      
    else (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${_projectName})
      
      add_custom_command (
	TARGET UpdateSources
        POST_BUILD
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
  add_git_repository (${GIT_REPOSITORY_BASE}/athena.git)

  ## Assist with handling messed up encodings. 
  add_git_repository (${GIT_REPOSITORY_BASE}/cmess.git)

  ## Flatten relational databases.
  add_git_repository (${GIT_REPOSITORY_BASE}/flattendb.git)

  ## Website of prometheus - The digital image archive 
  add_git_repository (${GIT_REPOSITORY_BASE}/promhp.git)

  ## Fuzzy string matching based on linguistic analysis.
  add_git_repository (${GIT_REPOSITORY_BASE}/perseus_match.git)

  ##
  ##  Subversion repositories
  ##

  add_svn_repository (pandora http://prometheus-srv.uni-koeln.de/svn/pandora)

endif (GIT_EXECUTABLE)

## ==============================================================================
##
##  Subdirectories
##
## ==============================================================================

add_subdirectory (apache)
add_subdirectory (jekyll)
add_subdirectory (ruby)
