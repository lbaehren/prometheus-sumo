
## ==============================================================================
##
##  Installation of system packages
##
## ==============================================================================

##__________________________________________________________
## Define top-level collective build target

add_custom_target (InstallPackages
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Installing required system packages..."
  )

##__________________________________________________________
## Add platform-dependent instructions: only add the
## sub-directory matching the previously determined platform

if (APPLE)
    include (${CMAKE_CURRENT_SOURCE_DIR}/PackagesOSX.cmake)
else (APPLE)
  ## Debian / Ubuntu
  if (DEBIAN_FOUND OR UBUNTU_FOUND)
    include (${CMAKE_CURRENT_SOURCE_DIR}/PackagesDebian.cmake)
  endif (DEBIAN_FOUND OR UBUNTU_FOUND)
  ## RedHat / Fedora
  if (REDHAT_FOUND OR FEDORA_FOUND)
    include (${CMAKE_CURRENT_SOURCE_DIR}/PackagesRedhat.cmake)
  endif (REDHAT_FOUND OR FEDORA_FOUND)
endif (APPLE)

include (${CMAKE_CURRENT_SOURCE_DIR}/RubyGems.cmake)

## ==============================================================================
##
##  Sub-directories
##
## ==============================================================================

add_subdirectory (KWSys)
add_subdirectory (tinyxml2)
add_subdirectory (yaml-cpp)

if (WITH_PACKAGE_CLAMAV)
  add_subdirectory (clamav)
endif (WITH_PACKAGE_CLAMAV)

if (WITH_PACKAGE_FERRET)
  add_subdirectory (ferret)
endif (WITH_PACKAGE_FERRET)

if (WITH_DOXYGEN)
  add_subdirectory (doxygen)
endif (WITH_DOXYGEN)

if (WITH_PACKAGE_SPHINX)
  if (MYSQL_FOUND)
    add_subdirectory (sphinx)
  else (MYSQL_FOUND)
    message (STATUS "Unable to install build package Sphinx - missing MySQL!")
  endif (MYSQL_FOUND)
endif (WITH_PACKAGE_SPHINX)

if (WITH_PACKAGE_YAZ)
  ## directories
  add_subdirectory (yaz)
  add_subdirectory (yazpp)
  ## dependencies
  add_dependencies(yazpp yaz)
endif (WITH_PACKAGE_YAZ)

