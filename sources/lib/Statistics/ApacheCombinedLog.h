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

#ifndef APACHE_COMBINED_LOG_H
#define APACHE_COMBINED_LOG_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <set>
#include <map>

#ifdef WITH_BOOST
#include <boost/tokenizer.hpp>
typedef boost::tokenizer< boost::escaped_list_separator<char> > Tokenizer;
#endif

namespace prometheus { // namespace prometheus -- BEGIN

  namespace statistics { // namespace statistics -- BEGIN

    //! Fields the line of an Apache common log file
    struct ApacheCombinedLogLine {
      //! IP address of the client (remote host) which made the request.
      std::string itsRemoteHost;
      //! RFC 1413 identity of the client.
      std::string itsUserIdent;
      //! userid of the person requesting the document.
      std::string itsUserAuth;
      //! Time that the server finished processing the request.
      std::string itsTimestamp;
      //! Request line from the client in double quotes.
      std::string itsRequestMethod;
      //! URL requested.
      std::string itsRequestUri;
      //! Protocol used.
      std::string itsRequestProtocol;
      //! Result code.
      std::string itsStatus;
      //! Number of bytes transferred.
      std::string itsBytes;
      //! Referrer.
      std::string itsReferer;
      //! Browser identification string.
      std::string itsUserAgent;
    };

    /*!
      \file ApacheCombinedLog.h
      \class ApacheCombinedLog
      \ingroup prometheus
      \ingroup statistics
      \brief Handling of Apache combined logs
      \author Lars Baehren
      \date 2012-10-16
     */
    class ApacheCombinedLog {

      //! Name of the input data file
      std::string itsFilename;

    public:

    //! Argumented constructor
    ApacheCombinedLog (std::string const &filename);

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
    static bool processLine (std::vector<std::string> matches,
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
