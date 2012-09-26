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

#include <iostream>
#include <string>

#include <tinyxml2.h>

using namespace tinyxml2;

/*!
  \file TestXML.cc
  \ingroup prometheus
  \ingroup tests
  \author Lars Baehren
*/

//______________________________________________________________________________
//                                                                test_load_file

/*!
  \brief Test basic XML file loading
  \param filename -- Name of the \ref xml file to load.
*/
int test_load_file (std::string const &filename="resources/dream.xml")
{
  std::cout << "\n[TestXML::test_load_file]\n" << std::endl;

  std::cout << "--> Input file = " << filename << std::endl;

  tinyxml2::XMLDocument doc;
  doc.LoadFile(filename.c_str());

  return doc.ErrorID();
}

//______________________________________________________________________________
//                                                              test_char_buffer

/*!
  \brief Test parsing a simple string stored in character buffer
  \param teststring -- Simple string containing some \ref xml syntax.
  \return status -- Return status of the function; returns non-zero in case an
                    an error is caught.
*/
int test_char_buffer (std::string const &teststring="<element/>")
{
  std::cout << "\n[TestXML::test_char_buffer]\n" << std::endl;

  int status = 0;

  std::cout << "--> Input string = " << teststring << std::endl;

  XMLDocument doc;
  doc.Parse(teststring.c_str());
  status = doc.ErrorID();

  return status;
}

//______________________________________________________________________________
//                                                           test_parse_document

/*!
  \brief Test parsing a XML document
  \param filename -- Name of the \ref xml file to load.
*/
int test_parse_document (std::string const &filename)
{
  std::cout << "\n[TestXML::test_parse_document]\n" << std::endl;

  int status = 0;
  XMLDocument doc;

  /* Load the XML file; LoadFile() returns non-zero value if everything is ok. */
  if (!doc.LoadFile(filename.c_str())) {

    /* Get root node */
    XMLElement * elemRoot = doc.RootElement();
    std::cout << "-- Root element = " << elemRoot->Name() << std::endl;

  } else {
    std::cerr << "[ERROR] Failed to load file " << filename << std::endl;
    status += 1;
  }

  return status;
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
   *  Test without the need of external data
   */
  status += test_char_buffer();

  /*
   *  Test working with external dataset
   */
  if ( argc>1 ) {
    filename = std::string(argv[1]);
    status += test_load_file(filename);
    status += test_parse_document (filename);
  }

  return status;
}
