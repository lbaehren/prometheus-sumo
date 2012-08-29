
#include <fstream>
#include <iostream>
#include <string>
#include <set>
/* YAML support */
#include <yaml-cpp/yaml.h>
/* Project */
#include <ConfigFileInstitution.h>

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
//                                                              readDatabaseRoles

//! Data structure of configuration node
struct Role {
  //! Title for the role
  std::string title;
  //! ID used internally with the database
  unsigned int id;
};

/*!
  \brief Overloading of output operator
  \param node -- Object container for the node.
  \param role -- Data structure into which the contents of the node is being stored.
*/
void operator >> (const YAML::Node& node, Role& role) {
  node["title"] >> role.title;
  node["id"]    >> role.id;
}

/*!
  \brief Read user roles for database
  \param filename -- Path to the configuration file
*/
int readDatabaseRoles (std::string const &filename)
{
  std::cout << "\n[YamlReader::readInstitution]\n" << std::endl;
  
  std::ifstream infile (filename.c_str());
  
  if (infile.is_open()) {
    
    YAML::Node node;
    
    YAML::Parser parser(infile);
    parser.GetNextDocument(node);
    
    std::cout << "--> nof. nodes = " << node.size() << std::endl;
    std::cout << " ... Is aliased? " << node.IsAliased() << std::endl;
    std::cout << " ... Tag         " << node.Tag()        << std::endl;

    for (YAML::Iterator it=node.begin(); it!=node.end(); ++it) {
      std::cout << " -- Reading sub-node ..." << std::endl;
    }
    
  } else {
    std::cerr << "--> Failed to open file " << filename << std::endl;
    return 1;
  }

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
int main (int argc,
	  char *argv[])
{
  int retval = 0;
  std::string filename;
  std::string pathTestData;

  /* Check parameter provided from the command line */
  if ( argc>1 ) {
    pathTestData = std::string(argv[1]);
  } else {
    std::cerr << "[ERROR] No path to directory with test data!" << std::endl;
    return 1;
  }

  /* Read the list of trusted proxies */
  filename = pathTestData + "/trusted_proxies.yml";
  retval += readTrustedProxies (filename);
 
  /* Read attributes of user role */
  filename = pathTestData + "/roles.yml";
  retval += readDatabaseRoles (filename);

  return retval;
}
