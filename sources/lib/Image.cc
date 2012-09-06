/***************************************************************************
 *   Copyright (C) 2012                                                    *
 *   Lars B"ahren (lbaehren@gmail.com)                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "Image.h"

namespace prometheus {  //  namespace prometheus -- BEGIN

  // ===========================================================================
  //
  //  Construction
  //
  // ===========================================================================

  //____________________________________________________________________________
  //                                                                       Image

  /*!
    \param title  -- Title of the image.
    \param artist -- Artist for the image.
  */
  Image::Image (std::string const &title,
                std::string const &artist)
  {
    init();
    itsAttributes["title"]  = title;
    itsAttributes["artist"] = artist;
  }
  
  //____________________________________________________________________________
  //                                                                       Image

  /*!
    \param attributes -- Attributes attached to/describing the image.
  */
  Image::Image (std::map<std::string,std::string> const &attributes)
  {
    itsAttributes.clear();

    if (!attributes.empty()) {
      itsAttributes = attributes;
    }
  }

  // ===========================================================================
  //
  //  Private methods
  //
  // ===========================================================================

  //____________________________________________________________________________
  //                                                               attributeKeys

  std::set<std::string> Image::attributeKeys ()
  {
    std::map<std::string,std::string>::iterator it;
    std::set<std::string> keys;

    for (it=itsAttributes.begin();it!=itsAttributes.end(); ++it) {
      keys.insert(it->first);
    }
    return keys;
  }

  //____________________________________________________________________________
  //                                                                hasAttribute

  /*!
    \param key     -- Keyword to be searched for amongst the attributes.
    \return status -- Returns \c true of the provided \c key can be found amongst
            the attributes; else \c false is returned.
   */
  bool Image::hasAttribute (std::string const &key)
  {
    std::map<std::string,std::string>::iterator it = itsAttributes.find(key);

    if (it==itsAttributes.end()) {
      return false;
    } else {
      return true;
    }
  }

  //____________________________________________________________________________
  //                                                                   attribute

  /*!
    \retval value  -- Value of the attribute indicated by \c key.
    \param key     -- Keyword to be searched for amongst the attributes.
    \return status -- Returns \c true of the provided \c key can be found amongst
            the attributes; else \c false is returned.
  */
  bool Image::attribute (std::string &value,
			 std::string const &key)
  {
    std::map<std::string,std::string>::iterator it = itsAttributes.find(key);

    if (it==itsAttributes.end()) {
      value = "";
      return false;
    } else {
      value = it->second;
      return true;
    }
  }

  //____________________________________________________________________________
  //                                                                setAttribute

  /*!
    \param key       -- 
    \param value     -- 
    \param overwrite -- 
    \return status   -- 
  */
  bool Image::setAttribute (std::string const &key,
			    std::string const &value,
			    bool const &overwrite)
  {
    if (hasAttribute(key) && overwrite) {
      return false;
    } else {
      itsAttributes[key] = value;
    }
    return true;
  }

}  //  namespace prometheus -- END

