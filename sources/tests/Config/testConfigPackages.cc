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
#include <Config/Packages.h>

/*!
  \file testConfigPackages.cc
  \ingroup prometheus
  \ingroup tests
  \brief A collection of tests for the prometheus::config::Packages class
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
  std::cout << "\n[testPackages::test_constructors]\n" << std::endl;

  int status = 0;

  std::cout << "[1] Testing Packages() ..." << std::endl;
  try {
    prometheus::config::Packages packages;
    //
    std::cout << "--> Config file = " << packages.configFile() << std::endl;
    std::cout << "--> nof. packages   = " << packages.size()    << std::endl;
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[2] Testing Packages(std::string) ..." << std::endl;
  try {
    prometheus::config::Packages packages (filename);
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
//                                                               test_read_config

/*!
  \brief Test reading list of Ruby packages from configuration file
*/
int test_read_config (std::string const &filename)
{
  std::cout << "\n[testPackages::test_read_config]\n" << std::endl;

  int status = 0;
  prometheus::config::Packages packages;

  std::cout << "[1] Testing Packages::readConfig(std::string) ..." << std::endl;
  try {
    packages.readConfig(filename);
    packages.summary();
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[2] Testing Packages::names() ..." << std::endl;
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

  std::cout << "[3] Testing Packages::versions() ..." << std::endl;
  try {
    std::map<std::string,std::string>::iterator it;
    // Get the names of the packages ...
    std::map<std::string,std::string> versions = packages.versions();
    // ... and print them
    std::cout << "--> nof. packages = " << versions.size() << std::endl;
    for (it=versions.begin();it!=versions.end();++it) {
      std::cout << std::setw(25) << it->first << "  :  " << it->second << std::endl;
    }
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[4] Testing Packages::descriptions() ..." << std::endl;
  try {
    std::map<std::string,std::string>::iterator it;
    // Get the names of the packages ...
    std::map<std::string,std::string> descriptions = packages.descriptions();
    // ... and print them
    std::cout << "--> nof. packages = " << descriptions.size() << std::endl;
    for (it=descriptions.begin();it!=descriptions.end();++it) {
      std::cout << std::setw(25) << it->first << "  :  " << it->second << std::endl;
    }
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[5] Testing Packages::urls() ..." << std::endl;
  try {
    std::map<std::string,std::string>::iterator it;
    // Get the names of the packages ...
    std::map<std::string,std::string> urls = packages.urls();
    // ... and print them
    std::cout << "--> nof. packages = " << urls.size() << std::endl;
    for (it=urls.begin();it!=urls.end();++it) {
      std::cout << std::setw(25) << it->first << "  :  " << it->second << std::endl;
    }
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  return status;
}

//_______________________________________________________________________________
//                                                                 test_ruby_gems

/*!
  \brief Test listing and installation of Ruby gems
 */
int test_ruby_gems ()
{
  std::cout << "\n[testPackages::test_ruby_gems]\n" << std::endl;

  int status = 0;
  std::vector<std::string> commands;
  std::string output;

  commands.push_back("gem list unicode");
  commands.push_back("gem list bliblablub");
  commands.push_back("apt-get update");
  commands.push_back("yum update");
  commands.push_back("date");

  std::cout << "[1] Test 'gem list' to find gem ..." << std::endl;
  try {

    for (size_t n=0; n<commands.size(); ++n) {
      // Run the command
      status = run_command (commands[n], output);
      // Report the results
      std::cout << "-- Command = " << commands[n] << std::endl;
      std::cout << "-- Status  = " << status      << std::endl;
      std::cout << "-- Output  = " << output      << std::endl;
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

  // --- Tests depending on input test data ---
  
  if (argc >1) {
    status += test_constructors (argv[1]);
    status += test_read_config (argv[1]);
  } else {
    status += test_constructors ();
  }

  // --- Tests independent on input testdata

  status += test_ruby_gems ();

  return status;
}
