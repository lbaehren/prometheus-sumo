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

#include <iostream>
#include <string>
#include <vector>

#include "Common.h"

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  /*!
    \file Image.h
    \class Image
    \ingroup prometheus
    \brief An image
    \author Lars Baehren
    \date 2012-09-03
  */
  class Image {

    // === Private data ========================================================

    //! Title of the image
    std::string itsTitle;
    //! Artist for the image
    std::string itsArtist;
    //! (Creation) Date of the image
    std::string itsDate;
    //! Location of the image
    std::string itsLocation;
    //! Credits for the image
    std::string itsCredits;
    //! Path name for the image
    std::string itsPath;

    // === Private methods =====================================================

  public:

    // === Construction ========================================================

    //! Argumented constructor
    Image (std::string const &title,
           std::string const &artist);

    // === Parameter access ====================================================

    //! Get the title of the image
    inline std::string title () const {
      return itsTitle;
      }
    //! Set the title of the image
    inline void setTitle (std::string const &title) {
      itsTitle = title;
      }

    //! Get the artist for the image
    inline std::string artist () const {
      return itsArtist;
      }
    //! Set the artist for the image
    inline void setArtist (std::string const &artist) {
      itsArtist = artist;
      }

    //! Get the (creation) date of the image
    inline std::string date () const {
      return itsDate;
      }
    //! Set the (creation) date of the image
    inline void setDate (std::string const &date) {
      itsDate = date;
      }

    //! Get the location of the image
    inline std::string location () const {
      return itsLocation;
      }
    //! Set the location of the image
    inline void setLocation (std::string const &location) {
      itsLocation = location;
      }

    //! Get the credits for the image
    inline std::string credits () const {
      return itsCredits;
      }
    //! Set the credits for the image
    inline void setCredits (std::string const &credits) {
      itsCredits = credits;
      }

    //! Get the path name for the image
    inline std::string path () const {
      return itsPath;
      }
    //! Set the path name for the image
    inline void setPath (std::string const &path) {
      itsPath = path;
      }

    // === Public methods ======================================================


    // === Static methods ======================================================
    
    // === Private methods =====================================================
    
  private:
    
    void init ();

  };
  
}  //  namespace prometheus -- END

#endif

