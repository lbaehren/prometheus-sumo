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
  \file TestImage.cc
  \ingroup prometheus
  \ingroup tests
  \author Lars Baehren
 */

#include <map>
#include <set>
#include <Models/Image.h>

//______________________________________________________________________________
//                                                             test_construction

/*!
  \brief Test constructor for a new object
  \return status -- Return status of the function; returns non-zero value in case
                    an error is caught.
*/
int test_construction (std::map<std::string,std::string> const &attributes)
{
  std::cout << "\n[TestImage::test_construction]\n" << std::endl;

  int status           = 0;
  std::string title    = "D'oh!";
  std::string artist   = "Homer Simpson";
  std::string location = "Springfield";

  std::cout << "[1] Testing Image(string,string) ..." << std::endl;
  try {
    prometheus::Image img (title,artist);
    img.summary();
  } catch (std::exception &e) {
    std::cerr << "[TestImage] ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[2] Testing Image(std::map<string,string>) ..." << std::endl;
  try {
    prometheus::Image img (attributes);
    img.summary();
  } catch (std::exception &e) {
    std::cerr << "[TestImage] ERROR : " << e.what() << std::endl;
    ++status;
  }

  return status;
}

//______________________________________________________________________________
//                                                               test_attributes

/*!
  \brief Test access to and manipulation of image attributes
  \return status -- Return status of the function; returns non-zero value in case
                    an error is caught.
*/
int test_attributes (std::map<std::string,std::string> &attributes)
{
  std::cout << "\n[TestImage::test_attributes]\n" << std::endl;

  int status = 0;

  prometheus::Image img (attributes);
  img.summary();

  std::cout << "[1] Testing Image::setAttribute(string,string)" << std::endl;
  try {
    img.setAttribute("object","Recording");
    img.setAttribute("city","Cologne");
    img.setAttribute("country","Germany");
    img.summary();
  } catch (std::exception &e) {
    std::cerr << "[TestImage] ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[2] Testing Image::attribute(string,string)" << std::endl;
  try {
    std::string object  = img.attribute("object");
    std::string city    = img.attribute("city");
    std::string country = img.attribute("country");
    std::string gallery = img.attribute("gallery","UNDEFINED");
    //
    std::cout << "-- Object  = " << object  << std::endl;
    std::cout << "-- City    = " << city    << std::endl;
    std::cout << "-- Country = " << country << std::endl;
    std::cout << "-- Gallery = " << gallery << std::endl;
  } catch (std::exception &e) {
    std::cerr << "[TestImage] ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[3] Testing Image::attribute(string,string)" << std::endl;
  try {
    bool stat;
    std::string object;
    std::string city;
    std::string country;
    std::string gallery;
    //
    stat = img.attribute(object,"object");
    stat = img.attribute(city,"city");
    stat = img.attribute(country,"country");
    stat = img.attribute(gallery,"gallery");
    //
    std::cout << "-- Object  = " << object  << std::endl;
    std::cout << "-- City    = " << city    << std::endl;
    std::cout << "-- Country = " << country << std::endl;
    std::cout << "-- Gallery = " << gallery << std::endl;
  } catch (std::exception &e) {
    std::cerr << "[TestImage] ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[4] Testing Image::hasAttribute(string)" << std::endl;
  try {
    std::cout << "-- Object  = " << img.hasAttribute("object")  << std::endl;
    std::cout << "-- City    = " << img.hasAttribute("city")    << std::endl;
    std::cout << "-- Country = " << img.hasAttribute("country") << std::endl;
    std::cout << "-- Gallery = " << img.hasAttribute("gallery") << std::endl;
  } catch (std::exception &e) {
    std::cout << "[TestImage] ERROR : " << e.what() << std::endl;
    ++status;
  }

  return status;
}

// === Program main function ===================================================

//! Program main function
int main ()
{
  int status = 0;

  std::map<std::string,std::string> attributes;
  attributes["title"]    = "D'oh!";
  attributes["artist"]   = "Homer Simpson";
  attributes["location"] = "Springfield";

  status += test_construction (attributes);
  status += test_attributes (attributes);

  return status;
}

