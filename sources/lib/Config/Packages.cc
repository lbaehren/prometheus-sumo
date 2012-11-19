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

#include "Packages.h"

namespace prometheus {   // namespace prometheus -- BEGIN

  namespace config {   // namespace config -- BEGIN

    // ==========================================================================
    //
    //  Construction
    //
    // ==========================================================================

    Packages::Packages ()
      : ConfigFileBase ()
    {
    }

    Packages::Packages (std::string const &filename)
      : ConfigFileBase (filename)
    {
    }

    // ==========================================================================
    //
    //  Parameter access
    //
    // ==========================================================================

    bool Packages::storeNode (YAML::Iterator const &it)
    {
      bool status = true;
      PackageParameters buffer;

      try {
        /* Extract parameters from node ... */
        (*it)["name"]         >> buffer.name;
        (*it)["homepage"]     >> buffer.homepage;
        (*it)["description"]  >> buffer.description;
        (*it)["version"]      >> buffer.version;
        /* .. and store them internally */
        itsPackageList.push_back(buffer);
      } catch (std::exception &e) {
        std::cout << "[Packages::storeNode] ERROR : " << e.what() << std::endl;
        status = false;
      }

      return status;
    }

    //___________________________________________________________________________
    //                                                                      names

    std::set<std::string> Packages::names ()
    {
      std::set<std::string> data;

      if (!itsPackageList.empty()) {
        for (size_t n=0; n<itsPackageList.size(); ++n) {
          data.insert(itsPackageList[n].name);
        }
      }

      return data;
    }

    //___________________________________________________________________________
    //                                                               descriptions

    std::map<std::string,std::string> Packages::descriptions ()
    {
      std::map<std::string,std::string> data;

      if (!itsPackageList.empty()) {
        for (size_t n=0; n<itsPackageList.size(); ++n) {
          data[itsPackageList[n].name] = itsPackageList[n].description;
        }
      }

      return data;
    }

    //___________________________________________________________________________
    //                                                                   versions

    std::map<std::string,std::string> Packages::versions ()
    {
      std::map<std::string,std::string> data;

      if (!itsPackageList.empty()) {
        for (size_t n=0; n<itsPackageList.size(); ++n) {
          data[itsPackageList[n].name] = itsPackageList[n].version;
        }
      }

      return data;
    }

    //___________________________________________________________________________
    //                                                                  homepages

    std::map<std::string,std::string> Packages::homepages ()
    {
      std::map<std::string,std::string> data;

      if (!itsPackageList.empty()) {
        for (size_t n=0; n<itsPackageList.size(); ++n) {
          data[itsPackageList[n].name] = itsPackageList[n].homepage;
        }
      }

      return data;
    }

    // ==========================================================================
    //
    //  Public functions
    //
    // ==========================================================================

    /*!
      \param installCommand -- Command to be invoked for the installation of the
                               packages.
      \param verbose -- Be verbose during the installation procedure?
      \return status -- Status of the operation; returns non-zero value in case
                        an error was encoutered.
    */
    int Packages::install_packages (std::string const &installCommand,
                                    bool const &verbose)
    {
      int status = 0;

      if (!itsPackageList.empty()) {
        for (size_t n=0; n<itsPackageList.size(); ++n) {
	  std::string command = installCommand + " " + itsPackageList[n].name;
	  /* Check if a specific version is defined */
	  if (itsPackageList[n].version != "~") {
	    command += " --version '" + itsPackageList[n].version + "'";
	  }
	  /* Feedback */
	  if (verbose) {
	    std::cout << "--> Installing package "
		      << itsPackageList[n].name
		      << " ..."
		      << std::endl;
	  }
	  /* System call */
	  status = system (command.c_str());
        }
      } else {
	std::cerr << "[Packages::install_packages]"
		  << " Empty package list - nothing to install!"
		  << std::endl;
      }

      return status;
    }

    //___________________________________________________________________________
    //                                                                    summary

    /*!
      \param os -- Output stream to which the summary will be written.
    */
    void Packages::summary (std::ostream &os)
    {
      os << "[Packages] Summary of internal parameters"         << std::endl;
      os << "-- Configuration file = " << itsConfigFile         << std::endl;
      os << "-- nof. packages      = " << itsPackageList.size() << std::endl;
      os << "-- Package names      = " << names()               << std::endl;
    }

  }   // namespace config -- BEGIN

}   // namespace prometheus -- END

