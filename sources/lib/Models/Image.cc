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
    init();

    std::map<std::string,std::string> buffer = attributes;
    std::map<std::string,std::string>::iterator it;

    for (it=buffer.begin(); it!=buffer.end(); ++it) {
      itsAttributes[it->first] = it->second;
    }

  }

  // ===========================================================================
  //
  //  Public methods
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
    \param key            -- Keyword to be searched for amongst the attributes.
    \param unsetIndicator -- String to be returned in case the key could not be
                          found amongst the image attributes; since returning an
                          empty string as value could be considered a valid
                          answer, a custom reply can be defined to indicate the
                          case where the attribute is not set/available.
    \retval value  -- Value of the attribute indicated by \c key.
  */
  std::string Image::attribute (std::string const &key,
                                std::string const &unsetIndicator)
  {
    std::string val;

    if (attribute(val,key)) {
      return val;
    } else {
      val = unsetIndicator;
      return val;
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
    \param key       -- Keyword for the attribute.
    \param value     -- Value of the attribute.
    \param overwrite -- Overwrite existing entry if it exists?
    \return status   -- Feedback on whether or not a new value for the attribute
                     has been set; if the attribute has been set already and
                     \c overwrite=false, then the provided \c value is not going
                     to be stored.
  */
  bool Image::setAttribute (std::string const &key,
                            std::string const &value,
                            bool const &overwrite)
  {
    if (hasAttribute(key) && !overwrite) {
      return false;
    } else {
      itsAttributes[key] = value;
    }
    return true;
  }

  //____________________________________________________________________________
  //                                                                     summary

  /*!
    \param os -- Output stream to which the summary will be written.
  */
  void Image::summary (std::ostream &os)
  {
    os << "[Image] Summary of internal parameters" << std::endl;
    os << "-- Attribute keywords = " << attributeKeys() << std::endl;

    std::map<std::string,std::string>::iterator it;
    for (it=itsAttributes.begin(); it!=itsAttributes.end(); ++it) {
      std::cout << "  --> " << it->first << "\t= " << it->second<< std::endl;
    }
  }


}  //  namespace prometheus -- END
