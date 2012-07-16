
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
