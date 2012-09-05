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
  \file TestXMLBoost.cc
  \ingroup prometheus
  \ingroup tests
  \author Lars Baehren
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>

#include <boost/foreach.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <Sources/Beeskow.h>
#include <Sources/TheolEik.h>

using boost::property_tree::ptree;

// === Functions ===============================================================

//______________________________________________________________________________
//                                                       test_character_encoding

/*!
  \brief Test working with different character encodings
*/
int test_character_encoding ()
{
  std::cout << "\n[TestXMLBoost::test_character_encoding]\n" << std::endl;

  {
    std::string text = "á";
    std::cout << "-- Text size = " << text.size() << std::endl;
    std::cout << "-- Text      = " << text        << std::endl;

    text = "KünstlerIn";
    std::cout << "-- Text size = " << text.size() << std::endl;
    std::cout << "-- Text      = " << text        << std::endl;

  }
  
  return 0;
}

//______________________________________________________________________________
//                                                      read_beeskow_kunstarchiv

/*!
  \brief Read database for Beeskow Kunstarchiv

  \param infile -- Input stream connected to the XML dump for the collection.
  \retval collection -- Array with the items in the colleciton
 */
int read_beeskow_kunstarchiv (std::istream & infile,
                              std::vector<prometheus::source::Beeskow::Attributes> &collection)
{
  std::cout << "\n[TestXMLBoost::read_beeskow_kunstarchiv]\n" << std::endl;
  
  ptree pt;

  std::cout << "-- Reading XML input file ..." << std::endl;
  read_xml(infile, pt);

  std::cout << "-- Parsin XML document ..." << std::endl;
  BOOST_FOREACH( ptree::value_type const& v, pt.get_child("root") ) {
    if( v.first == "row" ) {
      prometheus::source::Beeskow::Attributes r;
      // r.artist   = v.second.get<std::string>("KünstlerIn");
      r.location = v.second.get<std::string>("Standort");
      r.title    = v.second.get<std::string>("Titel");
      r.date     = v.second.get<std::string>("Datierung");
      r.category = v.second.get<std::string>("Gattung");
      r.units    = v.second.get<std::string>("Einheit");
      r.object   = v.second.get<unsigned int>("Ob_f41");
      // r.height   = v.second.get<std::string>("Höhe");
      r.width    = v.second.get<std::string>("Breite");
      collection.push_back(r);
    }
  }

  return 0;
}

//______________________________________________________________________________
//                                                                 read_theoleik

/*!
  \brief Read database for Institut für Evangelische Theologie

  \param infile -- Input stream connected to the XML dump for the collection.
  \retval collection -- Array with the items in the colleciton
 */
int read_theoleik (std::istream & infile,
                   std::vector<prometheus::source::TheolEik::Attributes> &collection)
{
  ptree pt;

  std::cout << "-- Reading XML input file ..." << std::endl;
  read_xml(infile, pt);

  std::cout << "-- Parsin XML document ..." << std::endl;
  BOOST_FOREACH( ptree::value_type const& v, pt.get_child("dataroot") ) {
    if( v.first == "row" ) {
      prometheus::source::TheolEik::Attributes node;
      node.location = v.second.get<std::string>("Standort");
      node.title    = v.second.get<std::string>("Titel");
      node.date     = v.second.get<std::string>("Datierung");
      node.category = v.second.get<std::string>("Gattung");
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

  /*
   *  Test with no further external data required
   */
  
  status += test_character_encoding ();

  /*
   *  Test using external datasets
   */
  
  /* Parse command line parameters */
  if ( argc>1 ) {
    /* Get the name of the testdata ... */
    filename = std::string(argv[1]);
    /* ... and run the actual tests. */
    std::ifstream infile (filename.c_str());
    
    if (infile.is_open()) {

      std::vector<prometheus::source::Beeskow::Attributes> collection;

      /* Parse the contents of the document */
      read_beeskow_kunstarchiv (infile, collection);

      /* Summary of document contents */
      std::cout << "-- nof. collection items = " << collection.size() << std::endl;
      for (unsigned int n=0; n<collection.size(); ++n) {
	std::cout << " --> " << collection[n].title
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
