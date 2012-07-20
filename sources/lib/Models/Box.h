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

#ifndef BOX_H
#define BOX_H

#include <iostream>
#include <set>
#include <string>

#include "Collection.h"
#include "Presentation.h"

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  /*!
    \class Box
    \ingroup prometheus
  */
  class Box {

    // === Public attributes ====================================================

  public:

    //! Type of the object encapsulated by the box
    enum Type {
      //! Box encapsulating a single Image
      Image,
      //! Box encapsulating a Collection of images
      Collection,
      //! Box encapsulating a Presentation
      Presentation,
      //! Box encapsulating the results from a search
      Search,
      //! Box encapsulating the results from a search within the collections
      CollectionSearch,
      //! Box encapsulating the results from a search within the presentations
      PresentationSearch
    };

    // === Protected attributes =================================================
    
  protected:
    
    //! Identifier for the box
    unsigned int itsId;
    //! Owner/Account ID 
    unsigned int itsOwnerId;
    //! Type of the object the box is connected to
    Box::Type itsObjectType;
    //! ID of the object the box is connected to
    unsigned int itsObjectId;
    
  public:

    // === Construction =========================================================
    
    //! Argumented constructor
    Box (unsigned int const &id,
	 unsigned int const &ownerId,
	 Box::Type const &objectType,
	 unsigned int const &objectId);

    //! Create a box for a Collection
    Box (unsigned int const &id,
	 class Collection const &collection);

    //! Create a box for a Presentation
    Box (unsigned int const &id,
	 class Presentation const &presentation);

    // === Parameter access =====================================================
    
    //! Get the identifier for the box
    inline unsigned int id () {
      return itsId;
    }

    //! Get the account ID for the box
    inline unsigned int ownerId () {
      return itsOwnerId;
    }

    //! Get the type of the object the box is connected to
    inline Box::Type objectType () {
      return itsObjectType;
    }

    // === Public methods =======================================================

    //! Show the contents of the Box
    inline void show () {
      summary (std::cout);
    }
    
    //! Show the contents of the Box, writing the output to stream \c os
    void show (std::ostream &os);

    //! Provide a summary of the internal status
    inline void summary () {
      summary (std::cout);
    }
    
    //! Provide a summary of the internal status to output stream \c os
    void summary (std::ostream &os);

    // === Static methods =======================================================

    //! Get a list of the available box types
    static std::set<std::string> types ();

  };
  
}  //  namespace prometheus -- END

#endif

