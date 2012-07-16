
#include "Collection.h"

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  // ============================================================================
  //
  //  Construction
  //
  // ============================================================================
  
  /*!
    \param id      -- Identifier for the collection
    \param title   -- Title for the collection
    \param ownerId -- ID of the collection's owner
  */
  Collection::Collection (unsigned int const &id,
			  std::string const &title,
			  unsigned int const &ownerId)
  {
    init (id,
	  title,
	  "",
	  ownerId);
  }
  
  /*!
    \param id    -- Identifier for the collection
    \param title -- Title for the collection
    \param owner -- Owner of the collection
  */
  Collection::Collection (unsigned int const &id,
			  std::string const &title,
			  Account const &owner)
  {
    unsigned int ownerId = owner.id();

    init (id,
	  title,
	  "",
	  ownerId);
  }
  
  // ============================================================================
  //
  //  Private methods
  //
  // ============================================================================
  
  void Collection::init (unsigned int const &id,
			 std::string const &title,
			 std::string const &description,
			 unsigned int const &ownerId)
  {
    itsId          = id;
    itsTitle       = title;
    itsDescription = description;
    itsOwnerId     = ownerId;
  }

}  //  namespace prometheus -- END
