
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

##__________________________________________________________
## Installation of Ruby Gems

include (${CMAKE_CURRENT_SOURCE_DIR}/RubyGems.cmake)

## ==============================================================================
##
##  Sub-directories
##
## ==============================================================================

foreach (_package
  doxygen
  KWSys
  rant
  tinyxml2
  yaml-cpp
  yaz
  yazpp
  )
  if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${_package})
    ## Add sub-directory
    add_subdirectory (${_package})
    ## Update top-level configuration after installation of package
#    ExternalProject_Add_Step (${_package} update_configuration
#      COMMAND ${CMAKE_COMMAND} -E remove CMake*
#      COMMAND ${CMAKE_COMMAND} ..
#      COMMENT "Updating top-level configuration ..."
#      DEPENDEES install
#      DEPENDERS build
#      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#    )
  else (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${_package})
    message (STATUS ">> Skipping package ${_package}")
  endif (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${_package})
endforeach (_package)

if (WITH_CLAMAV)
  add_subdirectory (clamav)
endif (WITH_CLAMAV)

if (WITH_SPHINX)
  if (MYSQL_FOUND)
    add_subdirectory (sphinx)
  endif (MYSQL_FOUND)
endif (WITH_SPHINX)

## ==============================================================================
##
##  Package dependencies
##
## ==============================================================================

add_dependencies(yazpp yaz)
