
#include <iostream>
#include <string>
#include <vector>

#include "Common.h"

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  /*!
    \class Institution
    \ingroup prometheus
    \brief An institutation and its details
    \author Lars Baehren
    \date 2012-07-11
  */
  class Institution {

    // === Private data =========================================================

    std::string itsName;
    std::string itsTitle;
    std::string itsDescription;
    std::string itsAddressline;
    std::string itsPostalcode;
    std::string itsCity;
    std::string itsCountry;
    std::string itsEmail;

    // === Private methods ======================================================

    // === Public methods =======================================================

  public:

    // === Construction =========================================================

    Institution (std::string const &name,
		 std::string const &title="",
		 std::string const &description="");

    // === Parameter access =====================================================

    //! Get the name of the institution
    inline std::string name () {
      return itsName;
    }
    //! Set the name of the institution
    inline void setName (std::string const &name) {
      itsName = name;
    }

    //! Get the title of the institution
    inline std::string title () {
      return itsTitle;
    }
    //! Set the title of the institution
    inline void setTitle (std::string const &title) {
      itsTitle = title;
    }

    //! Get a description for the institution
    inline std::string description () {
      return itsDescription;
    }

    //! Get the address line of the institution
    inline std::string addressline () {
      return itsAddressline;
    }

    //! Get the postal code of the institution
    inline std::string postalcode () {
      return itsPostalcode;
    }

    //! Get the city of the institution
    inline std::string city () {
      return itsCity;
    }

    //! Get the country of the institution
    inline std::string country () {
      return itsCountry;
    }

    //! Get the email contact for the institution
    inline std::string email () {
      return itsEmail;
    }

    // === Static methods =======================================================

  };
  
}  //  namespace prometheus -- END
