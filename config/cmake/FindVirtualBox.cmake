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

# - Check for the presence of VIRTUALBOX
#
# The following variables are set when VIRTUALBOX is found:
#  VIRTUALBOX_FOUND      = Set to true, if all components of VirtualBox
#                         have been found.

if (NOT VIRTUALBOX_FOUND)

  if (NOT VIRTUALBOX_ROOT_DIR)
    set (VIRTUALBOX_ROOT_DIR ${CMAKE_INSTALL_PREFIX})
  endif (NOT VIRTUALBOX_ROOT_DIR)

  ##_____________________________________________________________________________
  ## Check for the executable

  foreach (_program
    VirtualBox
    VBoxManage
    )
    string (TOUPPER ${_program} _varProgram)
    find_program (${_varProgram}_EXECUTABLE ${_program}
      HINTS ${${_varProgram}_ROOT_DIR} ${CMAKE_INSTALL_PREFIX}
      PATH_SUFFIXES bin
      )
  endforeach (_program)

  ##_____________________________________________________________________________
  ## Actions taken when all components have been found

  if (VIRTUALBOX_EXECUTABLE)
    set (VIRTUALBOX_FOUND TRUE)
  else (VIRTUALBOX_EXECUTABLE)
    set (VIRTUALBOX_FOUND FALSE)
    if (NOT VIRTUALBOX_FIND_QUIETLY)
      if (NOT VIRTUALBOX_INCLUDES)
	message (STATUS "Unable to find VIRTUALBOX header files!")
      endif (NOT VIRTUALBOX_INCLUDES)
      if (NOT VIRTUALBOX_LIBRARIES)
	message (STATUS "Unable to find VIRTUALBOX library files!")
      endif (NOT VIRTUALBOX_LIBRARIES)
    endif (NOT VIRTUALBOX_FIND_QUIETLY)
  endif (VIRTUALBOX_EXECUTABLE)

  if (VIRTUALBOX_FOUND)
    if (NOT VIRTUALBOX_FIND_QUIETLY)
      message (STATUS "Found components for VIRTUALBOX")
      message (STATUS "VIRTUALBOX_ROOT_DIR  = ${VIRTUALBOX_ROOT_DIR}")
      message (STATUS "VIRTUALBOX_INCLUDES  = ${VIRTUALBOX_INCLUDES}")
      message (STATUS "VIRTUALBOX_LIBRARIES = ${VIRTUALBOX_LIBRARIES}")
    endif (NOT VIRTUALBOX_FIND_QUIETLY)
  else (VIRTUALBOX_FOUND)
    if (VIRTUALBOX_FIND_REQUIRED)
      message (FATAL_ERROR "Could not find VIRTUALBOX!")
    endif (VIRTUALBOX_FIND_REQUIRED)
  endif (VIRTUALBOX_FOUND)

  ##_____________________________________________________________________________
  ## Mark advanced variables

  mark_as_advanced (
    VIRTUALBOX_ROOT_DIR
    VIRTUALBOX_EXECUTABLE
    )

endif (NOT VIRTUALBOX_FOUND)
