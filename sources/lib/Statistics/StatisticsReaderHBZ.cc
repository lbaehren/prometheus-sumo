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

#include "StatisticsReaderHBZ.h"

namespace prometheus {  //  namespace prometheus -- BEGIN

  namespace statistics {  //  namespace statistics -- BEGIN

    // ==========================================================================
    //
    //  Construction
    //
    // ==========================================================================

    StatisticsReaderHBZ::StatisticsReaderHBZ (std::string const &filename)
      : StatisticsReader (filename)
    {
    }

    // ==========================================================================
    //
    //  Public methods
    //
    // ==========================================================================

    //___________________________________________________________________________
    //                                                                processFile

    bool StatisticsReaderHBZ::processFile ()
    {
      bool status = true;
      std::string line;
      std::vector<std::string> data;

      /* Open stream for the input data ... */
      std::ifstream in (itsFilename.c_str());
      /* ... and check if the stream is ok */
      if (!in.is_open()) return false;
      /* Reset the internal storage for the actual entries */
      itsEntries.clear();

      //______________________________________________________
      // Extract the first line with the column headers

      status *= extactColumnHeaders (in);

      //______________________________________________________
      // Process the rows containing the actual data

#ifdef WITH_BOOST
      while (getline(in,line)) {
        /* Pass the line to the Tokenizer */
        Tokenizer tok(line);
        /* Retrieve the individual tokens */
        data.assign(tok.begin(),tok.end());

        if (data.size() < 3) {
          continue;
        }

        itsEntries.push_back(StatisticsHBZ(data[0],data[1],data[2],data[3]));
      }
#else
      status = false;
#endif

      return status;
    }

    //___________________________________________________________________________
    //                                                                    summary

    std::set<std::string> StatisticsReaderHBZ::institutions ()
    {
      std::vector<StatisticsHBZ>::iterator it;
      std::set<std::string> data;

      for (it=itsEntries.begin(); it!=itsEntries.end(); ++it) {
        data.insert(it->consortium());
      }

      return data;
    }

    //___________________________________________________________________________
    //                                                                    summary

    void StatisticsReaderHBZ::summary (std::ostream &os)
    {
      os << "[StatisticsReaderHBZ] Summary of internal parameters." << std::endl;
      os << "-- Input data file  = " << itsFilename                 << std::endl;
      os << "-- nof data columns = " << itsColumns.size()           << std::endl;
    }

    // ==========================================================================
    //
    //  Private methods
    //
    // ==========================================================================

    bool StatisticsReaderHBZ::extactColumnHeaders (std::ifstream &in)
    {
#ifdef WITH_BOOST
      bool status = true;
      std::string line;

      getline(in,line);
      Tokenizer tok(line);
      itsColumns.assign(tok.begin(),tok.end());

      if (itsColumns.empty()) {
        std::cerr << "[StatisticsReaderHBZ::extactColumnHeaders]"
                  << " No column headers extracted!"
                  << std::endl;
      }

      return status;
#else
      return false;
#endif
    }

  }  //  namespace statistics -- END

}  //  namespace prometheus -- END
