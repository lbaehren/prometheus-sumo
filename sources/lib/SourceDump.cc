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

  //____________________________________________________________________________
  //                                                                  SourceDump

  /*!
    \param rootNode  -- Name of the root node in the XML file.
    \param imageNode -- Name of the node containing attributes of an image
  */
  SourceDump::SourceDump (std::string const &rootNode,
                          std::string const &imageNode)
    : Image(),
      itsRootNode (rootNode),
      itsImageNode (imageNode)
  {;}

  //____________________________________________________________________________
  //                                                                  SourceDump

  /*!
    \param rootNode   -- Name of the root node in the XML file.
    \param imageNode  -- Name of the node containing attributes of an image
    \param attributes -- Attributes attached to/describing the images in the
           database dump.
  */
  SourceDump::SourceDump (std::string const &rootNode,
			  std::string const &imageNode,
			  std::map<std::string,std::string> const &attributes)
    : Image(attributes),
      itsRootNode (rootNode),
      itsImageNode (imageNode)
  {;}

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
#ifdef WITH_BOOST
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
        /* Add image to the list returned */
        images.push_back(image);
      }
    }

    return status;
#else
    return -1;
#endif
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
  //  Static methods
  //
  // ===========================================================================

  //___________________________________________________________________________
  //                                                                  sourceIDs
  
  /*!
    \param filename -- Name of the file containing the source IDs.
    \param match    -- Matching pattern to distinguish source IDs from possible
                       other contents found within the input file.
    \return items   -- Array with the source IDs.
  */
  std::vector<std::string> SourceDump::sourceIDs (std::string const &filename,
						  std::string const &match)
  {
    std::vector<std::string> items;
    std::string buffer;
    std::ifstream infile (filename.c_str());

#ifdef WITH_BOOST
    boost::regex ex (match);
    
    if ( infile.is_open() ) {
      while (infile.good()) {
	// Read line from file into buffer ...
	std::getline (infile, buffer);
	// ... and check it against the matching pattern
	if (boost::regex_search(buffer, ex)) {
	  items.push_back(buffer);
	}
      }
    }
#else
    std::cerr << "[SourceDump::sourceIDs]"
	      << " Unable to perform pattern matching - missing Boost library!"
	      << std::endl;
#endif
    
    return items;
  }
  
}  //  namespace prometheus -- END
