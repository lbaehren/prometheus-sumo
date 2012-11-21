/***************************************************************************
 *   Copyright (C) 2012                                                    *
 *   Lars B"ahren (lbaehren@gmail.com)                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "Common.h"

//_______________________________________________________________________________
//                                                                       to_lower

/*!
  \param in   -- Input string to convert to lower case.
  \return out -- String converted to lower case.
*/
std::string to_lower (std::string const &in)
{
  std::string out = in;

#ifdef WITH_BOOST
  boost::algorithm::to_lower(out);
#else
  std::transform (out.begin(), out.end(), out.begin(), ::tolower);
#endif

  return out;
}

//_______________________________________________________________________________
//                                                                    run_command

/*!
  \param command    -- System command to be run.
  \retval output    -- Output produced from running the system command.
  \param max_buffer -- Maximum size of the buffer to capture the \c output.
  \return status 
 */
int run_command (std::string const &command,
                 std::string &output,
                 int const &max_buffer)
{
  int status      = 0;
  std::string cmd = command;

  output.clear();
  cmd.append(" 2>&1");
  
  FILE * stream = popen(cmd.c_str(), "r");

  if (stream) {
    char buffer[max_buffer];
    while (!feof(stream))
      if (fgets(buffer, max_buffer, stream) != NULL) {
	output.append(buffer);
      }
    status = pclose(stream);
  } else {
    std::cerr << "ERROR - popen() failed!" << std::endl;
    status = -1;
  }

  /* Decode the exit status */
  if (WIFEXITED(status)) {
    status = WEXITSTATUS(status);
  }

  return status;
}
