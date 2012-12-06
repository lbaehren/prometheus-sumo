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
  \file testPackage.cc
  \ingroup prometheus
  \ingroup tests
  \author Lars Baehren
  \date 2012-12-06
*/

#include <Config/Package.h>

int test_construction (std::map<std::string,std::string> const &attributes)
{
  std::cout << "\n[testPackage::test_construction]\n" << std::endl;

  int status = 0;

  std::cout << "[1] Testing Package() ..." << std::endl;
  try {
    prometheus::config::Package package;
    package.summary();
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[2] Testing Package(map<string,string>) ..." << std::endl;
  try {
    prometheus::config::Package package (attributes);
    package.summary();
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  return status;
}

// === Test program main function ===============================================

//! Test program main function
int main (int argc, char* argv[])
{
  int status = 0;

  std::map<std::string,std::string> attributes;
  attributes["name"]    = "ferret";
  attributes["version"] = "= 0.11.8.1";
  attributes["source"]  = "http://prometheus-app.uni-koeln.de/rubygems";

  status += test_construction (attributes);

  return status;
}

