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

#include "VirtualMachines.h"

namespace prometheus {   // namespace prometheus -- BEGIN

  namespace config {   // namespace config -- BEGIN

    // ==========================================================================
    //
    //  Construction
    //
    // ==========================================================================

    VirtualMachines::VirtualMachines ()
      : ConfigFileBase ()
    {
    }

    VirtualMachines::VirtualMachines (std::string const &filename)
      : ConfigFileBase (filename)
    {
    }

    // ==========================================================================
    //
    //  Parameter access
    //
    // ==========================================================================

    bool VirtualMachines::storeNode (YAML::Iterator const &it)
    {
      bool status = true;
      params buffer;

      try {
        /* Extract parameters from node ... */
        (*it)["name"]    >> buffer.name;
        (*it)["uuid"]    >> buffer.uuid;
        (*it)["import"]  >> buffer.importName;
        (*it)["export"]  >> buffer.exportName;
        /* .. and store them internally */
        itsPackageList.push_back(buffer);
      } catch (std::exception &e) {
        std::cout << "[VirtualMachines::storeNode] ERROR : " << e.what() << std::endl;
        status = false;
      }

      return status;
    }

    //___________________________________________________________________________
    //                                                                      names

    std::set<std::string> VirtualMachines::names ()
    {
      std::set<std::string> packageNames;

      if (!itsPackageList.empty()) {
        for (size_t n=0; n<itsPackageList.size(); ++n) {
          packageNames.insert(itsPackageList[n].name);
        }
      }

      return packageNames;
    }

    //___________________________________________________________________________
    //                                                                      uuids

    std::map<std::string,std::string> VirtualMachines::uuids ()
    {
      std::map<std::string,std::string> data;

      if (!itsPackageList.empty()) {
        for (size_t n=0; n<itsPackageList.size(); ++n) {
          data[itsPackageList[n].name] = itsPackageList[n].uuid;
        }
      }

      return data;
    }

    //___________________________________________________________________________
    //                                                                importNames

    std::map<std::string,std::string> VirtualMachines::importNames ()
    {
      std::map<std::string,std::string> data;

      if (!itsPackageList.empty()) {
        for (size_t n=0; n<itsPackageList.size(); ++n) {
          data[itsPackageList[n].name] = itsPackageList[n].importName;
        }
      }

      return data;
    }

    //___________________________________________________________________________
    //                                                                exportNames

    std::map<std::string,std::string> VirtualMachines::exportNames ()
    {
      std::map<std::string,std::string> data;

      if (!itsPackageList.empty()) {
        for (size_t n=0; n<itsPackageList.size(); ++n) {
          data[itsPackageList[n].name] = itsPackageList[n].exportName;
        }
      }

      return data;
    }

    // ==========================================================================
    //
    //  Public functions
    //
    // ==========================================================================

    //___________________________________________________________________________
    //                                                                     import

    bool VirtualMachines::import ()
    {
      bool status = true;

      if (!itsPackageList.empty()) {
	for (size_t n=0; n<itsPackageList.size(); ++n) {
          status *= import (itsPackageList[n].name);
        }
      } else {
	std::cerr << "[VirtualMachines::import] Empty list of virtual machines!"
                  << std::endl;
	status = false;
      }

      return status;
    }

    //___________________________________________________________________________
    //                                                                     import

    /*!
      \param name       -- Name of the virtual machine to import.
      \param nameIsUUID -- Interpret the given name as \c UUID.
      \return status    -- Status of the operation; returns \c false in case an
                           error was encountered.
     */
    bool VirtualMachines::import (std::string const &name,
                                  bool const &nameIsUUID)
    {
#ifdef VIRTUALBOX_FOUND
      return true;
#else
      return false;
#endif
    }

    //___________________________________________________________________________
    //                                                                    summary

    /*!
      \param os -- Output stream to which the summary will be written.
    */
    void VirtualMachines::summary (std::ostream &os)
    {
      os << "[VirtualMachines] Summary of internal parameters"     << std::endl;
      os << "-- Configuration file    = " << itsConfigFile         << std::endl;
      os << "-- nof. virtual machines = " << itsPackageList.size() << std::endl;
      os << "-- Virtual machine names = " << names()               << std::endl;
    }

  }   // namespace config -- BEGIN

}   // namespace prometheus -- END

