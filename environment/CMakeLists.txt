
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