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

#include "StatisticsReader.h"

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  // ============================================================================
  //
  //  Construction
  //
  // ============================================================================

  StatisticsReader::StatisticsReader (std::string const &filename)
  {
    itsFilename = filename;

    if (!checkFile()) {
      std::cerr << "Failed to open file " << filename
		<< " for read access!"
		<< std::endl;
    }
  }
  
  // ============================================================================
  //
  //  Public methods
  //
  // ============================================================================


  // ============================================================================
  //
  //  Private methods
  //
  // ============================================================================
  
  bool StatisticsReader::checkFile ()
  {
    /* Open stream for the input data ... */
    std::ifstream in (itsFilename.c_str());
    /* ... and check if the stream is ok */
    if (in.is_open()) {
      if (in.good()) {
	in.close();
	return true;
      } else {
	in.close();
	return false;
      }
    } else {
      return false;
    }
  }
  
}  //  namespace prometheus -- END

