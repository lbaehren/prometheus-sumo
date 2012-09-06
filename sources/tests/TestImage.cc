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
#include <Image.h>

//______________________________________________________________________________
//                                                             test_construction

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
    std::cout << "[TestImage] ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[2] Testing Image(std::map<string,string>) ..." << std::endl;  
  try {
    prometheus::Image img (attributes);
    img.summary();
  } catch (std::exception &e) {
    std::cout << "[TestImage] ERROR : " << e.what() << std::endl;
    ++status;
  }
  
  return status;
}

//______________________________________________________________________________
//                                                               test_attributes

int test_attributes (std::map<std::string,std::string> &attributes)
{
  std::cout << "\n[TestImage::test_attributes]\n" << std::endl;

  int status = 0;

  prometheus::Image img (attributes);
  img.summary();  
  
  /* Set additional attributes */
  try {
    img.setAttribute("object","Recording");
    img.setAttribute("city","Cologne");
    img.setAttribute("country","Germany");
    img.summary();
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

