
if (GIT_EXECUTABLE)

  ## Some extensions to the Ruby programming language. 
  add_git_repository (git@github.com:prometheus-ev/ruby-nuggets.git)

  ## Ruby bindings to the magic(4) library, revised. 
  add_git_repository (git@github.com:prometheus-ev/ruby-filemagic.git)

  ## Ruby client for the Web Application Description Language.
  add_git_repository (git@github.com:prometheus-ev/wadl.git)

endif (GIT_EXECUTABLE)