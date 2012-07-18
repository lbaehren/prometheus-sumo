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

#include "Box.h"

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  // ============================================================================
  //
  //  Construction
  //
  // ============================================================================
  
  /*!
    \param id         -- Identifier for the box.
    \param userId     -- User/Account ID.
    \param objectType -- Type of the object the box is connected to.
    \param objectId   -- ID of the object the box is connected to.
  */
  Box::Box (unsigned int const &id,
	    unsigned int const &userId,
	    Box::Type const &objectType,
	    unsigned int const &objectId)
  {
    itsId         = id;
    itsUserId     = userId;
    itsObjectType = objectType;
    itsObjectId   = objectId;
  }
  
  /*!
    \param id         -- Identifier for the box.
    \param collection -- Collection for which the box is created.
  */
  Box::Box (unsigned int const &id,
	    class Collection const &collection)
  {
    itsId         = id;
    itsUserId     = collection.ownerId();
    itsObjectType = Box::Collection;
    itsObjectId   = collection.id();
  }
  
  // ============================================================================
  //
  //  Public methods
  //
  // ============================================================================
  
  void Box::show (std::ostream &os)
  {
    os << "This is box no. " << itsId << " for user no. " << itsUserId << std::endl;
  }

  void Box::summary (std::ostream &os)
  {
    os << "[Box] Summary of internal parameters." << std::endl;
    os << "-- Box ID  = " << itsId     << std::endl;
    os << "-- User ID = " << itsUserId << std::endl;
  }

  // ============================================================================
  //
  //  Public methods
  //
  // ============================================================================
  
  std::set<std::string> Box::types ()
  {
    std::set<std::string> var;

    var.insert("Image");
    var.insert("Collection");
    var.insert("Presentation");
    var.insert("Search");
    var.insert("CollectionSearch");
    var.insert("PresentationSearch");

    return var;
  }
  
}  //  namespace prometheus -- END
