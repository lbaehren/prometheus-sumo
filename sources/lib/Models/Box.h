
#include <iostream>
#include <string>

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  /*!
    \class Box
    \ingroup prometheus
  */
  class Box {

    // === Public attributes ====================================================

  public:

    //! Type of the object encapsulated by the box
    enum Type {
      //! Box encapsulating a single Image
      Image,
      //! Box encapsulating a Collection of images
      Collection,
      //! Box encapsulating a Presentation
      Presentation,
      //! Box encapsulating the results from a search
      Search,
      //! Box encapsulating the results from a search within the collections
      CollectionSearch,
      //! Box encapsulating the results from a search within the presentations
      PresentationSearch
    };

    // === Protected attributes =================================================
    
  protected:
    
    //! Identifier for the box
    unsigned int itsId;
    //! User/Account ID 
    unsigned int itsUserId;
    //! Type of the object the box is connected to
    Box::Type itsObjectType;
    //! ID of the object the box is connected to
    int itsObjectId;
    
  public:
    
    //! Argumented constructor
    Box (unsigned int const &id,
	 unsigned int const &userId,
	 Box::Type const &objectType,
	 int const &objectId);
    
    //! Get the identifier for the box
    inline unsigned int id () {
      return itsId;
    }

    //! Get the account ID for the box
    inline unsigned int userId () {
      return itsUserId;
    }

    //! Get the type of the object the box is connected to
    inline Box::Type objectType () {
      return itsObjectType;
    }

  };
  
}  //  namespace prometheus -- END
