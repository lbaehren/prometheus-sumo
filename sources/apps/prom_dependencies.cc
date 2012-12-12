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

#include "prom_dependencies.h"

// ==============================================================================
//
//  Function implementations
//
// ==============================================================================

//_______________________________________________________________________________
//                                                           install_dependencies

int install_dependencies ()
{
  int status = 0;
  std::string packagelist = CMAKE_INSTALL_PREFIX;

  /* Platform-/OS-dependent installation instructions */

#ifdef DEBIAN_FOUND
  packagelist += "/etc/prometheus/packages_debian.yml";
  install_packages_debian (packagelist);
#endif

#ifdef FEDORA_FOUND
#endif

#ifdef MACOSX_FOUND
#endif

#ifdef REDHAT_FOUND
  packagelist += "/etc/prometheus/packages_redhat.yml";
  install_packages_redhat (packagelist);
#endif

#ifdef UBUNTU_FOUND
  packagelist += "/etc/prometheus/packages_debian.yml";
  install_packages_debian (packagelist);
#endif

  /* Installation of Ruby gems */

  packagelist += "/etc/prometheus/gems.yml";
  install_ruby_gems (packagelist);

  return status;
}

//_______________________________________________________________________________
//                                                            update_dependencies

int update_dependencies ()
{
  int status = 0;

  return status;
}

//_______________________________________________________________________________
//                                                              install_ruby_gems

int install_ruby_gems (std::string const &filename)
{
  prometheus::config::Packages packages;
  packages.readConfig(filename);

  return packages.install_packages("gem install");
}

//_______________________________________________________________________________
//                                                        install_packages_debian

int install_packages_debian (std::string const &filename)
{
  prometheus::config::Packages packages;
  packages.readConfig(filename);

  return packages.install_packages("apt-get install");
}

//_______________________________________________________________________________
//                                                           install_packages_osx

int install_packages_osx (std::string const &filename)
{
  prometheus::config::Packages packages;
  packages.readConfig(filename);

  return packages.install_packages("port install");
}

//_______________________________________________________________________________
//                                                        install_packages_redhat

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

  bpo::options_description desc ("[prom_dependencies] Available command line options");

  desc.add_options ()
    ("help,H",    "Show this help message")
    ("config,C",  "Print summary of configuration settings")
    ("install,I", "Install dependencies")
    ("update,U",  "Update dependencies")
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
  } else if (vm.count("install")) {
    status += install_dependencies();
  } else if (vm.count("update")) {
    status += update_dependencies();
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
  
  if ( argc>1 ) {
    std::string selection = std::string(argv[1]);
    if (selection == "--config") {
      prometheus::configuration_summary (std::cout);
    }
    if (selection == "--install") {
      status += install_dependencies();
    }
    if (selection == "--update") {
      status += update_dependencies();
    }
    if ( argc>2 ) {
      std::string filename  = std::string(argv[2]);
      // Extract the test case selection
      if (selection == "--config") {
	status += install_ruby_gems(filename);
      }	else if (selection == "--gems") {
	status += install_ruby_gems(filename);
      } else if (selection == "--debian") {
	status += install_packages_debian(filename);
      } else if (selection == "--osx") {
	status += install_packages_osx(filename);
      } else if (selection == "--redhat") {
	status += install_packages_redhat(filename);
      }
    }
  } else {
    std::cout << "[prom_dependencies] Available command line options:" << std::endl;
    std::cout << " --config         Print summary of configuration settings" << std::endl;
    std::cout << " --install        Install dependencies"                    << std::endl;
    std::cout << " --gems arg       Install Ruby gems"                       << std::endl;
    std::cout << " --debian arg     Install Debian packages"                 << std::endl;
    std::cout << " --osx arg        Install MacPorts packages for OS X"      << std::endl;
    std::cout << " --redhat arg     Install Redhat packages"                 << std::endl;
  }
  
#endif

  return status;
}
