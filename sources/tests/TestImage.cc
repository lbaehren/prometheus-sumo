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

#include <Image.h>

int test_construction (std::map<std::string,std::string> const &attributes)
{
  std::cout << "[TestImage::test_construction]" << std::endl;

  int status = 0;
  
  try {
    prometheus::Image img (attributes);
  } catch (std::exception &e) {
    std::cout << "[TestImage] ERROR : " << e.what() << std::endl;
    ++status;
  }
  
  return status;
}

// === Program main function ====================================================

int main ()
{
  int status = 0;
  
  std::string title    = "D'oh!";
  std::string artist   = "Homer Simpson";
  std::string location = "Springfield";

  std::map<std::string,std::string> attributes;
  attributes["title"]    = "D'oh!";
  attributes["artist"]   = "Homer Simpson";
  attributes["location"] = "Springfield";

  // === Test 1
  
  try {
    prometheus::Image img (title,artist);
  } catch (std::exception &e) {
    std::cout << "[TestImage] ERROR : " << e.what() << std::endl;
    ++status;
  }

  status += test_construction (attributes);
  
  return status;
}
