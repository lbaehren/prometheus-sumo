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

#ifndef CONFIG_PACKAGES_H
#define CONFIG_PACKAGES_H

#include "ConfigFileBase.h"

namespace prometheus {   // namespace prometheus -- BEGIN

  namespace config {   // namespace config -- BEGIN

    /*!
      \file Packages.h
      \class Packages
      \ingroup prometheus
      \ingroup config
      \brief Configuration settings for required software packages
      \test testConfigPackages.cc

      \author Lars Baehren
      \date 2012-10-22

      This class provides an adapter to read configuration data on list of
      required software packages (`.deb`, `.rpm`, MacPorts, Ruby gems), most of
      which are used for the \ref pandora web application and \ref homepage.
    */
    class Packages : public ConfigFileBase {

      //! Parameters for the package node of the configuration file
      struct param {
        //! Name of the package
        std::string name;
        //! URL for package's project page
        std::string homepage;
        //! Description of the package
        std::string description;
        //! Version specification
        std::string version;
      };

      //! List of packages for which parameters are kept
      std::vector<param> itsPackageList;

      //! Store the data from an individual node
      bool storeNode (YAML::Iterator const &it);

    public:

      // === Construction =======================================================

      //! Default constructor
      Packages ();

      //! Argumented constructor
      Packages (std::string const &filename);

      // === Parameter access ===================================================

      //! Get the number of packages for which parameters are kept
      inline size_t size () {
        return itsPackageList.size();
      }

      //! Get the name of the packages
      std::set<std::string> names ();

      //! Get version information for the packages
      std::map<std::string,std::string> versions ();

      //! Get URL for package's project page
      std::map<std::string,std::string> homepages ();

      //! Get description of the packages
      std::map<std::string,std::string> descriptions ();

      // === Public functions ===================================================

      //! Install the packages
      int install_packages (std::string const &installCommand,
                            bool const &verbose=false);

      //! Provide a summary of the object's internal parameters and status
      inline void summary () {
        summary (std::cout);
      }

      //! Provide a summary of the object's internal parameters and status
      void summary (std::ostream &os);

    };

  }   // namespace config -- BEGIN

}   // namespace prometheus -- END

#endif
