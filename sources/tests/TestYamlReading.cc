
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

namespace prometheus {
  
  class Movie {
    std::string itsTitle;
    unsigned int itsRelease;
    std::string itsDirector;
  public:
    //! Default constructor
    Movie (){
      itsTitle    = "";
      itsRelease  = 0;
      itsDirector = "";
    }
    //! Argumented constructor
    Movie (std::string const &title,
	   unsigned int const &release,
	   std::string const &director) {
      itsTitle    = title;
      itsRelease  = release;
      itsDirector = director;
    }
    //! Get the title
    inline std::string title () const {
      return itsTitle;
    }
    //! Get the release year
    inline unsigned int release () const {
      return itsRelease;
    }
    //! Get the director
    inline std::string director () const {
      return itsDirector;
    }
  };
  
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

/*! Data structure to store data attached to a node */
struct Movie {
  //! Title of the movie
  std::string title;
  //! Release year of the movie
  unsigned int release;
  //! Director of the movie
  std::string director;
};

/*!
  \brief Overloading of the output operator for a node.
  \param node -- Object container for the node.
  \param role -- Data structure into which the node's contents is being stored.
*/
void operator >> (const YAML::Node& node,
		  Movie& movie)
{
  node["title"]    >> movie.title;
  node["release"]  >> movie.release;
  node["director"] >> movie.director;
}

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

/*! Data structure to store data attached to a node */
struct Movies {
  std::vector<std::string> titles;
};

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

//! Data structure of configuration node
struct Role {
  //! Title for the role
  std::string title;
  //! ID used internally with the database
  unsigned int id;
};

/*!
  \brief Overloading of the output operator for a node.
  \param node -- Object container for the node.
  \param role -- Data structure into which the node's contents is being stored.
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
  std::cout << "\n[YamlReader::readDatabaseRoles]\n" << std::endl;
  
  std::ifstream infile (filename.c_str());
  
  if (infile.is_open()) {
    
    YAML::Node node;
    
    YAML::Parser parser(infile);
    parser.GetNextDocument(node);
    
    std::cout << "--> nof. nodes = " << node.size() << std::endl;

    std::cout << "---" << std::endl;
    for (YAML::Iterator it=node.begin(); it!=node.end(); ++it) {
      std::string key;
      Role role;
      it.first() >> key;
      it.second() >> role;
      std::cout << "" << key << std::endl;
      std::cout << "  " << role.title << std::endl;
      std::cout << "  " << role.id    << std::endl;
    }
    
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
