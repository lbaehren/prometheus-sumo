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

#ifndef PROM_DEPENDENCIES_H
#define PROM_DEPENDENCIES_H

#include <Config/Packages.h>

#ifdef WITH_BOOST
namespace bpo = boost::program_options;
#endif

/*!
  \file prom_dependencies.h
  \ingroup prometheus
  \ingroup apps
  \brief Wrapper for the installation of system packages
  \author Lars Baehren
  \date 2012-11-05

  \b Usage:

  \verbatim
  [prom_dependencies] Available command line options:
  -H [ --help ]         Show this help message
  -C [ --config ]       Print summary of configuration settings
  -I [ --install ]      Install dependencies
  -U [ --update ]       Update dependencies
  --gems arg            Install Ruby gems
  --debian arg          Install Debian packages
  --osx arg             Install MacPorts packages for OS X
  --redhat arg          Install Redhat packages
  \endverbatim
*/

// === Function prototypes ======================================================

/*!
  \brief Install dependencies
  \return status -- Returns non-zero value in case an error was encountered.
*/
int install_dependencies ();

/*!
  \brief Update dependencies
  \return status -- Returns non-zero value in case an error was encountered.
*/
int update_dependencies ();

/*!
  \brief Install Ruby gems
  \param filename -- Name of the configuration file.
  \return status  -- Returns non-zero value in case an error was encountered.
*/
int install_ruby_gems (std::string const &filename);

/*!
  \brief Install Debian packages
  \param filename -- Name of the configuration file.
  \return status  -- Returns non-zero value in case an error was encountered.
*/
int install_packages_debian (std::string const &filename);

/*!
  \brief Install OS X packages through MacPorts
  \param filename -- Name of the configuration file.
  \return status  -- Returns non-zero value in case an error was encountered.
*/
int install_packages_osx (std::string const &filename);

/*!
  \brief Install Redhat packages
  \param filename -- Name of the configuration file.
  \return status  -- Returns non-zero value in case an error was encountered.
*/
int install_packages_redhat (std::string const &filename);


#endif
