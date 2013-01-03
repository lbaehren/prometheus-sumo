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
  \brief A collection of tests for the prometheus::config::Package class
  \author Lars Baehren
  \date 2012-12-06
*/

#include <Config/Package.h>

//_______________________________________________________________________________
//                                                              test_construction

/*!
  \brief Test constructors for a new object
  \param attributes -- Map with a attributes for the package.
  \return status    -- Returns non-zero value in case an error was encountered.
*/
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

//_______________________________________________________________________________
//                                                                test_parameters

/*!
  \brief Test access to the internal attributes of an object.
  \param attributes -- Map with a attributes for the package.
  \return status    -- Returns non-zero value in case an error was encountered.
*/
int test_parameters (std::map<std::string,std::string> const &attributes)
{
  std::cout << "\n[testPackage::test_parameters]\n" << std::endl;

  int status = 0;

  std::cout << "[1] Testing Package::set() ..." << std::endl;
  try {
    prometheus::config::Package package;
    std::map<std::string,std::string> attr = attributes;
    std::map<std::string,std::string>::iterator it;

    for (it=attr.begin(); it!=attr.end(); ++it) {
      std::cout << "-- set(" << it->first << ")" << std::endl;
      package.set(it->first, it->second);
    }
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[2] Testing parameter access shortcuts ..." << std::endl;
  try {
    // Create object ...
    prometheus::config::Package package (attributes);
    // ... and get internal data
    std::cout << "-- name()    => "  << package.name()           << std::endl;
    std::cout << "-- version() => '" << package.version() << "'" << std::endl;
    std::cout << "-- source()  => "  << package.source()         << std::endl;
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[1] Testing generic access methods ..." << std::endl;
  try {
    std::string tmp;
    prometheus::config::Package package (attributes);

    if (package.get(tmp,"name")) {
      std::cout << "-- name    = " << tmp << std::endl;
    }

    if (package.get(tmp,"version")) {
      std::cout << "-- version = '" << tmp << "'" << std::endl;
    }

    if (package.get(tmp,"source")) {
      std::cout << "-- source  = " << tmp << std::endl;
    }

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
  status += test_parameters (attributes);

  return status;
}
