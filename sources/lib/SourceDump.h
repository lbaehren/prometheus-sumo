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

#ifndef SOURCEDUMP_H
#define SOURCEDUMP_H

#include <exception>
#include <iostream>
#include <map>
#include <string>

#include <boost/foreach.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "Image.h"

/*!
  \file SourceDump.h
  \class SourceDump
  \ingroup prometheus
  \brief Base class for source dump
  \author Lars Baehren
*/

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  class SourceDump : public Image {

  protected:
    
    //! Name of the root node in the XML file
    std::string itsRootNode;
    //! Name of the node containing attributes of an image
    std::string itsImageNode;
    
  public:

    //! Argumented constructor
    SourceDump (std::string const &rootNode="root",
                std::string const &imageNode="row");
    
    //! Argumented constructor
    SourceDump (std::string const &rootNode,
                std::string const &imageNode,
		std::map<std::string,std::string> const &attributes);
    
    // === Parameter access ====================================================
    
    //! Get the name of the root node in the XML file
    inline std::string rootNode () const {
      return itsRootNode;
    }

    //! Get the name of the node containing attributes of an image
    inline std::string imageNode () const {
      return itsImageNode;
    }

    //! Get map with the mappingof attribute names
    inline std::map<std::string,std::string> attributesMap () const {
      return itsAttributes;
    }

    //! Get the attribute keywords attached to the image
    std::set<std::string> attributeKeys ();
    
    // === Public methods ======================================================

    //! Read data from XML dump of database
    int readXML (std::istream & infile,
                 std::vector<Image> &images);

    //! Provide a summary of the object's internal parameters and status
    inline void summary () {
      summary (std::cout);
    }

    //! Provide a summary of the object's internal parameters and status
    void summary (std::ostream &os);

  };
  
}  //  namespace prometheus -- END

#endif
