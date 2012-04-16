
## ==============================================================================
##
##  Identification of operating system
##
## ==============================================================================

if (UNIX)

  if (APPLE)

    set (CMAKE_OS_NAME "OSX" CACHE STRING "Operating system name" FORCE)

  else (APPLE)

    ## Check for Debian GNU/Linux ________________

    find_file (DEBIAN_FOUND debian_version debconf.conf
      PATHS /etc
      )
    if (DEBIAN_FOUND)
      set (CMAKE_OS_NAME "Debian" CACHE STRING "Operating system name" FORCE)
    endif (DEBIAN_FOUND)

    ##  Check for Fedora _________________________

    find_file (FEDORA_FOUND fedora-release
      PATHS /etc
      )
    if (FEDORA_FOUND)
      set (CMAKE_OS_NAME "Fedora" CACHE STRING "Operating system name" FORCE)
    endif (FEDORA_FOUND)

    ##  Check for RedHat _________________________

    find_file (REDHAT_FOUND redhat-release inittab.RH
      PATHS /etc
      )
    if (REDHAT_FOUND)
      set (CMAKE_OS_NAME "RedHat" CACHE STRING "Operating system name" FORCE)
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
	## Check result of string search
	if (UBUNTU_FOUND)
	  set (CMAKE_OS_NAME "Ubuntu" CACHE STRING "Operating system name" FORCE)
	  set (DEBIAN_FOUND FALSE)
	endif (UBUNTU_FOUND)

      endif (UBUNTU_EXTRA)
      
    endif (DEBIAN_FOUND)
    
  endif (APPLE)

endif (UNIX)

## ==============================================================================
##
##  Installation of packages
##
## ==============================================================================

##__________________________________________________________
## Define top-level collective build target

add_custom_target (InstallPackages ALL
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Installing required system packages..."
  )

##__________________________________________________________
## Add platform-dependent instructions: only add the 
## sub-directory matching the previously determined platform

if (APPLE)
  
  add_subdirectory (osx)
  
else (APPLE)
  
  if (DEBIAN_FOUND)
    add_subdirectory (debian)
  endif (DEBIAN_FOUND)
  
  if (FEDORA_FOUND)
    add_subdirectory (fedora)
  endif (FEDORA_FOUND)
  
  if (REDHAT_FOUND)
    add_subdirectory (redhat)
  endif (REDHAT_FOUND)
  
  if (UBUNTU_FOUND)
    add_subdirectory (ubuntu)
  endif (UBUNTU_FOUND)
  
endif (APPLE)

##__________________________________________________________
## Installation of Ruby Gems

include (${CMAKE_CURRENT_SOURCE_DIR}/InstallRubyGems.cmake)
