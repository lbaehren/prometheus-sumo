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

#include "Gems.h"

namespace prometheus {   // namespace prometheus -- BEGIN

  namespace config {   // namespace config -- BEGIN

    // ==========================================================================
    //
    //  Construction
    //
    // ==========================================================================

    Gems::Gems ()
      : ConfigFileBase ()
    {
    }

    Gems::Gems (std::string const &filename)
      : ConfigFileBase (filename)
    {
    }

    // ==========================================================================
    //
    //  Parameter access
    //
    // ==========================================================================

    bool Gems::storeNode (YAML::Iterator const &it)
    {
      bool status = true;
      GemParameters buffer;

      try {
        /* Extract parameters from node ... */
        (*it)["name"]         >> buffer.name;
        (*it)["url"]          >> buffer.url;
        (*it)["description"]  >> buffer.description;
        (*it)["version"]      >> buffer.version;
        /* .. and store them internally */
        itsGemList.push_back(buffer);
      } catch (std::exception &e) {
        std::cout << "[Gems::storeNode] ERROR : " << e.what() << std::endl;
        status = false;
      }

      return status;
    }

    //___________________________________________________________________________
    //                                                                      names

    std::set<std::string> Gems::names ()
    {
      std::set<std::string> gemNames;

      if (!itsGemList.empty()) {
        for (size_t n=0; n<itsGemList.size(); ++n) {
          gemNames.insert(itsGemList[n].name);
        }
      }

      return gemNames;
    }

    //___________________________________________________________________________
    //                                                                   versions

    std::map<std::string,std::string> Gems::versions ()
    {
      std::map<std::string,std::string> gemVersions;

      if (!itsGemList.empty()) {
        for (size_t n=0; n<itsGemList.size(); ++n) {
          gemVersions[itsGemList[n].name] = itsGemList[n].version;
        }
      }

      return gemVersions;
    }

    //___________________________________________________________________________
    //                                                                       urls

    std::map<std::string,std::string> Gems::urls ()
    {
      std::map<std::string,std::string> gemURL;

      if (!itsGemList.empty()) {
        for (size_t n=0; n<itsGemList.size(); ++n) {
          gemURL[itsGemList[n].name] = itsGemList[n].url;
        }
      }

      return gemURL;
    }

    // ==========================================================================
    //
    //  Public functions
    //
    // ==========================================================================

    //___________________________________________________________________________
    //                                                                    summary

    /*!
      \param os -- Output stream to which the summary will be written.
    */
    void Gems::summary (std::ostream &os)
    {
      os << "[Gems] Summary of internal parameters"     << std::endl;
      os << "-- Configuration file = " << itsConfigFile     << std::endl;
      os << "-- nof. gem settings  = " << itsGemList.size() << std::endl;
      os << "-- Gem names          = " << names()           << std::endl;
    }


  }   // namespace config -- BEGIN

}   // namespace prometheus -- END
