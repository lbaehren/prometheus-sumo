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

#ifndef APACHE_LOGFILE_ENTRY_H
#define APACHE_LOGFILE_ENTRY_H

#include <Common.h>

#ifdef WITH_BOOST
#include <boost/regex.hpp>
#endif

namespace prometheus { // namespace prometheus -- BEGIN

  namespace statistics { // namespace statistics -- BEGIN

    /*!
      \file ApacheLogfileEntry.h
      \class ApacheLogfileEntry
      \ingroup prometheus
      \ingroup statistics
      \brief Entry line in Apache log file
      \author Lars Baehren
      \date 2012-10-17

      \test testApacheLogs.cc
     */
    class ApacheLogfileEntry {

      //! IP address of the client (remote host) which made the request.
      std::string itsRemoteHost;
      //! RFC 1413 identity of the client.
      std::string itsUserIdent;
      //! userid of the person requesting the document.
      std::string itsUserAuth;
      //! Date the server finished handling the request
      std::string itsDate;
      //! Time of day the server finished handling the request
      std::string itsTime;
      //! Timezone/Offset w.r.t. UTC
      std::string itsTimezone;
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

    public:

      // === Parameter access ===================================================

      //! IP address of the client (remote host) which made the request.
      inline std::string remoteHost () {
        return itsRemoteHost;
      }

      //! RFC 1413 identity of the client.
      inline std::string userIdent () {
        return itsUserIdent;
      }

      //! userid of the person requesting the document.
      inline std::string userAuth () {
        return itsUserAuth;
      }

      //! Date the server finished handling the request
      inline std::string data () {
        return itsDate;
      }

      // === Public methods =====================================================

      //! Processes a line of a log file.
      bool processLine (std::string const &line);

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
