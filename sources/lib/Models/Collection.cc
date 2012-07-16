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

#include "Collection.h"

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  // ============================================================================
  //
  //  Construction
  //
  // ============================================================================
  
  /*!
    \param id      -- Identifier for the collection
    \param title   -- Title for the collection
    \param ownerId -- ID of the collection's owner
  */
  Collection::Collection (unsigned int const &id,
			  std::string const &title,
			  unsigned int const &ownerId)
  {
    init (id,
	  title,
	  "",
	  ownerId);
  }
  
  /*!
    \param id    -- Identifier for the collection
    \param title -- Title for the collection
    \param owner -- Owner of the collection
  */
  Collection::Collection (unsigned int const &id,
			  std::string const &title,
			  Account const &owner)
  {
    unsigned int ownerId = owner.id();

    init (id,
	  title,
	  "",
	  ownerId);
  }
  
  // ============================================================================
  //
  //  Private methods
  //
  // ============================================================================
  
  void Collection::init (unsigned int const &id,
			 std::string const &title,
			 std::string const &description,
			 unsigned int const &ownerId)
  {
    itsId          = id;
    itsTitle       = title;
    itsDescription = description;
    itsOwnerId     = ownerId;
  }

}  //  namespace prometheus -- END
