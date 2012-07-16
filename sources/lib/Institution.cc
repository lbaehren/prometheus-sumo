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

#include "Institution.h"

namespace prometheus {
  
  // ============================================================================
  //
  //  Construction
  //
  // ============================================================================

  /*!
    \param name        -- The name of the institution.
    \param title       -- The title of the institution.
    \param description -- A description for the institution.
  */
  Institution::Institution (std::string const &name,
			    std::string const &title,
			    std::string const &description)
  {
    itsName        = name;
    itsTitle       = title;
    itsDescription = description;
  }
  
  // ============================================================================
  //
  //  Public methods
  //
  // ============================================================================

  /*!
    \param addressline -- The address line for the institution.
    \param postalcode  -- The postal code for the institution.
    \param city        -- 
    \param country     -- 
  */
  void Institution::setAddress (std::string const &addressline,
				std::string const &postalcode,
				std::string const &city,
				std::string const &country)
  {
    itsAddressline = addressline;
    itsPostalcode  = postalcode;
    itsCity        = city;
    itsCountry     = country;
  }
    
}
