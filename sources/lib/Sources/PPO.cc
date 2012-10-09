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

#include "PPO.h"

namespace prometheus {  //  namespace prometheus -- BEGIN

  namespace source {  //  namespace source -- BEGIN

    // ==========================================================================
    //
    //  Construction
    //
    // ==========================================================================

    PPO::PPO (std::string const &rootNode,
              std::string const &imageNode)
      : SourceDump (rootNode,imageNode)
    {
      init ();
    }

    // ==========================================================================
    //
    //  Public methods
    //
    // ==========================================================================

    // ==========================================================================
    //
    //  Static methods
    //
    // ==========================================================================

    //___________________________________________________________________________
    //                                                                  sourceIDs

    /*!
      \param filename -- Name of the file containing the source IDs.
      \param match    -- Matching pattern to distinguish source IDs from possible
                         other contents found within the input file.
      \return items   -- Array with the source IDs.
    */
    std::vector<std::string> PPO::sourceIDs (std::string const &filename,
                                             std::string const &match)
    {
      std::vector<std::string> items;
      std::string buffer;
      std::ifstream infile (filename.c_str());
      boost::regex ex (match);

      if ( infile.is_open() ) {
        while (infile.good()) {
          // Read line from file into buffer ...
          std::getline (infile, buffer);
          // ... and check it against the matching pattern
          if (boost::regex_search(buffer, ex))
          {
            items.push_back(buffer);
          }
        }
      }

      return items;
    }

    //___________________________________________________________________________
    //                                                              queryDatabase

#ifdef WITH_YAZPP
    /*!
      \param ids      -- Array with the image IDs to query the database for.
      \param server   -- Name of the Z39.50 server.
      \param port     -- Port number via which to establish the connection.
      \param database -- Name of the database.
      \param syntax   -- Preferred record syntax.
      \return records -- Array with the raw-data (in string format) for the
                         database records.
    */
    std::vector<std::string> PPO::queryDatabase (std::vector<std::string> const &ids,
                                                 std::string const &server,
                                                 int const &port,
                                                 std::string const &database,
                                                 std::string const &syntax)
    {
      std::vector<std::string> records;

      /* Configuration of server connection */
      ZOOM::connection conn(server.c_str(), port);
      conn.option ("databaseName",   database.c_str());
      conn.option ("preferredRecordSyntax", syntax.c_str());

      for (int n=0; n<ids.size(); ++n) {
        std::string queryString = "@attr 1=12 " + ids[n];
        /* Define query prefix */
        ZOOM::prefixQuery pq (queryString.c_str());

        /* Get the results from the database server */
        try {
          ZOOM::resultSet rs (conn, pq);
            if ( rs.size()>0 ) {
              ZOOM::record rec (rs, 0);
              records.push_back(rec.rawdata());
            }
        } catch (ZOOM::systemException &e) {
          std::cerr << "[PPO::queryDatabase] System error " << e.errcode()
                    << " (" << e.errmsg() << ")"
                    << std::endl;
	} catch (ZOOM::bib1Exception &e) {
	  std::cerr << "[PPO::queryDatabase] BIB-1 error " << e.errcode()
		    << " (" << e.errmsg() << "): " << e.addinfo()
		    << std::endl;
	} catch (ZOOM::queryException &e) {
	  std::cerr << "[PPO::queryDatabase] Query error " << e.errcode()
		    << " (" << e.errmsg() << "): " << e.addinfo()
		    << std::endl;
	} catch (ZOOM::exception &e) {
	  std::cerr << "[PPO::queryDatabase] Error " << e.errcode()
		    << " (" << e.errmsg() << ")"
		    << std::endl;
	}
    }

      return records;
    }

    /*!
      \param filename -- Name of the file containing the source IDs.
      \param match    -- Matching pattern to distinguish source IDs from possible
                         other contents found within the input file.
      \param server   -- Name of the Z39.50 server.
      \param port     -- Port number via which to establish the connection.
      \param database -- Name of the database.
      \param syntax   -- Preferred record syntax.
      \return records -- Array with the raw-data (in string format) for the
                         database records.
    */
    std::vector<std::string> PPO::queryDatabase (std::string const &filename,
                                                 std::string const &match,
                                                 std::string const &server,
                                                 int const &port,
                                                 std::string const &database,
                                                 std::string const &syntax)
    {
      std::vector<std::string> records;
      std::vector<std::string> ids = sourceIDs (filename, match);

      if (!ids.empty()) {
        records = queryDatabase (ids,
                                 server,
                                 port,
                                 database,
                                 syntax);
      }

      return records;
    }

#endif

  }   //  namespace source -- END

}  //  namespace prometheus -- END
