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

#include "Beeskow.h"

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  namespace source {

    // ==========================================================================
    //
    //  Construction
    //
    // ==========================================================================

    Beeskow::Beeskow (std::string const &rootNode,
                      std::string const &imageNode)
      : SourceDump (rootNode,imageNode)
    {
      init ();
    }

    // ==========================================================================
    //
    //  Public methods
    //
    // ==========================================================================

    /*!
      \param infile  -- Input stream connected to the XML dump for the
                     collection.
      \retval items  -- Array with the items listed in the database dump.
      \return status -- Indicator for status of internal operation: returns
                     \c -1 in case there was an error reading from the input stream,
		     \c N for the number of incomplete datasets (i.e. missing
		     attributes) and \c 0 otherwise.
    */
    int Beeskow::readXML (std::istream & infile,
                          std::vector<Beeskow::Attributes> &items)
    {
      boost::property_tree::ptree pt;
      
      try {
        read_xml(infile, pt);
      } catch (std::exception &e) {
        std::cout << "[Beeskow::readXML] ERROR : " << e.what() << std::endl;
        return -1;
      }
      
      int status      = 0;
      bool incomplete = false;
      
      BOOST_FOREACH( boost::property_tree::ptree::value_type const& v, pt.get_child("root") ) {
        if( v.first == "row" ) {
          Beeskow::Attributes node;

          incomplete = false;
          node.missingAttributes = false;

	  node.location = v.second.get<std::string>("Standort");
	  node.title    = v.second.get<std::string>("Titel");
	  node.date     = v.second.get<std::string>("Datierung");
	  node.category = v.second.get<std::string>("Gattung");
	  node.units    = v.second.get<std::string>("Einheit");
	  node.material = v.second.get<std::string>("Material");
	  node.object   = v.second.get<unsigned int>("Ob_f41");

          if (incomplete) ++status;
          items.push_back(node);
	}
      }

      return status;
    }
    
    // ==========================================================================
    //
    //  Private methods
    //
    // ==========================================================================

    void Beeskow::init ()
    {
      itsAttributes["location"] = "Standort";
      itsAttributes["title"]    = "Titel";
      itsAttributes["date"]     = "Datierung";
      itsAttributes["category"] = "Gattung";
    }
    
  }   //  namespace source -- END
  
}  //  namespace prometheus -- END
