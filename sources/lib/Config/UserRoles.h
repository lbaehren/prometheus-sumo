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

#ifndef CONFIG_USER_ROLES_H
#define CONFIG_USER_ROLES_H

#include "ConfigFileBase.h"

// ==============================================================================
//
//  Class definition
//
// ==============================================================================

namespace prometheus {   // namespace prometheus -- BEGIN

  namespace config {   // namespace config -- BEGIN

    /*!
      \file UserRoles.h
      \class UserRoles
      \ingroup prometheus
      \ingroup config
      \brief Configuration settings user roles inside the application
      \test testConfigUserRoles.cc

      \author Lars Baehren
      \date 2012-10-22
    */
    class UserRoles : public ConfigFileBase {

    protected:

      //! Parameters for a user role
      struct RoleParameters {
	//! Keyword used for referencing
	std::string key;
	//! Title for the role
	std::string title;
	//! ID used internally with the database
	unsigned int id;
      };

      //! Store the data from an individual node
      bool storeNode (YAML::Iterator const &it);

    private:

      //! List of gems for which parameters are kept
      std::vector<RoleParameters> itsRolesList;

    public:

      // === Construction =======================================================

      //! Default constructor
      UserRoles ();

      //! Argumented constructor
      UserRoles (std::string const &filename);

      // === Parameter access ===================================================

      //! Get the number of gems for which parameters are kept
      inline size_t nofRoles () {
	return itsRolesList.size();
      }
      
      //! Get a list of the role keys
      std::set<std::string> keys ();

      //! Get a list of the role titles
      std::set<std::string> titles ();

      // === Public functions ===================================================

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
