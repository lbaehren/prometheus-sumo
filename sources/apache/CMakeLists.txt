
if (GIT_EXECUTABLE)

  foreach (_varRepo
      ## Apache module providing upload merging functionality.
      https://github.com/blackwinter/apache_upload_merger.git
      ## Apache module providing image resizing functionality.
      https://github.com/blackwinter/apache_image_resizer.git
      ## Convert (analyse) Apache log files to COUNTER CSV.
      git@github.com:prometheus-ev/log2counter.git
      )
    add_git_repository (${_varRepo})
  endforeach (_varRepo)

  ## Apache module providing secure downloading functionality, just like Mongrel
  ## Secure Download does for mongrel.
  add_git_repository (https://github.com/blackwinter/apache_secure_download.git)

endif (GIT_EXECUTABLE)