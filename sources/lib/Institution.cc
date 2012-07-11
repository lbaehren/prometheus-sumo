
#include "Institution.h"

namespace prometheus {
  
  Institution::Institution (std::string const &name,
			    std::string const &title,
			    std::string const &description)
  {
    itsName        = name;
    itsTitle       = title;
    itsDescription = description;
  }
  
  
}
