# +-----------------------------------------------------------------------------+
# |   Copyright (C) 2012                                                        |
# |   Lars B"ahren (lbaehren@gmail.com)                                         |
# |                                                                             |
# |   This program is free software; you can redistribute it and/or modify      |
# |   it under the terms of the GNU General Public License as published by      |
# |   the Free Software Foundation; either version 2 of the License, or         |
# |   (at your option) any later version.                                       |
# |                                                                             |
# |   This program is distributed in the hope that it will be useful,           |
# |   but WITHOUT ANY WARRANTY; without even the implied warranty of            |
# |   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             |
# |   GNU General Public License for more details.                              |
# |                                                                             |
# |   You should have received a copy of the GNU General Public License         |
# |   along with this program; if not, write to the                             |
# |   Free Software Foundation, Inc.,                                           |
# |   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.                 |
# +-----------------------------------------------------------------------------+

# - Check for the presence of GEM
#
# The following variables are set when GEM is found:
#  GEM_FOUND      = Set to true, if all components of GEM have been found.
#  GEM_INCLUDES   = Include path for the header files of GEM
#  GEM_LIBRARIES  = Link these to use GEM
#  GEM_LFLAGS     = Linker flags (optional)

if (NOT GEM_FOUND)
    
  if (NOT GEM_ROOT_DIR)
    set (GEM_ROOT_DIR ${CMAKE_INSTALL_PREFIX})
  endif (NOT GEM_ROOT_DIR)
  
  ##_____________________________________________________________________________
  ## Check for the executable
  
  find_program (GEM_EXECUTABLE gem
    HINTS ${GEM_ROOT_DIR}  ${CMAKE_INSTALL_PREFIX}
    PATH_SUFFIXES bin
    )
  
  ##_____________________________________________________________________________
  ## Extract program version

  if (GEM_EXECUTABLE)

    ## Run gem to display version number
    execute_process(
      COMMAND ${GEM_EXECUTABLE} --version
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      RESULT_VARIABLE GEM_RESULT_VARIABLE
      OUTPUT_VARIABLE GEM_OUTPUT_VARIABLE
      ERROR_VARIABLE GEM_ERROR_VARIABLE
      OUTPUT_STRIP_TRAILING_WHITESPACE
      )

    ## Process output in order to extract version number. Gem returns status 0
    ## if run successfully.
    if (NOT GEM_RESULT_VARIABLE)

      string(REGEX REPLACE "gem " "" GEM_VERSION ${GEM_OUTPUT_VARIABLE})

      if (GEM_VERSION)
	## Convert string to list of numbers
	string (REGEX REPLACE "\\." ";" GEM_VERSION_LIST ${GEM_VERSION})
	## Retrieve individual elements in the list
	list(GET GEM_VERSION_LIST 0 GEM_VERSION_MAJOR)
	list(GET GEM_VERSION_LIST 1 GEM_VERSION_MINOR)
	list(GET GEM_VERSION_LIST 2 GEM_VERSION_PATCH)
      endif (GEM_VERSION)
      
    endif (NOT GEM_RESULT_VARIABLE)

  endif (GEM_EXECUTABLE)
  
  ##_____________________________________________________________________________
  ## Actions taken when all components have been found
  
  if (GEM_EXECUTABLE)
    set (GEM_FOUND TRUE)
  else (GEM_EXECUTABLE)
    set (GEM_FOUND FALSE)
    if (NOT GEM_FIND_QUIETLY)
      if (NOT GEM_INCLUDES)
	message (STATUS "Unable to find GEM header files!")
      endif (NOT GEM_INCLUDES)
      if (NOT GEM_LIBRARIES)
	message (STATUS "Unable to find GEM library files!")
      endif (NOT GEM_LIBRARIES)
    endif (NOT GEM_FIND_QUIETLY)
  endif (GEM_EXECUTABLE)
  
  if (GEM_FOUND)
    if (NOT GEM_FIND_QUIETLY)
      message (STATUS "Found components for GEM")
      message (STATUS "GEM_ROOT_DIR  = ${GEM_ROOT_DIR}")
      message (STATUS "GEM_INCLUDES  = ${GEM_INCLUDES}")
      message (STATUS "GEM_LIBRARIES = ${GEM_LIBRARIES}")
    endif (NOT GEM_FIND_QUIETLY)
  else (GEM_FOUND)
    if (GEM_FIND_REQUIRED)
      message (FATAL_ERROR "Could not find GEM!")
    endif (GEM_FIND_REQUIRED)
  endif (GEM_FOUND)
  
  ##_____________________________________________________________________________
  ## Mark advanced variables
  
  mark_as_advanced (
    GEM_ROOT_DIR
    GEM_INCLUDES
    GEM_LIBRARIES
    )
  
endif (NOT GEM_FOUND)
