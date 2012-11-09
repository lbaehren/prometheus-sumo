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

#include <Config/Packages.h>

#ifdef WITH_BOOST
namespace bpo = boost::program_options;
#endif

/*!
  \file install_packages.cc
  \ingroup prometheus
  \ingroup apps
  \brief Wrapper for the installation of system packages
  \author Lars Baehren
  \date 2012-11-05

  \b Usage:

  \verbatim
[install_packages] Available command line options:
  -H [ --help ]         Show this help message
  -C [ --config ]       Print summary of configuration settings
  --gems arg            Install Ruby gems
  --debian arg          Install Debian packages
  --osx arg             Install MacPorts packages for OS X
  --redhat arg          Install Redhat packages
  \endverbatim
*/

//_______________________________________________________________________________
//                                                              install_ruby_gems

/*!
  \brief Install Ruby gems
  \param filename -- Name of the configuration file.
  \return status  -- Returns non-zero value in case an error was encountered.
*/
int install_ruby_gems (std::string const &filename)
{
  prometheus::config::Packages packages;
  packages.readConfig(filename);

#ifdef GEM_FOUND
  return packages.install_packages("gem install");
#else
  return 0;
#endif
}

//_______________________________________________________________________________
//                                                        install_packages_debian

/*!
  \brief Install Debian packages
  \param filename -- Name of the configuration file.
  \return status  -- Returns non-zero value in case an error was encountered.
*/
int install_packages_debian (std::string const &filename)
{
  prometheus::config::Packages packages;
  packages.readConfig(filename);

  return packages.install_packages("apt-get install");
}

//_______________________________________________________________________________
//                                                           install_packages_osx

/*!
  \brief Install OS X packages through MacPorts
  \param filename -- Name of the configuration file.
  \return status  -- Returns non-zero value in case an error was encountered.
*/
int install_packages_osx (std::string const &filename)
{
  prometheus::config::Packages packages;
  packages.readConfig(filename);

  return packages.install_packages("port install");
}

//_______________________________________________________________________________
//                                                        install_packages_redhat

/*!
  \brief Install Redhat packages
  \param filename -- Name of the configuration file.
  \return status  -- Returns non-zero value in case an error was encountered.
*/
int install_packages_redhat (std::string const &filename)
{
  prometheus::config::Packages packages;
  packages.readConfig(filename);

  return packages.install_packages("yum install");
}

// ==============================================================================
//
//  Program main function
//
// ==============================================================================

/*!
  \brief Program main function
  \return status -- Returns non-zero value, in case an error was encountered; if
                    the default interface to process command line options is not
                    present, the program will exit with status -1.
*/
int main (int argc, char *argv[])
{
  int status = 0;
  std::string filename;

#ifdef WITH_BOOST

  //________________________________________________________
  // Description of command line options

  bpo::options_description desc ("[install_packages] Available command line options");

  desc.add_options ()
    ("help,H",    "Show this help message")
    ("config,C",  "Print summary of configuration settings")
    ("gems",     bpo::value<std::string>(), "Install Ruby gems")
    ("debian",   bpo::value<std::string>(), "Install Debian packages")
    ("osx",      bpo::value<std::string>(), "Install MacPorts packages for OS X")
    ("redhat",   bpo::value<std::string>(), "Install Redhat packages")
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
    prometheus::configuration_summary (std::cout);
  } else if (vm.count("gems")) {
    filename = vm["gems"].as<std::string>();
    status += install_ruby_gems(filename);
  } else if (vm.count("debian")) {
    filename = vm["debian"].as<std::string>();
    status += install_packages_debian(filename);
  } else if (vm.count("osx")) {
    filename = vm["osx"].as<std::string>();
    status += install_packages_osx(filename);
  } else if (vm.count("redhat")) {
    filename = vm["redhat"].as<std::string>();
    status += install_packages_redhat(filename);
  }

#else

  status = -1;

#endif

  return status;
}
