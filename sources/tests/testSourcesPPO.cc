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
  \file testSourcesPPO.cc
  \ingroup prometheus
  \ingroup tests
  \author Lars Baehren
 */

#include <Sources/PPO.h>

using boost::property_tree::ptree;

// ==============================================================================
//
//  Test routines
//
// ==============================================================================

//_______________________________________________________________________________
//                                                        test_read_ids_from_file

/*!
  \brief Test reading image IDs from file.
  \param filename -- Name of the file containing the list of image IDs.
*/
int test_read_ids_from_file (std::string const &filename)
{
  int status = 0;

  return status;
}

//_______________________________________________________________________________
//                                                             test_read_xml_dump

/*!
  \brief Test reading in data from XML database dump
  \param filename -- Name of the file with the XML data.
*/
int test_read_xml_dump (std::string const &filename)
{
  int status = 0;
  std::ifstream infile (filename.c_str());

  if (infile.is_open()) {

    std::cout << "-- Opened input file " << filename << std::endl;

    prometheus::source::PPO dump;
    std::vector<prometheus::Image> items;
    int nofIncompleteItems = 0;

    /* Parse the contents of the document */
    try {
      nofIncompleteItems = dump.readXML (infile, items);
    } catch (std::exception &e) {
      std::cout << "[ERROR] " << e.what() << "\n";
    }

    /* Summary of document contents */
    for (unsigned int n=0; n<items.size(); ++n) {
      std::cout << "[" << n << "]"
		<< " : " <<items[n].attribute("image")
		<< " : " << items[n].attribute("title")
		<< "\t(" << items[n].attribute("date") << ")"
		<< std::endl;
    }
    std::cout << "-- nof. items      = " << items.size()       << std::endl;
    std::cout << "-- nof. incomplete = " << nofIncompleteItems << std::endl;

  } else {
    std::cerr << "--> Failed to open file " << filename << std::endl;
    return 1;
  }

  return status;
}

// ==============================================================================
//
//  Program main function
//
// ==============================================================================

/*!
  \brief Test program main function
*/
int main(int argc, char* argv[])
{
  int status = 0;
  std::string filename;

  /* Parse command line parameters */
  if ( argc>1 ) {

    filename = std::string(argv[1]);

    /* Test reading in data from XML database dump */
    status += test_read_xml_dump (filename);
  }

  return status;
}
