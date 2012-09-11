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

#include "Robertinum.h"

namespace prometheus {  //  namespace prometheus -- BEGIN

  namespace source {  //  namespace source -- BEGIN

    // ==========================================================================
    //
    //  Construction
    //
    // ==========================================================================

    Robertinum::Robertinum (std::string const &rootNode,
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
    int Robertinum::readXML (std::istream & infile,
			     std::vector<Robertinum::Attributes> &items)
    {
      boost::property_tree::ptree pt;

      try {
	read_xml(infile, pt);
      } catch (std::exception &e) {
	std::cout << "[Robertinum::readXML] ERROR : " << e.what() << std::endl;
	return -1;
      }

      int status      = 0;
      bool incomplete = false;

      BOOST_FOREACH( boost::property_tree::ptree::value_type const& v, pt.get_child(itsRootNode) ) {
	if( v.first == itsImageNode ) {
	  Robertinum::Attributes node;
	
	  incomplete = false;
	
	  node.missingAttributes = false;
	  node.path           = v.second.get<std::string>("grossbildnummer");
	  node.artist         = v.second.get<std::string>("werkstatt");
	  node.title          = v.second.get<std::string>("titel");
	  node.date           = v.second.get<std::string>("datierung");
	  node.genre          = v.second.get<std::string>("form");
	  node.location       = v.second.get<std::string>("standort");
	  node.discoveryplace = v.second.get<std::string>("fundort");
	  node.credits        = v.second.get<std::string>("bildrecht");

	  if (incomplete) ++status;
	  items.push_back(node);
	}
      }

      return status;
    }

  }   //  namespace source -- END

}  //  namespace prometheus -- END
