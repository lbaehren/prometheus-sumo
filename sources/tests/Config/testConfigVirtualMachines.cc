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
#include <Config/VirtualMachines.h>

/*!
  \file testConfigVirtualMachines.cc
  \ingroup prometheus
  \ingroup tests
  \brief A collection of tests for the prometheus::config::VirtualMachines class
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
int test_constructors (std::string const &filename="virtual_machines.yml")
{
  std::cout << "\n[testVirtualMachines::test_constructors]\n" << std::endl;

  int status = 0;

  std::cout << "[1] Testing VirtualMachines() ..." << std::endl;
  try {
    prometheus::config::VirtualMachines packages;
    //
    std::cout << "--> Config file = " << packages.configFile() << std::endl;
    std::cout << "--> nof. packages   = " << packages.size()    << std::endl;
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[2] Testing VirtualMachines(std::string) ..." << std::endl;
  try {
    prometheus::config::VirtualMachines packages (filename);
    //
    std::cout << "--> Config file = " << packages.configFile() << std::endl;
    std::cout << "--> nof. packages   = " << packages.size()    << std::endl;
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  return status;
}

//_______________________________________________________________________________
//                                                              test_constructors

/*!
  \brief Test reading list of Ruby packages from configuration file
*/
int test_read_config (std::string const &filename)
{
  std::cout << "\n[testVirtualMachines::test_read_config]\n" << std::endl;

  int status = 0;
  prometheus::config::VirtualMachines packages;

  std::cout << "[1] Testing VirtualMachines::readConfig(std::string) ..." << std::endl;
  try {
    packages.readConfig(filename);
    packages.summary();
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[2] Testing VirtualMachines::names() ..." << std::endl;
  try {
    // Get the names of the packages ...
    std::set<std::string> names = packages.names();
    // ... and print them
    std::cout << "--> nof. packages = " << names.size() << std::endl;
    std::cout << "--> Package names = " << names        << std::endl;
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[3] Testing VirtualMachines::uuids() ..." << std::endl;
  try {
    std::map<std::string,std::string>::iterator it;
    // Get the names of the packages ...
    std::map<std::string,std::string> uuids = packages.uuids();
    // ... and print them
    std::cout << "--> nof. packages = " << uuids.size() << std::endl;
    for (it=uuids.begin();it!=uuids.end();++it) {
      std::cout << std::setw(25) << it->first << "  :  " << it->second << std::endl;
    }
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[4] Testing VirtualMachines::importNames() ..." << std::endl;
  try {
    std::map<std::string,std::string>::iterator it;
    // Get the names of the packages ...
    std::map<std::string,std::string> importNames = packages.importNames();
    // ... and print them
    std::cout << "--> nof. packages = " << importNames.size() << std::endl;
    for (it=importNames.begin();it!=importNames.end();++it) {
      std::cout << std::setw(25) << it->first << "  :  " << it->second << std::endl;
    }
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[5] Testing VirtualMachines::exportNames() ..." << std::endl;
  try {
    std::map<std::string,std::string>::iterator it;
    // Get the names of the packages ...
    std::map<std::string,std::string> exportNames = packages.exportNames();
    // ... and print them
    std::cout << "--> nof. packages = " << exportNames.size() << std::endl;
    for (it=exportNames.begin();it!=exportNames.end();++it) {
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
