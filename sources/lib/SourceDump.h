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
#include <map>
#include <string>

#include <boost/foreach.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

/*!
  \file SourceDump.h
  \class SourceDump
  \ingroup prometheus
  \brief Base class for source dump
  \author Lars Baehren
*/

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  class SourceDump {

  protected:
    
    std::string itsRootNode;
    std::string itsImageNode;
    //! List of attributes (and their potential mapping)
    std::map<std::string,std::string> itsAttributes;
    
  public:
    
    // === Parmater access ======================================================
    
    //! Get map with the mappingof attribute names
    inline std::map<std::string,std::string> attributesMap () const {
      return itsAttributes;
    }

    // === Public methods =======================================================
    
    /*!
      \brief Read in data from XML dump
      \param filename -- Name of the file with the XML dump of the database.
      \return status  -- Status of the operation; returns \c false in case an
              error was encountered.
    */
    virtual bool readXML (std::string const &filename) = 0;
    
    // === Private methods ======================================================
    
  private:
  
    //! Initialize internal attributes
    void init ();
    
  };
  
}  //  namespace prometheus -- END

#endif
