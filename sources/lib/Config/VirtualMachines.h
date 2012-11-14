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

#ifndef CONFIG_VIRTUAL_MACHINES_H
#define CONFIG_VIRTUAL_MACHINES_H

#include "ConfigFileBase.h"

namespace prometheus {   // namespace prometheus -- BEGIN

  namespace config {   // namespace config -- BEGIN

    /*!
      \file VirtualMachines.h
      \class VirtualMachines
      \ingroup prometheus
      \ingroup config
      \brief Configuration settings for virtual machine appliances
      \test testConfigVirtualMachines.cc

      \author Lars Baehren
      \date 2012-11-14

    */
    class VirtualMachines : public ConfigFileBase {

      //! Configuration settings for a virtual machine appliance
      struct params {
        //! Name of the package
        std::string name;
        //! UUID
        std::string uuid;
        //! Filename when importing virtual appliance
        std::string importName;
        //! Filename when exporting virtual appliance
        std::string exportName;
      };

      //! List of VirtualMachines for which parameters are kept
      std::vector<params> itsPackageList;

      //! Store the data from an individual node
      bool storeNode (YAML::Iterator const &it);

    public:

      // === Construction =======================================================

      //! Default constructor
      VirtualMachines ();

      //! Argumented constructor
      VirtualMachines (std::string const &filename);

      // === Parameter access ===================================================

      //! Get the number of VirtualMachines for which parameters are kept
      inline size_t size () {
        return itsPackageList.size();
      }

      //! Get the name of the Virtual Machines
      std::set<std::string> names ();

      //! Get the UUIDs of the Virtual Machines
      std::map<std::string,std::string> uuids ();

      //! Get the filenames for import of virtual appliance
      std::map<std::string,std::string> importNames ();

      //! Get the filenames for export of virtual appliance
      std::map<std::string,std::string> exportNames ();

      // === Public functions ===================================================

      //! Import virtual appliances
      bool import ();

      //! Import a virtual appliance by \c name
      bool import (std::string const &name,
                   bool const &nameIsUUID=false);

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
