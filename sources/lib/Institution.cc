
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
