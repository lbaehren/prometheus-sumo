
#include "Box.h"

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  /*!
    \param id         -- Identifier for the box.
    \param userId     -- User/Account ID.
    \param objectType -- Type of the object the box is connected to.
    \param objectId   -- ID of the object the box is connected to.
  */
  Box::Box (unsigned int const &id,
	    unsigned int const &userId,
	    Box::Type const &objectType,
	    int const &objectId)
  {
    itsId         = id;
    itsUserId     = userId;
    itsObjectType = objectType;
    itsObjectId   = objectId;
  }
  
}  //  namespace prometheus -- END
