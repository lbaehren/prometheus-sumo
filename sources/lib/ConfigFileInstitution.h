#ifndef CONFIG_FILE_INSTITUTION_H
#define CONFIG_FILE_INSTITUTION_H

/*!
  \file ConfigFileInstitution.h
  \ingroup prometheus
  \brief Data structures and and operator overloading
  \author Lars Baehren

  File location: $PANDORA_ROOT_DIR/config/apps/institution.yml

  \verbatim
  ---
:columns_for:
  :list:
    - name
    - title
    - city
    - country
    - licenses.license_type_id
  :search:
    - name
    - title
    - description
    - city
  :user:
    - title
    - description
    - addressline
    - postalcode
    - city
    - country
    - email
    - homepage
    - public_info
  \endverbatim
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


/*!
  \brief Parameters of the 'colums_for' node
*/
struct InstitutionColumns {
   std::vector <InstitutionList> list;
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
