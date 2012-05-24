
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
	TARGET FetchRepositories
        POST_BUILD
	COMMAND ${GIT_EXECUTABLE} fetch
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${_projectName}
	COMMENT "Updating clone of Git repository ${_projectName} ..."
	)
    else (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${_projectName})
      ## Create new clone
      add_custom_command (
	TARGET FetchRepositories
        POST_BUILD
	COMMAND ${GIT_EXECUTABLE} clone --bare ${_projectRepos} ${_projectName}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	COMMENT "Cloning Git repository ${_projectName} ..."
	)
    endif (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${_projectName})

    set_property (DIRECTORY
      APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
      ${CMAKE_CURRENT_SOURCE_DIR}/${_projectName}
      )
    
    
  endmacro (add_git_repository)
  
  ##__________________________________________________________________
  ## Macro for dealing with Subversion repositories
  ##
  ##  In order to be complete, the checkout should be performed from 
  ##  the root level of the repository and not the trunk only.
  
  macro (add_svn_repository _projectName _projectRepos)
    
    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${_projectName})
      
      add_custom_command (
	TARGET FetchRepositories
        POST_BUILD
	COMMAND ${GIT_EXECUTABLE} svn rebase
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${_projectName}
	COMMENT "Updating clone of Subversion repository ${_projectName} ..."
	)
      
    else (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${_projectName})
      
      add_custom_command (
	TARGET FetchRepositories
        POST_BUILD
	COMMAND ${GIT_EXECUTABLE} svn clone -s ${_projectRepos} ${_projectName}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	COMMENT "Cloning Git repository ${_projectName} ..."
	)
      
    endif (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${_projectName})
    
  endmacro (add_svn_repository)
  
endif (GIT_EXECUTABLE)

## ==============================================================================
##
##  Top-level target for updating clones of working copies
##
## ==============================================================================

add_custom_target (FetchRepositories ALL
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Updating clones of working copies ..."
  )

## ==============================================================================
##
##  Create/Update clones of repositories
##
## ==============================================================================

if (GIT_EXECUTABLE)

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

  ##________________________________________________________
  ## Apache modules

  ## Apache module providing upload merging functionality.
  add_git_repository (${GIT_REPOSITORY_BASE}/apache_upload_merger.git)
  ## Apache module providing image resizing functionality.
  add_git_repository (${GIT_REPOSITORY_BASE}/apache_image_resizer.git)
  ## Apache module providing secure downloading functionality, just like Mongrel
  ## Secure Download does for mongrel.
  add_git_repository (${GIT_REPOSITORY_BASE}/apache_secure_download.git)
  ## Convert (analyse) Apache log files to COUNTER CSV.
  add_git_repository (${GIT_REPOSITORY_BASE}/log2counter.git)

  ##________________________________________________________
  ## Jekyll modules/plugins

  ## Jekyll plugin that adds localization features to the rendering engine
  add_git_repository (${GIT_REPOSITORY_BASE}/jekyll-localization.git)
  ## Jekyll plugin to extend the pagination generator
  add_git_repository (${GIT_REPOSITORY_BASE}/jekyll-pagination.git)
  ## Jekyll plugin to provide alternative rendering engines
  add_git_repository (${GIT_REPOSITORY_BASE}/jekyll-rendering.git)
  ## Jekyll plugin to automatically generate a tag cloud and tag pages
  add_git_repository (${GIT_REPOSITORY_BASE}/jekyll-tagging.git)
  ## A Sinatra based web interface, to maintain a Jekyll website, including
  ## git version control. 
  add_git_repository (${GIT_REPOSITORY_BASE}/JekyllCommander.git)

  ##________________________________________________________
  ## Ruby extensions/modules
  
  ## LibXML Ruby extensions
  add_git_repository (${GIT_REPOSITORY_BASE}/libxml-ext.git)
  ## Backports of newer Ruby features to older versions.
  add_git_repository (${GIT_REPOSITORY_BASE}/ruby-backports.git)
  ## Ruby bindings to the magic(4) library, revised. 
  add_git_repository (${GIT_REPOSITORY_BASE}/ruby-filemagic.git)
  ## Some extensions to the Ruby programming language. 
  add_git_repository (${GIT_REPOSITORY_BASE}/ruby-nuggets.git)
  ## Ruby client for the Web Application Description Language.
  add_git_repository (${GIT_REPOSITORY_BASE}/wadl.git)
  
  ##
  ##  Subversion repositories
  ##

  add_svn_repository (pandora http://prometheus-srv.uni-koeln.de/svn/pandora)

endif (GIT_EXECUTABLE)
