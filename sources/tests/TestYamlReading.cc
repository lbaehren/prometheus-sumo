
#include <fstream>
#include <iostream>
/* YAML support */
#include <yaml-cpp/yaml.h>
/* Project */
#include <Common.h>
#include <ConfigFileInstitution.h>

/*!
  \file TestYamlReading.cc
  \brief Test reading in configuration data from \ref refman_yaml files
  \author Lars Baehren
*/

// =============================================================================
//
//  Data stuctures
//
// =============================================================================

/*! Data structure to store a node representing a movie */
struct Movie {
  //! Title of the movie
  std::string title;
  //! Release year of the movie
  unsigned int release;
  //! Director of the movie
  std::string director;
};

/*! Data structure to store a node representing a database role */
struct Role {
  //! Title for the role
  std::string title;
  //! ID used internally with the database
  unsigned int id;
};

namespace prometheus {   //   namespace prometheus - BEGIN

  namespace test {   //   namespace test - BEGIN
    
    class Roles {
      std::map<unsigned int,std::string> itsRoles;
    public:
      // === Construction ========================
      //! Default constructor
      Roles () {
	itsRoles.clear();
      }
      //! Argumented constructor
      Roles (unsigned int const &id,
	     std::string const &title) {
	itsRoles[id] = title;
      }
      //! Argumented constructor
      Roles (Role const &role) {
	setRole(role);
      }
      // === Parameter access ====================
      //! Set a database role
      void setRole (Role const &role) {
	itsRoles[role.id] = role.title;
      }
      //! Get the number of stored database roles
      inline size_t size () {
	return itsRoles.size();
      }
      //! Get the stored database roles
      inline std::map<unsigned int,std::string> roles () {
	return itsRoles;
      }
      //! Get the IDs of the database roles
      inline std::vector<unsigned int> ids () {
	std::map<unsigned int,std::string>::iterator it;
	std::vector<unsigned int> ids;
	for (it=itsRoles.begin(); it!=itsRoles.end(); ++it) {
	  ids.push_back(it->first);
	}
	return ids;
      }
      //! Get the titles of the database roles
      inline std::vector<std::string> titles () {
	std::map<unsigned int,std::string>::iterator it;
	std::vector<std::string> titles;
	for (it=itsRoles.begin(); it!=itsRoles.end(); ++it) {
	  titles.push_back(it->second);
	}
	return titles;
      }
    };

  };   //   namespace test - END

};   //   namespace prometheus - END

// =============================================================================
//
//  Operator overloading
//
// =============================================================================

/*!
  \brief Overloading of the output operator for a node representing a movie.
  \param node  -- Object container for the node.
  \param movie -- Data structure into which the node's contents is being stored.
*/
void operator >> (const YAML::Node& node,
		  Movie& movie)
{
  node["title"]    >> movie.title;
  node["release"]  >> movie.release;
  node["director"] >> movie.director;
}

/*!
  \brief Overloading of the output operator for a node representing a database role.
  \param node -- Object container for the node.
  \param role -- Data structure into which the node's contents is being stored.
*/
void operator >> (const YAML::Node& node, Role& role) {
  node["title"] >> role.title;
  node["id"]    >> role.id;
}

// =============================================================================
//
//  Tests functions
//
// =============================================================================

//______________________________________________________________________________
//                                                                      readList

/*!
  \brief Read data from list.
  \param filename - Path to the configuration file.
  \return Status of the function; returns non-zero value in case an error was
          encountered.
*/
int readList (std::string const &filename)
{
  std::cout << "\n[YamlReader::readList]\n" << std::endl;
  
  std::ifstream infile (filename.c_str());
  
  if (infile.is_open()) {
    std::vector<std::string> dataVector;
    std::set<std::string> dataSet;
    YAML::Node node;
    YAML::Parser parser(infile);
    // Parse data into node
    parser.GetNextDocument(node);
    /* Parse the contents of the node */
    std::cout << "--> Node data" << std::endl;
    for (YAML::Iterator it=node.begin();it!=node.end();++it) {
      std::string data;
      *it >> data;
      dataVector.push_back(data);
      dataSet.insert(data);
      std::cout << "- " << data << std::endl;
    }
    /* Display the data read from the file*/
    std::cout << "--> std::vector<std::string>\n" << dataVector << std::endl;
    std::cout << "--> std::set<std::string>\n"    << dataSet    << std::endl;
  } else {
    std::cerr << "--> Failed to open file " << filename << std::endl;
    return 1;
  }
  
  /* Close the input stream */
  infile.close();

  return 0;
}

//______________________________________________________________________________
//                                                          readAssociativeArray

/*!
  \brief Read data from asociative array.
  \param filename - Path to the configuration file.
  \return Status of the function; returns non-zero value in case an error was
          encountered.
*/
int readAssociativeArray (std::string const &filename)
{
  std::cout << "\n[YamlReader::readAssociativeArray]\n" << std::endl;
  
  std::ifstream infile (filename.c_str());
  
  if (infile.is_open()) {
    YAML::Node node;
    YAML::Parser parser(infile);
    // Parse data into node
    parser.GetNextDocument(node);
    std::cout << "--> nof. nodes = " << node.size() << std::endl;
    /* Parse the contents of the node */
    for (YAML::Iterator it=node.begin();it!=node.end();++it) {
      Movie movie;
      *it >> movie;
      /* Dispay contents of the node */
      std::cout << "- " << movie.title << " (" << movie.release << ")"
		<< "\t- " << movie.director
		<< std::endl;
    }
  } else {
    std::cerr << "--> Failed to open file " << filename << std::endl;
    return 1;
  }
  
  /* Close the input stream */
  infile.close();

  return 0;
}

//______________________________________________________________________________
//                                                        readScalarsToSequences

/*!
  \brief Read data from mapping of scalars to sequences.
  \param filename - Path to the configuration file.
  \return Status of the function; returns non-zero value in case an error was
          encountered.
*/
int readScalarsToSequences (std::string const &filename)
{
  std::cout << "\n[YamlReader::readScalarsToSequences]\n" << std::endl;
  
  std::ifstream infile (filename.c_str());
  
  if (infile.is_open()) {
    YAML::Node node;
    YAML::Parser parser(infile);
    // Parse data into node
    parser.GetNextDocument(node);
    std::cout << "--> nof. nodes = " << node.size() << std::endl;
    /* Parse the contents of the node */
    for (YAML::Iterator it=node.begin();it!=node.end();++it) {
      /* Get the key of the node */
      std::string director;
      it.first()>> director;
      std::cout << "  " << director << ":" << std::endl;
      for (size_t n=0; n<it.second().size(); ++n) {
        std::string movie;
        it.second()[n] >> movie;
        std::cout << "    - " << movie << std::endl;
      }
    }
  } else {
    std::cerr << "--> Failed to open file " << filename << std::endl;
    return 1;
  }
  
  /* Close the input stream */
  infile.close();

  return 0;
}

//______________________________________________________________________________
//                                                            readTrustedProxies

/*!
  \brief Read in the list of trusted proxies

  \param filename - Path to the configuration file.

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

//______________________________________________________________________________
//                                                             readDatabaseRoles

/*!
  \brief Read user roles for database
  \param filename -- Path to the configuration file
*/
int readDatabaseRoles (std::string const &filename)
{
  std::cout << "\n[YamlReader::readDatabaseRoles]\n" << std::endl;
  
  std::ifstream infile (filename.c_str());
  
  if (infile.is_open()) {
    
    prometheus::test::Roles roles;
    YAML::Node node;
    
    YAML::Parser parser(infile);
    parser.GetNextDocument(node);
    
    std::cout << "--> nof. nodes = " << node.size() << std::endl;

    for (YAML::Iterator it=node.begin(); it!=node.end(); ++it) {
      std::string key;
      Role role;
      it.first() >> key;
      it.second() >> role;
      /* Store the contents of the node */
      roles.setRole(role);
    }

    /* Show the database role titles */
    std::cout << roles.ids()    << std::endl;
    std::cout << roles.titles() << std::endl;
    
  } else {
    std::cerr << "--> Failed to open file " << filename << std::endl;
    return 1;
  }

  return 0;
}

// =============================================================================
//
//  Main program function
//
// =============================================================================

/*! Program main function */
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
  
  /*
   *  Basic parser testing
   */
  
  filename = pathTestData + "/yaml_List.yml";
  retval +=  readList(filename);
  
  filename = pathTestData + "/yaml_AssociativeArray.yml";
  retval +=  readAssociativeArray(filename);

  filename = pathTestData + "/yaml_ScalarsToSequences.yml";
  retval +=  readScalarsToSequences(filename);

  /*
   *  prometheus/pandora type configuration data
   */

  /* Read the list of trusted proxies */
  filename = pathTestData + "/trusted_proxies.yml";
  retval += readTrustedProxies (filename);
 
  /* Read attributes of user role */
  filename = pathTestData + "/roles.yml";
  retval += readDatabaseRoles (filename);

  return retval;
}
