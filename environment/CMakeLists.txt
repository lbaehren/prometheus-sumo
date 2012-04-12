
## ==============================================================================
##
##  Identification of operating system
##
## ==============================================================================

if (UNIX)

  if (APPLE)

    set (CMAKE_OS_NAME "OSX")

  else (APPLE)

    ## Check for Debian GNU/Linux ________________

    find_file (DEBIAN_FOUND debian_version debconf.conf
      PATHS /etc
      )
    if (DEBIAN_FOUND)
      set (CMAKE_OS_NAME "Debian")
    endif (DEBIAN_FOUND)

    ##  Check for RedHat _________________________

    find_file (REDHAT_FOUND redhat-release inittab.RH
      PATHS /etc
      )
    if (REDHAT_FOUND)
      set (CMAKE_OS_NAME "RedHat")
    endif (REDHAT_FOUND)

    ## Extra check for Ubuntu ____________________

    if (DEBIAN_FOUND)

      ## At its core Ubuntu is a Debian system, with
      ## a slighty altered configuration; hence from
      ## a first superficial inspection a system will
      ## be considered as Debian, which signifies an
      ## extra check is required.

      find_file (UBUNTU_EXTRA legal issue
	PATHS /etc
	)

      if (UBUNTU_EXTRA)
	## Scan contents of file
	file (STRINGS ${UBUNTU_EXTRA} UBUNTU_FOUND
	  REGEX Ubuntu
	  )
	## Check result of
	if (UBUNTU_FOUND)
	  set (CMAKE_OS_NAME "Ubuntu")
	endif (UBUNTU_FOUND)

      endif (UBUNTU_EXTRA)
      
    endif (DEBIAN_FOUND)
    
  endif (APPLE)

endif (UNIX)

##_______________________________________________________________________________
## Define top-level collective build target

add_custom_target (InstallPackages
  COMMENT "Installing required system packages..."
  )

##_______________________________________________________________________________
## Select platform-dependent installation instructions for the individual
## packages

if (DEBIAN_FOUND)
  include (${CMAKE_CURRENT_SOURCE_DIR}/InstallPackagesDebian.cmake)
endif (DEBIAN_FOUND)

if (REDHAT_FOUND)
  include (${CMAKE_CURRENT_SOURCE_DIR}/InstallPackagesRedhat.cmake)
endif (REDHAT_FOUND)

if (UBUNTU_FOUND)
  include (${CMAKE_CURRENT_SOURCE_DIR}/InstallPackagesUbuntu.cmake)
endif (UBUNTU_FOUND)
