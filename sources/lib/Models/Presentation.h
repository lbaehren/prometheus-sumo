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

#ifndef PRESENTATION_H
#define PRESENTATION_H

#include "Account.h"

namespace prometheus {  //  namespace prometheus -- BEGIN

  /*!
    \class Presentation
    \ingroup prometheus
    \ingroup Models
    \author Lars Baehren
  */
  class Presentation {

    //! Identifier for the presentation
    unsigned int itsId;
    //! Title for the presentation
    std::string itsTitle;
    //! Description for the presentation
    std::string itsDescription;
    //! ID of the presentation's owner
    unsigned int itsOwnerId;

  public:

    //! Argumented construction
    Presentation (unsigned int const &id,
		std::string const &title,
		unsigned int const &ownerId);

    // === Parameter access =====================================================

    //! Get the identifier for the presentation
    inline unsigned int id () const {
      return itsId;
    };

    //! Get the title for the presentation
    inline std::string title () const {
      return itsTitle;
    };

    //! Get the description for the presentation
    inline std::string description () const {
      return itsDescription;
    };

    //! Get the ID of the presentation's owner
    inline unsigned int ownerId () const {
      return itsOwnerId;
    };

  private:

    //! Initialize internal parameters
    void init (unsigned int const &id,
	       std::string const &title,
	       std::string const &description,
	       unsigned int const &ownerId);

  };  //  class Presentation -- END

}  //  namespace prometheus -- END

#endif
