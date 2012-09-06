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

// === Main function ===========================================================

/*!
  \brief Test program main function
*/
int main(int argc, char* argv[])
{
  std::string filename;

  /* Parse command line parameters */
  if ( argc>1 ) {
    /* Get the name of the testdata ... */
    filename = std::string(argv[1]);
    /* ... and run the actual tests. */
    std::ifstream infile (filename.c_str());
    
    if (infile.is_open()) {

      std::cout << "-- Opened input file " << filename << std::endl;

      prometheus::source::Kassel dump;
      std::vector<prometheus::source::Kassel::Attributes> items;
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
                  << " : " <<items[n].missingAttributes
                  << " : " <<items[n].image
                  << " : " << items[n].title
                  << "\t(" << items[n].date << ")"
                  << std::endl;
      }
      std::cout << "-- nof. items      = " << items.size()       << std::endl;
      std::cout << "-- nof. incomplete = " << nofIncompleteItems << std::endl;

    } else {
      std::cerr << "--> Failed to open file " << filename << std::endl;
      return 1;
    }
  }
  
  return 0;
}
