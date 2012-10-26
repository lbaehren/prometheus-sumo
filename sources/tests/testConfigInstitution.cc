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
#include <Config/Institution.h>

/*!
  \file testConfigInstitution.cc
  \ingroup prometheus
  \ingroup tests
  \brief A collection of tests for the prometheus::config::Institution class
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
int test_constructors (std::string const &filename="institution.yml")
{
  std::cout << "\n[testInstitution::test_constructors]\n" << std::endl;

  int status = 0;

  std::cout << "[1] Testing Institution() ..." << std::endl;
  try {
    prometheus::config::Institution inst;
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[2] Testing Institution(std::string) ..." << std::endl;
  try {
    prometheus::config::Institution inst (filename);
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
  std::cout << "\n[testInstitution::test_read_config]\n" << std::endl;

  int status = 0;
  prometheus::config::Institution inst;
  std::set<std::string> columnNames;

  std::cout << "[1] Testing Institution::readConfig(std::string) ..." << std::endl;
  try {
    inst.readConfig(filename);
    inst.summary();
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[2] Testing Institution::columnNames() ..." << std::endl;
  try {
    columnNames = inst.columnNames();
    std::cout << "--> Column names = " << columnNames << std::endl;
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[3] Testing Institution::columnNamesFor(std::string) ..." << std::endl;
  try {
    std::set<std::string>::iterator it;

    for (it=columnNames.begin(); it!=columnNames.end(); ++it) {
      std::cout << "--> " << (*it) << std::endl;
      std::cout << "\t" << inst.columnNamesFor( (*it) ) << std::endl;
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
  int status      = 0;

  if (argc >1) {
    status += test_constructors (argv[1]);
    status += test_read_config (argv[1]);
  } else {
    status += test_constructors ();
  }

  return status;
}
