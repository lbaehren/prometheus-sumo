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

#ifndef STATISTICS_READER_HBZ_H
#define STATISTICS_READER_HBZ_H

#include "StatisticsReader.h"
#include "StatisticsHBZ.h"

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  /*!
    \class StatisticsReaderHBZ
    \ingroup prometheus
    \brief Class for reading statistics file for HBZ
    \author Lars Baehren
    \date 2012-07-12
  */
  class StatisticsReaderHBZ : public StatisticsReader {
    
    std::vector<std::string> itsColumns;
    std::vector<StatisticsHBZ> itsEntries;
    
  public:
    
    //! Argumented constructor
    StatisticsReaderHBZ (std::string const &filename);
    
    // === Parameter access =====================================================
    

    // === Public methods =======================================================

    //! Read and process the input data file
    bool processFile ();

    //! Get the number of entries in the statistics data file
    inline unsigned int nofEntries () {
      itsEntries.size();
    }

    //! Columns names
    inline std::vector<std::string> columns () {
      return itsColumns;
    }

    //! Number of data columns
    inline unsigned int nofColumns () {
      itsColumns.size();
    }

    //! Get the names of the institutions
    std::set<std::string> institutions ();

    //! Provide a summary of the object's internal parameters and status
    void summary (std::ostream &os);

  private:

    // === Private methods ======================================================

    bool extactColumnHeaders (std::ifstream &in);

  };
  
}  //  namespace prometheus -- END

#endif

