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

#include "Account.h"

namespace prometheus {  //  namespace prometheus -- BEGIN

  // ============================================================================
  //
  //  Construction
  //
  // ============================================================================

  /*!
    \param id    -- Identifier for the account.
    \param email -- Email address for the account.
  */
  Account::Account (unsigned int const& id,
		    std::string const &email)
  {
    init (id, email);
  }

  // ============================================================================
  //
  //  Private methods
  //
  // ============================================================================

  /*!
    \param id    -- Identifier for the account.
    \param email -- Email address for the account.
    \param login -- Login for the account.
    \param firstname
    \param lastname
    \param title
  */
  void Account::init (unsigned int const &id,
		      std::string const &email,
		      std::string const &login,
		      std::string const &firstname,
		      std::string const &lastname,
		      std::string const &title)
  {
    itsId = id;
    itsEmail = email;

    if (login == "") {
      itsLogin = email;
    } else {
      itsLogin = login;
    }

    itsFirstname = firstname;
    itsLastname  = lastname;
    itsTitle     = title;
  }

}  //  namespace prometheus -- END
