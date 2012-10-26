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

#include <iomanip>
#include <Config/Gems.h>

/*!
  \file testConfigGems.cc
  \ingroup prometheus
  \ingroup tests
  \brief A collection of tests for the prometheus::config::Gems class
  \author Lars Baehren
*/

// === Test procedures ==========================================================

//_______________________________________________________________________________
//                                                              test_constructors

/*!
  \brief Test constructors for a new object
  \param filename -- Name of the configuration file.
  \return status  -- Returns non-zero value in case an error was encountered.
*/
int test_constructors (std::string const &filename="ruby_gems.yml")
{
  std::cout << "\n[testGems::test_constructors]\n" << std::endl;

  int status = 0;

  std::cout << "[1] Testing Gems() ..." << std::endl;
  try {
    prometheus::config::Gems gems;
    //
    std::cout << "--> Config file = " << gems.configFile() << std::endl;
    std::cout << "--> nof. gems   = " << gems.nofGems()    << std::endl;
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[2] Testing Gems(std::string) ..." << std::endl;
  try {
    prometheus::config::Gems gems (filename);
    //
    std::cout << "--> Config file = " << gems.configFile() << std::endl;
    std::cout << "--> nof. gems   = " << gems.nofGems()    << std::endl;
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  return status;
}

//_______________________________________________________________________________
//                                                              test_constructors

/*!
  \brief Test reading list of Ruby gems from configuration file
*/
int test_read_config (std::string const &filename)
{
  std::cout << "\n[testGems::test_read_config]\n" << std::endl;

  int status = 0;
  prometheus::config::Gems gems;

  std::cout << "[1] Testing Gems::readConfig(std::string) ..." << std::endl;
  try {
    gems.readConfig(filename);
    gems.summary();
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[2] Testing Gems::names() ..." << std::endl;
  try {
    // Get the names of the gems ...
    std::set<std::string> names = gems.names();
    // ... and print them
    std::cout << "--> nof. gems = " << names.size() << std::endl;
    std::cout << "--> Gem names = " << names        << std::endl;
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[3] Testing Gems::versions() ..." << std::endl;
  try {
    std::map<std::string,std::string>::iterator it;
    // Get the names of the gems ...
    std::map<std::string,std::string> versions = gems.versions();
    // ... and print them
    std::cout << "--> nof. gems = " << versions.size() << std::endl;
    for (it=versions.begin();it!=versions.end();++it) {
      std::cout << std::setw(25) << it->first << "  :  " << it->second << std::endl;
    }
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[4] Testing Gems::urls() ..." << std::endl;
  try {
    std::map<std::string,std::string>::iterator it;
    // Get the names of the gems ...
    std::map<std::string,std::string> urls = gems.urls();
    // ... and print them
    std::cout << "--> nof. gems = " << urls.size() << std::endl;
    for (it=urls.begin();it!=urls.end();++it) {
      std::cout << std::setw(25) << it->first << "  :  " << it->second << std::endl;
    }
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  return status;
}

// === Program main function ====================================================

//! Program main function
int main (int argc, char **argv)
{
  int status       = 0;
  bool haveDataset = false;

  if (argc >1) {
    status += test_constructors (argv[1]);
    status += test_read_config (argv[1]);
  } else {
    status += test_constructors ();
  }

  return status;
}
