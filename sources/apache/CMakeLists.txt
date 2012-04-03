
if (GIT_EXECUTABLE)

    ## Apache module providing image resizing functionality. 
  add_git_repository (https://github.com/blackwinter/apache_image_resizer.git)

  ## Apache module providing secure downloading functionality, just like Mongrel
  ## Secure Download does for mongrel.
  add_git_repository (https://github.com/blackwinter/apache_secure_download.git)

  add_git_repository (https://github.com/blackwinter/apache_upload_merger.git)

endif (GIT_EXECUTABLE)