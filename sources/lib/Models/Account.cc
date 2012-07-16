

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
