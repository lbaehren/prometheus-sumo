
if (GIT_EXECUTABLE)

  foreach (_repos
      ## Jekyll plugin that adds localization features to the rendering engine
      jekyll-localization
      ## Jekyll plugin to extend the pagination generator
      jekyll-pagination
      ## Jekyll plugin to provide alternative rendering engines
      jekyll-rendering
      ## Jekyll plugin to automatically generate a tag cloud and tag pages
      jekyll-tagging
      ## A Sinatra based web interface, to maintain a Jekyll website, including
      ## git version control. 
      JekyllCommander
      )
    add_git_repository (${GIT_REPOSITORY_BASE}/${_repos}.git)
  endforeach (_repos)
  
endif (GIT_EXECUTABLE)


