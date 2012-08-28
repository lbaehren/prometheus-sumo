
#include <fstream>
#include <iostream>
#include <string>
#include <set>

#include <yaml-cpp/yaml.h>

// ==============================================================================
//
//  Helper functions
//
// ==============================================================================

//_______________________________________________________________________________
//                                                             readTrustedProxies

/*!
  \brief Read in the list of trusted proxies

  \param pandoraBase -- Base directory of the pandora installation.
  \param path        -- Relative path to the configuration file.

  \verbatim
  ---
  - 134.95.80.11    # prometheus1.uni-koeln.de
  - 134.95.80.12    # prometheus2.uni-koeln.de
  - 134.95.80.95    # prometheus-db1.uni-koeln.de
  - 134.95.80.96    # prometheus-web1.uni-koeln.de
  \endverbatim
*/
int readTrustedProxies (std::string const &filename)
{
  std::cout << "\n[YamlReader::readTrustedProxies]\n" << std::endl;
  
  /* Load configuration file */
  std::ifstream infile (filename.c_str());
  
  if (infile.is_open()) {
    
    YAML::Parser parser(infile);
    
    /* Parse the contents of the file */
    YAML::Node node;
    parser.GetNextDocument(node);
    
    std::cout << "--> nof. nodes = " << node.size() << std::endl;
    
    for (YAML::Iterator it=node.begin();it!=node.end();++it) {
      std::string scalar;
      *it >> scalar;
      std::cout << "Found scalar: " << scalar << std::endl;
    }
    
  } else {
    std::cerr << "--> Failed to open file " << filename << std::endl;
    return 1;
  }
  
  /* Close the input stream */
  infile.close();

  return 0;
}

//_______________________________________________________________________________
//                                                                 readInsitution


//! \a List node of the Institution configuration file
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

struct InstitutionSearch {
  //! Name of the institution
  std::string name;
  //! Title of the institution
  std::string title;
  //! Description for the institution
  std::string description;
  //! City the institution is located in
  std::string city;
};

struct InstitutionUser {
  std::string title;
  std::string description;
  std::string addressline;
  std::string postalcode,;
  std::string city;
  std::string country;
  std::string email;
  std::string homepage;
  std::string public_info;
 };

// struct InstitutionColumns {
//   std::string name;
//   Vec3 position;
//   std::vector <Power> powers;
// };


//! Operator overloading to store contents of node
void operator >> (const YAML::Node& node,
		  InstitutionList& inst)
{
  node["name"]    >> inst.name;
  node["title"]   >> inst.title;
  node["city"]    >> inst.city;
  node["country"] >> inst.country;
}

/*!
  \brief Read attributes associated with an institution.
  
  \param filename -- Path to the configuration file.

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
int readInsitution (std::string const &filename)
{
  std::cout << "\n[YamlReader::readInsitution]\n" << std::endl;
  
  /* Load configuration file */
  std::ifstream infile (filename.c_str());
  
  if (infile.is_open()) {

    YAML::Node node;
    
    YAML::Parser parser(infile);
    parser.GetNextDocument(node);
    
    std::cout << "--> nof. nodes = " << node.size() << std::endl;

    for (YAML::Iterator it=node.begin();it!=node.end();++it) {
      InstitutionList inst;
      *it >> inst;
      std::cout << "Found Institution list: "<< std::endl;
      std::cout << "-- Name  = " << inst.name  << std::endl;
      std::cout << "-- Title = " << inst.title << std::endl;
      
    }
    
  } else {
    std::cerr << "--> Failed to open file " << filename << std::endl;
    return 1;
  }
  
  /* Close the input stream */
  infile.close();

  return 0;
}

// ==============================================================================
//
//  Main program function
//
// ==============================================================================

/*!
  \file TestYamlReading.cc
  \brief Test reading in configuration data from \ref refman_yaml files
  \author Lars Baehren
*/
int main ()
{
  int retval = 0;
  std::string filename;
  std::string pandoraBaseDir = "/Users/lars/CodeDevelopment/Projects/Work/prometheus/pandora/";

  /* Read the list of trusted proxies */
  filename = pandoraBaseDir + "config/trusted_proxies.yml";
  retval += readTrustedProxies (filename);
 
  /* Read attributes of an institution */
  filename = pandoraBaseDir + "config/app/institution.yml";
  retval += readInsitution (filename);

  return retval;
}
