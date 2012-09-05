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

/*!
  \file TestSourcesKassel.cc
  \ingroup prometheus
  \ingroup tests
  \author Lars Baehren
 */

#include <Sources/Kassel.h>

using boost::property_tree::ptree;

//______________________________________________________________________________
//                                                                 read_theoleik

/*!
  \brief Read database for Institut für Evangelische Theologie

  \param infile -- Input stream connected to the XML dump for the collection.
  \retval collection -- Array with the items in the colleciton
 */
int read_dump (std::istream & infile,
	       std::vector<prometheus::source::Kassel::Attributes> &collection)
{
  ptree pt;
  
  std::cout << "-- Reading data from input stream ..." << std::endl;
  read_xml(infile, pt);
  
  std::cout << "-- Parsing XML document ..." << std::endl;
  BOOST_FOREACH( ptree::value_type const& v, pt.get_child("dataroot") ) {
    if( v.first == "row" ) {
      prometheus::source::Kassel::Attributes node;
      node.image    = v.second.get<std::string>("bild_nr");
      // node.title    = v.second.get<std::string>("titel");
      // node.artist   = v.second.get<std::string>("kuenstler");
      node.date     = v.second.get<std::string>("datierung");
      // node.object   = v.second.get<std::string>("objekt");
      // node.objectID = v.second.get<std::string>("objekt_id");
      // node.category = v.second.get<std::string>("gattung");
      collection.push_back(node);
    }
  }

  return 0;
}
                              
// === Main function ===========================================================

/*!
  \brief Test program main function
*/
int main(int argc, char* argv[])
{
  int status = 0;
  std::string filename;

  /* Parse command line parameters */
  if ( argc>1 ) {
    /* Get the name of the testdata ... */
    filename = std::string(argv[1]);
    /* ... and run the actual tests. */
    std::ifstream infile (filename.c_str());
    
    if (infile.is_open()) {

      std::cout << "-- Opened input file " << filename << std::endl;

      std::vector<prometheus::source::Kassel::Attributes> collection;

      /* Parse the contents of the document */
      read_dump (infile, collection);

      /* Summary of document contents */
      std::cout << "-- nof. collection items = " << collection.size() << std::endl;
      for (unsigned int n=0; n<collection.size(); ++n) {
	std::cout << " --> " << collection[n].image
		  << " : " << collection[n].title
		  << "\t(" << collection[n].date << ")"
		  << std::endl;
      }

    } else {
      std::cerr << "--> Failed to open file " << filename << std::endl;
      return 1;
    }
  }
  
  return status;
}
