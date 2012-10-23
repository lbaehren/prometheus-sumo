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

#include "UserRoles.h"

namespace prometheus {   // namespace prometheus -- BEGIN

  namespace config {   // namespace config -- BEGIN

    // ==========================================================================
    //
    //  Construction
    //
    // ==========================================================================

    UserRoles::UserRoles ()
      : ConfigFileBase ()
    {
    }

    UserRoles::UserRoles (std::string const &filename)
      : ConfigFileBase (filename)
    {
    }

    // ==========================================================================
    //
    //  Parameter access
    //
    // ==========================================================================

    //___________________________________________________________________________
    //                                                                     titles

    std::set<std::string> UserRoles::titles ()
    {
      std::set<std::string> roleTitles;

      if (!itsRolesList.empty()) {
	for (size_t n=0; n<itsRolesList.size(); ++n) {
	  roleTitles.insert(itsRolesList[n].title);
	}
      }

      return roleTitles;
    }

    //___________________________________________________________________________
    //                                                                       keys

    std::set<std::string> UserRoles::keys ()
    {
      std::set<std::string> roleKeys;

      if (!itsRolesList.empty()) {
	for (size_t n=0; n<itsRolesList.size(); ++n) {
	  roleKeys.insert(itsRolesList[n].key);
	}
      }

      return roleKeys;
    }

    //___________________________________________________________________________
    //                                                                  storeNode

    bool UserRoles::storeNode (YAML::Iterator const &it)
    {
      bool status = true;
      RoleParameters buffer;

      try {
	/* Extract parameters from node ... */
	it.first()           >> buffer.key;
	it.second()["title"] >> buffer.title;
	it.second()["id"]    >> buffer.id;
	/* .. and store them internally */
	itsRolesList.push_back(buffer);
      } catch (std::exception &e) {
	std::cout << "[UserRoles::storeNode] ERROR : " << e.what() << std::endl;
	status = false;
      }

      return status;
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
    void UserRoles::summary (std::ostream &os)
    {
      os << "[UserRoles] Summary of internal parameters"      << std::endl;
      os << "-- Configuration file = " << itsConfigFile       << std::endl;
      os << "-- nof. roles         = " << itsRolesList.size() << std::endl;
      os << "-- Role titles        = " << titles()            << std::endl; 
    }

  }   // namespace config -- BEGIN

}   // namespace prometheus -- END

