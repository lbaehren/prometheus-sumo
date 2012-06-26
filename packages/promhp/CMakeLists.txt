
## ==============================================================================
##
##  CMake project settings
##
## ==============================================================================

## Name of the project handled by CMake
project (promhp)

## Minimum required version of CMake to configure the project
cmake_minimum_required (VERSION 2.8)

## Enforced CMake policy 
cmake_policy (VERSION 2.8)

##  Package information
set (promhp_VERSION        "" )
set (promhp_SOURCE_ARCHIVE "" )
set (promhp_URL            "" )
set (promhp_GIT            "${GIT_REPOSITORY_BASE}/promhp.git" )

## ==============================================================================
##
##  Options
##
## ==============================================================================

option (promhp_FORCE_BUILD    "Force build and installation of package?" NO  )
option (promhp_FROM_REPOS     "Install package from repository?"         YES )
option (promhp_ENABLE_TESTING "Enable testing and experimental builds?"  YES )

##__________________________________________________________
## Handle option: Enable testing and experimental builds?

if (promhp_ENABLE_TESTING)
  include (CTest)
  enable_testing()
endif (promhp_ENABLE_TESTING)

##__________________________________________________________
## Handle option: Install package from repository?

if (promhp_FROM_REPOS)

  set (promhp_FORCE_BUILD TRUE)

  ## Check if a local version of the repository is available already;
  ## we need to be rather carefull here, in order not to accidentally
  ## pick up the Git repository files of the host project.
  find_file (PROMHP_REPOS_HEAD
    NAMES promhp/.git/HEAD promhp/HEAD
    HINTS ${prometheus-sumo_SOURCE_DIR} ${CMAKE_INSTALL_PREFIX}
    PATH_SUFFIXES data/repositories
    )
  
  if (PROMHP_REPOS_HEAD)
    get_filename_component (promhp_GIT ${PROMHP_REPOS_HEAD} PATH)
  endif (PROMHP_REPOS_HEAD)
  
endif (promhp_FROM_REPOS)

## ==============================================================================
##
##  Build instructions
##
##  - gem install jekyll
##  - gem install jekyll-rendering
##  - gem install jekyll-localization
##  - gem install RedCloth
##
## ==============================================================================

if (promhp_FORCE_BUILD)
  
  ## Locate source file to build from
  
  find_file (promhp_SOURCE ${promhp_SOURCE_ARCHIVE}
    PATHS ${PROJECT_SOURCE_DIR}
    )
  
  if (NOT promhp_SOURCE)
    set (promhp_SOURCE ${promhp_URL})
  endif (NOT promhp_SOURCE)
  
  ## Build package from source
  
  if (promhp_FROM_REPOS)
    
    ExternalProject_Add (promhp
      PREFIX ${PROJECT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      GIT_REPOSITORY ${promhp_GIT}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ${RAKE_EXECUTABLE} setup
      BUILD_COMMAND ${RAKE_EXECUTABLE} build
      INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_BINARY_DIR}/source/_site ${CMAKE_INSTALL_PREFIX}/share/promhp
      )
  
  else (promhp_FROM_REPOS)
    
    ExternalProject_Add (promhp
      PREFIX ${PROJECT_BINARY_DIR}
      DOWNLOAD_DIR download
      SOURCE_DIR source
      URL ${promhp_SOURCE}
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND rake setup
      BUILD_COMMAND rake_build
      INSTALL_COMMAND ${PORT_INSTALL_COMMAND} make install
      )
    
  endif (promhp_FROM_REPOS)
  
else (promhp_FORCE_BUILD)
  
  add_custom_target (<package>
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "[<package>] Found system-wide installation; skipping rebuild!"
    )
  
endif (promhp_FORCE_BUILD)
