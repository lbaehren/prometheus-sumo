
##_______________________________________________________________________________
## Identify operating system

if (UNIX)
  if (APPLE)
    set (CMAKE_OS_NAME "OSX")
  else (APPLE)
    ## Check for Debian GNU/Linux
    find_file (DEBIAN_FOUND debian_version debconf.conf
      PATHS /etc
      )
    if (DEBIAN_FOUND)
      set (CMAKE_OS_NAME "Debian")
    endif (DEBIAN_FOUND)
    ##  Check for RedHat
    find_file (REDHAT_FOUND redhat-release inittab.RH
      PATHS /etc
      )
  endif (APPLE)
    if (REDHAT_FOUND)
      set (CMAKE_OS_NAME "RedHat")
    endif (REDHAT_FOUND)
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