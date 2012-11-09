
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

  if (DEBIAN_FOUND OR UBUNTU_FOUND)
    include (${CMAKE_CURRENT_SOURCE_DIR}/PackagesDebian.cmake)
  endif (DEBIAN_FOUND OR UBUNTU_FOUND)

  if (REDHAT_FOUND OR FEDORA_FOUND)
    include (${CMAKE_CURRENT_SOURCE_DIR}/PackagesRedhat.cmake)
  endif (REDHAT_FOUND OR FEDORA_FOUND)

endif (APPLE)

##__________________________________________________________
## Installation of Ruby Gems

include (${CMAKE_CURRENT_SOURCE_DIR}/RubyGems.cmake)

## ==============================================================================
##
##  Sub-directories
##
## ==============================================================================

add_subdirectory (doxygen)
add_subdirectory (pandora)
add_subdirectory (promhp)
add_subdirectory (rant)
add_subdirectory (tinyxml2)
add_subdirectory (yaml-cpp)
add_subdirectory (yaz)
add_subdirectory (yazpp)

if (WITH_CLAMAV)
  add_subdirectory (clamav)
endif (WITH_CLAMAV)

if (MYSQL_FOUND)
  add_subdirectory (sphinx)
endif (MYSQL_FOUND)

## ==============================================================================
##
##  Package dependencies
##
## ==============================================================================

add_dependencies(yazpp yaz)
