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

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  /*!
    \class Account
    \ingroup prometheus
    \ingroup Models
    \author Lars Baehren
  */
  class Account {

    //! Identifier
    unsigned int itsId;
    //! Email address
    std::string itsEmail;
    //! Login
    std::string itsLogin;
    //! First name
    std::string itsFirstname;
    //! Last name
    std::string itsLastname;
    //! Title
    std::string itsTitle;
    
  public:

    //! Argumented constructor
    Account (unsigned int const& id,
	     std::string const &email);

    // === Parameter access =====================================================

    //! Get the identifier for the account
    inline unsigned int id () const {
      return itsId;
    }

    //! Get the email address for the account    
    inline std::string email () const {
      return itsEmail;
    }

    //! Get the login for the account
    inline std::string login () const {
      return itsLogin;
    }

    //! Get the first name of the user
    inline std::string firstname () const {
      return itsFirstname;
    }

    //! Get the last name of the user
    inline std::string lastname () const {
      return itsLastname;
    }

  private:
    
    void init (unsigned int const &id,
	       std::string const &email,
	       std::string const &login="",
	       std::string const &firstname="",
	       std::string const &lastname="",
	       std::string const &title="");
    
  };
  
}  //  namespace prometheus -- END

#endif
