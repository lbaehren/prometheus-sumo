
if (GIT_EXECUTABLE)
  
  foreach (_varRepo
      ## Apache module providing upload merging functionality.
      apache_upload_merger
      ## Apache module providing image resizing functionality.
      apache_image_resizer
      ## Apache module providing secure downloading functionality, just like Mongrel
      ## Secure Download does for mongrel.
      apache_secure_download
      ## Convert (analyse) Apache log files to COUNTER CSV.
      log2counter
      )
    add_git_repository (${GIT_REPOSITORY_BASE}/${_varRepo}.git)
  endforeach (_varRepo)
  
endif (GIT_EXECUTABLE)
