
if (GIT_EXECUTABLE)

  foreach (_varRepo
      ## LibXML Ruby extensions
      libxml-ext
      ## Backports of newer Ruby features to older versions.
      ruby-backports
      ## Ruby bindings to the magic(4) library, revised. 
      ruby-filemagic
      ## Some extensions to the Ruby programming language. 
      ruby-nuggets
      ## Ruby client for the Web Application Description Language.
      wadl
      )
    add_git_repository (${GIT_REPOSITORY_BASE}/${_varRepo}.git)
  endforeach (_varRepo)
  
endif (GIT_EXECUTABLE)
