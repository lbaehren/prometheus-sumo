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

#include "ApacheLogfileParser.h"

namespace prometheus {  //  namespace prometheus -- BEGIN

  namespace statistics {  //  namespace statistics -- BEGIN

    ApacheLogfileParser::ApacheLogfileParser (std::string const &filename)
    {
      itsFilename = filename;
    }

    // ==========================================================================
    //
    //  Static methods
    //
    // ==========================================================================

    //___________________________________________________________________________
    //                                                                processLine

    /*!
      \param matches -- Array containing the matched sub-strings.
      \param line    -- Line in the logfile to parse.
      \return status -- Status of the operation; returns \c false in case an
                        error was encountered.
    */
    bool ApacheLogfileParser::processLine (std::vector<std::string> &matches,
                                           std::string const &line)
    {
#ifdef WITH_BOOST
      return true;
#else
      std::cerr << "[ApacheLogfileParser::processLine] WARNING: "
		<< "Missing Boost library - unable to parse input string!"
		<< std::endl;
      return false;
#endif
    }

    //___________________________________________________________________________
    //                                                                processLine

    /*!
      \param matches -- 
      \param line    -- 
      \return status -- Status of the operation; returns \c false in case an 
                        error was encountered.
    */
    bool ApacheLogfileParser::processLine (ApacheLogfileEntry &matches,
                                           std::string const &line)
    {
#ifdef WITH_BOOST
      boost::regex e (regex_apache_log);
      return true;
#else
      std::cerr << "[ApacheLogfileParser::processLine] WARNING: "
		<< "Missing Boost library - unable to parse input string!"
		<< std::endl;
      return false;
#endif
    }

  }  //  namespace statistics -- END

}  //  namespace prometheus -- END
