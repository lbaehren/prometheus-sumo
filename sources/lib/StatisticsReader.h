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

#ifndef STATISTICS_READER_H
#define STATISTICS_READER_H

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


namespace prometheus {  //  namespace prometheus -- BEGIN

  /*!
    \file StatisticsReader.h
    \class StatisticsReader
    \ingroup prometheus
    \brief Base class for reading statistics files
    \author Lars Baehren
    \date 2012-07-12
  */
  class StatisticsReader {

  protected:

    //! Name of the input data file
    std::string itsFilename;

  public:

    //! Argumented constructor
    StatisticsReader (std::string const &filename);

    // === Parameter access =====================================================

    //! Get the name of the input data file
    inline std::string filename () {
      return itsFilename;
    }
    //! Set the name of the input data file
    inline void setFilename (std::string const &filename) {
      itsFilename = filename;
    }

    // === Public methods =======================================================

    //! Read and process the input data file
    virtual bool processFile () = 0;

    //! Provide a summary of the object's internal parameters and status
    inline void summary () {
      summary (std::cout);
    }

    //! Provide a summary of the object's internal parameters and status
    void summary (std::ostream &os);

  private:

    // === Private methods ======================================================

    bool checkFile ();

  };

}  //  namespace prometheus -- END

#endif

