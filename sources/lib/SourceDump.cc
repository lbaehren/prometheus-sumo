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

#include "SourceDump.h"

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  // ============================================================================
  //
  //  Construction
  //
  // ============================================================================
  
  /*!
    \param rootNode  -- Name of the root node in the XML file.
    \param imageNode -- Name of the node containing attributes of an image
  */
  SourceDump::SourceDump (std::string const &rootNode,
			  std::string const &imageNode)
    : itsRootNode (rootNode),
      itsImageNode (imageNode)
  {
    init();
  }
  
  // ============================================================================
  //
  //  Private methods
  //
  // ============================================================================

  void SourceDump::init ()
  {
    itsAttributes.clear();

    itsAttributes["title"]    = "title";
    itsAttributes["artist"]   = "artist";
    itsAttributes["date"]     = "date";
    itsAttributes["location"] = "location";
    itsAttributes["credits"]  = "credits";
  }
  
  
}  //  namespace prometheus -- END
