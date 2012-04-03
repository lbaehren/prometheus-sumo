
if (GIT_EXECUTABLE)
  
  ## A Sinatra based web interface, to maintain a Jekyll website, including git
  ## version control.
  add_git_repository (git@github.com:prometheus-ev/JekyllCommander.git)

  ## Jekyll plugin that adds localization features to the rendering engine.
  add_git_repository (git@github.com:prometheus-ev/jekyll-localization.git)
  
  ## Jekyll plugin to provide alternative rendering engines.
  add_git_repository (git@github.com:prometheus-ev/jekyll-rendering.git)
  
endif (GIT_EXECUTABLE)
