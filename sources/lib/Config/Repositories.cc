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

#include "Repositories.h"

namespace prometheus {   // namespace prometheus -- BEGIN

  namespace config {   // namespace config -- BEGIN

    // ==========================================================================
    //
    //  Construction
    //
    // ==========================================================================

    Repositories::Repositories ()
      : ConfigFileBase ()
    {
    }

    Repositories::Repositories (std::string const &filename)
      : ConfigFileBase (filename)
    {
    }

    // ==========================================================================
    //
    //  Parameter access
    //
    // ==========================================================================

    bool Repositories::storeNode (YAML::Iterator const &it)
    {
      bool status = true;
      params buffer;

      try {
        /* Extract parameters from node ... */
        (*it)["name"]         >> buffer.name;
        (*it)["description"]  >> buffer.description;
        (*it)["type"]         >> buffer.type;
        (*it)["url"]          >> buffer.url;
        /* .. and store them internally */
        itsRepositoryList.push_back(buffer);
      } catch (std::exception &e) {
        std::cout << "[Repositories::storeNode] ERROR : " << e.what() << std::endl;
        status = false;
      }

      return status;
    }

    //___________________________________________________________________________
    //                                                                      names

    std::set<std::string> Repositories::names ()
    {
      std::set<std::string> packageNames;

      if (!itsRepositoryList.empty()) {
        for (size_t n=0; n<itsRepositoryList.size(); ++n) {
          packageNames.insert(itsRepositoryList[n].name);
        }
      }

      return packageNames;
    }

    //___________________________________________________________________________
    //                                                               descriptions

    std::map<std::string,std::string> Repositories::descriptions ()
    {
      std::map<std::string,std::string> packageDescriptions;

      if (!itsRepositoryList.empty()) {
        for (size_t n=0; n<itsRepositoryList.size(); ++n) {
          packageDescriptions[itsRepositoryList[n].name] = itsRepositoryList[n].description;
        }
      }

      return packageDescriptions;
    }

    //___________________________________________________________________________
    //                                                                   types

    std::map<std::string,std::string> Repositories::types ()
    {
      std::map<std::string,std::string> packageTypes;

      if (!itsRepositoryList.empty()) {
        for (size_t n=0; n<itsRepositoryList.size(); ++n) {
          packageTypes[itsRepositoryList[n].name] = itsRepositoryList[n].type;
        }
      }

      return packageTypes;
    }

    //___________________________________________________________________________
    //                                                                       urls

    std::map<std::string,std::string> Repositories::urls ()
    {
      std::map<std::string,std::string> packageURL;

      if (!itsRepositoryList.empty()) {
        for (size_t n=0; n<itsRepositoryList.size(); ++n) {
          packageURL[itsRepositoryList[n].name] = itsRepositoryList[n].url;
        }
      }

      return packageURL;
    }

    // ==========================================================================
    //
    //  Public functions
    //
    // ==========================================================================

    bool Repositories::clone ()
    {
      bool status = true;

      if (itsRepositoryList.empty()) {
        std::cerr << "[Repositories::clone] Empty list of repositories!"
                  << std::endl;
        status = false;
      }  else {
        for (size_t n=0; n<itsRepositoryList.size(); ++n) {
          status *= clone(itsRepositoryList[n].name);
        }
      }

      return status;
    }

    /*!
      \param name -- Name of the repository/project for which to check out a
                     working copy.
    */
    bool Repositories::clone (std::string const &name)
    {
      bool status = true;

      return status;
    }

    //___________________________________________________________________________
    //                                                                    summary

    /*!
      \param os -- Output stream to which the summary will be written.
    */
    void Repositories::summary (std::ostream &os)
    {
      os << "[Repositories] Summary of internal parameters"         << std::endl;
      os << "-- Configuration file = " << itsConfigFile         << std::endl;
      os << "-- nof. packages      = " << itsRepositoryList.size() << std::endl;
      os << "-- Repository names   = " << names()               << std::endl;
    }

  }   // namespace config -- BEGIN

}   // namespace prometheus -- END

