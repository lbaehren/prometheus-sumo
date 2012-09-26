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

      if ( infile.is_open() ) {
        while (infile.good()) {
          /* Read line from file into buffer */
          std::getline (infile, buffer);
          /* Check contents of line against matching pattern */
          if ( buffer.find(match) )
          {
            items.push_back(buffer);
          }
        }
      }

      return items;
    }

  }   //  namespace source -- END

}  //  namespace prometheus -- END
