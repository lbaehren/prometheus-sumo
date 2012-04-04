
if (GIT_EXECUTABLE)

  foreach (_varRepo
      ## Some extensions to the Ruby programming language. 
      ruby-nuggets
      ## Ruby bindings to the magic(4) library, revised. 
      ruby-filemagic
      ## Ruby client for the Web Application Description Language.
      wadl
      )
    add_git_repository (${GIT_REPOSITORY_BASE}/${_varRepo}.git)
  endforeach (_varRepo)
  
endif (GIT_EXECUTABLE)
