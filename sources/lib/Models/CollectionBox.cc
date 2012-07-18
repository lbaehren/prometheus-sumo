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

#include "CollectionBox.h"

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  // ============================================================================
  //
  //  Construction
  //
  // ============================================================================
  
  CollectionBox::CollectionBox (unsigned int const &id,
				class Collection const &collection)
    : Box (id,
  	   collection)
  {
  }
  
  // ============================================================================
  //
  //  Public methods
  //
  // ============================================================================
  
  void CollectionBox::summary (std::ostream &os)
  {
    os << "[CollectionBox] Summary of internal parameters." << std::endl;
    os << "-- Box ID  = " << itsId     << std::endl;
    os << "-- User ID = " << itsUserId << std::endl;
  }
  
}  //  namespace prometheus -- END
