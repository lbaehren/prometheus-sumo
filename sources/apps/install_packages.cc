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

namespace bpo = boost::program_options;

/*!
  \file install_packages.cc
  \ingroup prometheus
  \ingroup apps
  \brief Wraper for the installation of system packages
  \author Lars Baehren
  \date 2012-11-05
*/

//! Install Debian packages
int install_packages_debian ()
{
}

//! Install OS X packages through MacPorts
int install_packages_osx ()
{
}

//! Install Redhat packages
int install_packages_redhat ()
{
}

// === Program main function ====================================================

//! Program main function
int main (int argc, char *argv[])
{
  int status = 0;

  //________________________________________________________
  // Description of command line options

  bpo::options_description desc ("[install_packages] Available command line options");

  desc.add_options ()
    ("help,H",    "Show help messages")
    ("config,C",  "Print summary of configuration settings")
    ("debian",    "Install Debian packages")
    ("osx",       "Install MacPorts packages for OS X")
    ("redhat",    "Install Redhat packages")
    ;

  bpo::variables_map vm;
  bpo::store (bpo::parse_command_line(argc,argv,desc), vm);

  /*________________________________________________________
    Process command line options
  */

  if (vm.count("help") || argc == 1) {
    std::cout << "\n" << desc << std::endl;
    return 0;
  } else if (vm.count("config")) {
    configuration_settings (std::cout);
  } else if (vm.count("debian")) {
    status += install_packages_debian();
  } else if (vm.count("osx")) {
    status += install_packages_osx();
  } else if (vm.count("redhat")) {
    status += install_packages_redhat();
  }

  return status;
}
