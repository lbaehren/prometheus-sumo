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

#include "SourceDump.h"

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  // ===========================================================================
  //
  //  Construction
  //
  // ===========================================================================
  
  /*!
    \param rootNode  -- Name of the root node in the XML file.
    \param imageNode -- Name of the node containing attributes of an image
  */
  SourceDump::SourceDump (std::string const &rootNode,
                          std::string const &imageNode)
    : itsRootNode (rootNode),
      itsImageNode (imageNode)
  {
    init();
  }

  // ===========================================================================
  //
  //  Parameter access
  //
  // ===========================================================================

  //____________________________________________________________________________
  //                                                               attributeKeys

  std::set<std::string> SourceDump::attributeKeys ()
  {
    std::map<std::string,std::string>::iterator it;
    std::set<std::string> keys;

    for (it=itsAttributes.begin();it!=itsAttributes.end(); ++it) {
      keys.insert(it->first);
    }
    return keys;
  }

  // ===========================================================================
  //
  //  Public methods
  //
  // ===========================================================================

  //____________________________________________________________________________
  //                                                                     readXML

  int SourceDump::readXML (std::istream & infile,
                           std::vector<Image> &images)
  {
    boost::property_tree::ptree pt;

    /* Try reading data from input stream */
    try {
      read_xml(infile, pt);
    } catch (std::exception &e) {
      std::cout << "[SourceDump::readXML] ERROR : " << e.what() << std::endl;
      return -1;
    }
    
    /* Local variables */
    int status = 0;
    std::map<std::string,std::string>::iterator it;
    std::string buffer;

    /* Iterate through the document */
    BOOST_FOREACH (boost::property_tree::ptree::value_type const& v,
                   pt.get_child(itsRootNode) ) {
      if( v.first == itsImageNode ) {
        Image image;
        /* Iterate through the attributes expected in the image group */
        for (it=itsAttributes.begin(); it!=itsAttributes.end(); ++it) {
          /* Try to read the attribute */
          try {
            buffer = v.second.get<std::string>(it->second);
          } catch (std::exception &e) {
            buffer = "";
          }
          /* Store attribute value */
          image.setAttribute(it->first,buffer);
        }
      }
    }
    
    return status;
  }

  //____________________________________________________________________________
  //                                                                     summary

  /*!
    \param os -- Output stream to which the summary will be written.
  */
  void SourceDump::summary (std::ostream &os)
  {
    os << "[SourceDump] Summary of internal parameters" << std::endl;
    os << "-- Name of root node  = " << itsRootNode     << std::endl;
    os << "-- Name of image node = " << itsImageNode    << std::endl;
    os << "-- Attribute keywords = " << attributeKeys() << std::endl;
  }

  // ===========================================================================
  //
  //  Private methods
  //
  // ===========================================================================

  void SourceDump::init ()
  {
    itsAttributes.clear();

    itsAttributes["title"]    = "title";
    itsAttributes["artist"]   = "artist";
    itsAttributes["date"]     = "date";
    itsAttributes["location"] = "location";
    itsAttributes["credits"]  = "credits";
  }
  
  
}  //  namespace prometheus -- END
