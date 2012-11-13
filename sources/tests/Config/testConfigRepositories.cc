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
#include <Config/Repositories.h>

/*!
  \file testConfigRepositories.cc
  \ingroup prometheus
  \ingroup tests
  \brief A collection of tests for the prometheus::config::Repositories class
  \author Lars Baehren
  \date 2012-11-13
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
  std::cout << "\n[testRepositories::test_constructors]\n" << std::endl;

  int status = 0;

  std::cout << "[1] Testing Repositories() ..." << std::endl;
  try {
    prometheus::config::Repositories repositories;
    //
    std::cout << "--> Config file = " << repositories.configFile() << std::endl;
    std::cout << "--> nof. repositories   = " << repositories.size()    << std::endl;
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[2] Testing Repositories(std::string) ..." << std::endl;
  try {
    prometheus::config::Repositories repositories (filename);
    //
    std::cout << "--> Config file = " << repositories.configFile() << std::endl;
    std::cout << "--> nof. repositories   = " << repositories.size()    << std::endl;
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  return status;
}

//_______________________________________________________________________________
//                                                              test_constructors

/*!
  \brief Test reading list of Ruby repositories from configuration file
*/
int test_read_config (std::string const &filename)
{
  std::cout << "\n[testRepositories::test_read_config]\n" << std::endl;

  int status = 0;
  prometheus::config::Repositories repositories;

  std::cout << "[1] Testing Repositories::readConfig(std::string) ..." << std::endl;
  try {
    repositories.readConfig(filename);
    repositories.summary();
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[2] Testing Repositories::names() ..." << std::endl;
  try {
    // Get the names of the repositories ...
    std::set<std::string> names = repositories.names();
    // ... and print them
    std::cout << "--> nof. repositories = " << names.size() << std::endl;
    std::cout << "--> Package names = " << names        << std::endl;
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[3] Testing Repositories::types() ..." << std::endl;
  try {
    std::map<std::string,std::string>::iterator it;
    // Get the names of the repositories ...
    std::map<std::string,std::string> types = repositories.types();
    // ... and print them
    std::cout << "--> nof. repositories = " << types.size() << std::endl;
    for (it=types.begin();it!=types.end();++it) {
      std::cout << std::setw(25) << it->first << "  :  " << it->second << std::endl;
    }
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[4] Testing Repositories::descriptions() ..." << std::endl;
  try {
    std::map<std::string,std::string>::iterator it;
    // Get the names of the repositories ...
    std::map<std::string,std::string> descriptions = repositories.descriptions();
    // ... and print them
    std::cout << "--> nof. repositories = " << descriptions.size() << std::endl;
    for (it=descriptions.begin();it!=descriptions.end();++it) {
      std::cout << std::setw(25) << it->first << "  :  " << it->second << std::endl;
    }
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[5] Testing Repositories::urls() ..." << std::endl;
  try {
    std::map<std::string,std::string>::iterator it;
    // Get the names of the repositories ...
    std::map<std::string,std::string> urls = repositories.urls();
    // ... and print them
    std::cout << "--> nof. repositories = " << urls.size() << std::endl;
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
