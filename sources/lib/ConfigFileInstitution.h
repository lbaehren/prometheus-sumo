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

#ifndef CONFIG_FILE_INSTITUTION_H
#define CONFIG_FILE_INSTITUTION_H

/*!
  \file ConfigFileInstitution.h
  \ingroup prometheus
  \brief Data structures and and operator overloading
  \author Lars Baehren

  \include institution.yml
*/

// ==============================================================================
//
//  Data structures
//
// ==============================================================================

/*! Parameters of the 'list' node */
struct InstitutionList {
  //! Name of the institution
  std::string name;
  //! Title of the institution
  std::string title;
  //! City the institution is located in
  std::string city;
  //! Country the institution is located in
  std::string country;
  //! Type of license
  int license_type_id;
};


/*! Parameters of the 'search' node */
struct InstitutionSearch {
  //! Parameters available to search
  std::vector<std::string> searchParameters;
};

/*! Parameters of the 'user' node */
struct InstitutionUser {
  //! Title of the institution
  std::string title;
  //! Description for the institution
  std::string description;
  //! Address of the institution
  std::string addressline;
  //! Postal code for the institution
  std::string postalcode,;
  //! City the institution is located in
  std::string city;
  //! Country the institution is located in
  std::string country;
  //! Email contact for the institution
  std::string email;
  //! Homepage of the institution
  std::string homepage;
  std::string public_info;
 };


/*! Parameters of the 'colums_for' node */
struct InstitutionColumns {
  //! Parameter list
  std::vector <InstitutionList> list;
  //! Parameters available for search
  std::vector <InstitutionSearch> search;
  std::vector <InstitutionUser> user;
};

// ==============================================================================
//
//  Methods
//
// ==============================================================================

//! Operator overloading to store contents of node
void operator >> (const YAML::Node& node,
		  InstitutionSearch& inst)
{
  // Initialize parameter vector
  inst.searchParameters.clear();

}


//! Operator overloading to store contents of node
void operator >> (const YAML::Node& node,
		  InstitutionList& inst)
{
  node["name"]    >> inst.name;
  node["title"]   >> inst.title;
  node["city"]    >> inst.city;
  node["country"] >> inst.country;
}

#endif
