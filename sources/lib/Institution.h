
#ifndef INSTITUTION_H
#define INSTITUTION_H

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

    //! The name of the institution
    std::string itsName;
    //! The title of the institution
    std::string itsTitle;
    //! A description for the institution
    std::string itsDescription;
    //! The address line of the institution
    std::string itsAddressline;
    std::string itsPostalcode;
    std::string itsCity;
    std::string itsCountry;
    std::string itsEmail;

    // === Private methods ======================================================

  public:

    // === Construction =========================================================

    //! Argumented constructor
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
    //! Set a description for the institution
    inline void setDescription (std::string const &description) {
      itsDescription = description;
    }

    //! Get the address line for the institution
    inline std::string addressline () {
      return itsAddressline;
    }
    //! Set the address line for the institution
    inline void setAddressline (std::string const &addressline) {
      itsAddressline = addressline;
    }

    //! Get the postal code for the institution
    inline std::string postalcode () {
      return itsPostalcode;
    }
    //! Set the postal code for the institution
    inline void setPostalcode (std::string const &postalcode) {
      itsPostalcode = postalcode;
    }
    
    //! Get the city of the institution
    inline std::string city () {
      return itsCity;
    }
    //! Set the city of the institution
    inline void setCity (std::string const &city) {
      itsCity = city;
    }

    //! Get the country of the institution
    inline std::string country () {
      return itsCountry;
    }

    //! Get the email contact for the institution
    inline std::string email () {
      return itsEmail;
    }

    // === Public methods =======================================================

    //! Set the address information for the institution
    void setAddress (std::string const &addressline,
		     std::string const &postalcode,
		     std::string const &city,
		     std::string const &country);

    // === Static methods =======================================================

  };
  
}  //  namespace prometheus -- END

#endif
