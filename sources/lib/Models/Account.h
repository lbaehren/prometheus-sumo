
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
