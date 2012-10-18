/***************************************************************************
 * Copyright (C) 2012                                                      *
 * Lars B"ahren (lbaehren@gmail.com)                                       *
 *                                                                         *
 * This program is free software; you can redistribute it and/or modify    *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation; either version 2 of the License, or       *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This program is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the            *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with this program; if not, write to the                           *
 * Free Software Foundation, Inc.,                                         *
 * 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.                *
 ***************************************************************************/

#ifndef APACHE_LOGFILE_PARSER_H
#define APACHE_LOGFILE_PARSER_H

#include "ApacheLogfileEntry.h"

namespace prometheus { // namespace prometheus -- BEGIN

  namespace statistics { // namespace statistics -- BEGIN

    const std::string regex_apache_log ("^([^[:space:]]+) ([^[:space:]]+) ([^[:space:]]+) \\[([^:]+):([[:digit:]]+:[[:digit:]]+:[[:digit:]]+) ([^\\]]+)\\] \"([^[:space:]]+) (.+?) ([^[:space:]]+)\" ([^[:space:]]+) ([^[:space:]]+)");

    /*!
      \file ApacheLogfileParser.h
      \class ApacheLogfileParser
      \ingroup prometheus
      \ingroup statistics
      \brief Handling of Apache combined logs
      \author Lars Baehren
      \date 2012-10-16

      \test testApacheLogs.cc
     */
    class ApacheLogfileParser {

      //! Name of the input data file
      std::string itsFilename;
      
    public:

      //! Argumented constructor
      ApacheLogfileParser (std::string const &filename);

      // === Parameter access ===================================================

      //! Get the name of the input data file.
      inline std::string filename () {
	return itsFilename;
      }

      //! Set the name of the input data file.
      inline void setFilename (std::string const &filename) {
	itsFilename = filename;
      }

    // === Public methods =====================================================

    //! Read and process the input data file.
    bool processFile ();

    //! Processes a line of a log file.
    static bool processLine (std::vector<std::string> &matches,
                             std::string const &line);

    //! Processes a line of a log file.
    static bool processLine (ApacheLogfileEntry &matches,
                             std::string const &line);

    //! Provide a summary of the object's internal parameters and status
    inline void summary () {
      summary (std::cout);
    }

    //! Provide a summary of the object's internal parameters and status
    void summary (std::ostream &os);

    };

  } // namespace statistics -- END

} // namespace prometheus -- END

#endif
