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

#include "TheolEik.h"

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  namespace source {  //  namespace source -- BEGIN
    
    int TheolEik::readXML (std::istream & infile,
                           std::vector<TheolEik::Attributes> &items)
    {
      boost::property_tree::ptree pt;
      
      try {
        read_xml(infile, pt);
      } catch (std::exception &e) {
        std::cout << "[TheolEik::readXML] ERROR : " << e.what() << std::endl;
        return -1;
      }
      
      int status      = 0;
      bool incomplete = false;
      
      BOOST_FOREACH( boost::property_tree::ptree::value_type const& v, pt.get_child("dataroot") ) {
        if( v.first == "row" ) {
        TheolEik::Attributes node;

        incomplete = false;
        node.missingAttributes = false;

        node.image    = v.second.get<std::string>("bildreferenz");
        node.location = v.second.get<std::string>("standort");
        node.title    = v.second.get<std::string>("titel");
        node.date     = v.second.get<std::string>("datierung");
        node.category = v.second.get<std::string>("gattung");
        node.keyword  = v.second.get<std::string>("schlagwort");
        node.artist   = v.second.get<std::string>("kuenstlerin");

	    if (incomplete) ++status;
	    items.push_back(node);
	  }
	}
	
	return status;
    }
    
  };  //  namespace source -- END

}  //  namespace prometheus -- END

