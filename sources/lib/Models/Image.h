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

#ifndef IMAGE_H
#define IMAGE_H

#include "Common.h"

namespace prometheus {  //  namespace prometheus -- BEGIN

  /*!
    \file Image.h
    \class Image
    \ingroup prometheus
    \brief An image
    \author Lars Baehren
    \date 2012-09-03
    \test TestImage.cc
  */
  class Image {

  protected:

    //! Attributes attached to/describing the image
    std::map<std::string,std::string> itsAttributes;

  public:

    // === Construction ========================================================

    //! Default constructor
    Image () {
      init();
    }

    //! Argumented constructor
    Image (std::string const &title,
           std::string const &artist);

    //! Argumented constructor
    Image (std::map<std::string,std::string> const &attributes);

    // === Parameter access ====================================================

    //! Get the value of an attribute attached to the image
    std::string attribute (std::string const &key,
                           std::string const &unsetIndicator="");

    //! Get the value of an attribute attached to the image
    bool attribute (std::string &value,
                    std::string const &key);

    //! Set the value of an attribute attached to the image
    bool setAttribute (std::string const &key,
                       std::string const &value,
                       bool const &overwrite=true);

    // === Public methods ======================================================

    //! Get the attributes attached to/describing the image
    inline std::map<std::string,std::string> attributes () const {
      return itsAttributes;
    }

    //! Get the attribute keywords attached to the image
    std::set<std::string> attributeKeys ();

    //! Is the attribute defined for the image?
    bool hasAttribute (std::string const &key);

    //! Provide a summary of the object's internal parameters and status
    inline void summary () {
      summary (std::cout);
    }

    //! Provide a summary of the object's internal parameters and status
    void summary (std::ostream &os);

    // === Private methods =====================================================

  private:

    //! Initialize internal parameters
    void init ()
    {
      itsAttributes.clear();
      itsAttributes["title"]       = "";
      itsAttributes["artist"]      = "";
      itsAttributes["location"]    = "";
      itsAttributes["credits"]     = "";
      itsAttributes["location"]    = "";
      itsAttributes["category"]    = "";
      itsAttributes["object"]      = "";
      itsAttributes["genre"]       = "";
      itsAttributes["comment"]     = "";
      itsAttributes["annotation"]  = "";
      itsAttributes["size"]        = "";
    }

  };

}  //  namespace prometheus -- END

#endif
