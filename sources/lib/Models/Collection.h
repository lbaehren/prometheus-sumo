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

#ifndef COLLECTION_H
#define COLLECTION_H

#include "Account.h"

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  /*!
    \class Collection
    \ingroup prometheus
    \ingroup Models
    \author Lars Baehren
  */
  class Collection {

    //! Identifier for the collection
    unsigned int itsId;
    //! Title for the collection
    std::string itsTitle;
    //! Description for the collection
    std::string itsDescription;
    //! ID of the collection's owner
    unsigned int itsOwnerId;

  public:

    //! Argumented construction
    Collection (unsigned int const &id,
		std::string const &title,
		unsigned int const &ownerId);

    //! Argumented construction
    Collection (unsigned int const &id,
		std::string const &title,
		Account const &owner);

  private:
    
    //! Initialize internal parameters
    void init (unsigned int const &id,
	       std::string const &title,
	       std::string const &description,
	       unsigned int const &ownerId);
    
  };
  
}  //  namespace prometheus -- END

#endif
